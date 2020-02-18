#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <string>
#include <filesystem>

#include "parse/parser.h"
#include "utility.h"
#include "platform.h"
#include "scanner.h"
#include "weeder.h"
#include "profiler.h"
#include "middleend.h"
#include "ast/ast.h"
#include "ast/node.h"

#include "semantic/semantic.h"

using namespace std;
namespace fs = std::filesystem;

const char *gFrontendStageName[] = {
  "Scan", "Parse", "Weed", "(Pass)"
};

struct JoosC {
  Scan::Scanner scanner;
  Parse::Parser parser;
};

bool isProgramValidFromFileName(const char *name) {
  auto path = fs::path(string(name));
  const string stem = path.stem().string();
  return stem[1] != 'e';
}

void compileDumpSingleResult(char *baseOutputPath, const FrontendResult &singleResult) {
  { // create descending directories
    auto p = fs::path(string(baseOutputPath));
    fs::create_directories(p.parent_path());
  }

  { // copy the original source code file so that it appears in the same directory
    // as debug output files
    FILE *originalFile = fopen(baseOutputPath, "wb");
    fwrite(singleResult.fileContent, singleResult.fileSize, 1, originalFile);
    fclose(originalFile);

    //Scan::scannerDumpDebugInfo(singleResult.scanResult, baseOutputPath);
    //Parse::parserDumpDebugInfo(singleResult.parseResult, baseOutputPath);
    AST::astDumpDebugInfo(singleResult.astResult, baseOutputPath);
  }
}

FrontendResult doFrontEndSingle(JoosC *joosc, const char *fileName) {
  profileSection("compile single");
  s32 sourceFileSize;
  std::unique_ptr<char[]> sourceCode = readEntireFile(fileName, &sourceFileSize);

  FrontendResult fileResult;
  fileResult.fileName = string(fileName);
  fileResult.fileSize = sourceFileSize;
  fileResult.fileContent = sourceCode.release();

  {
    profileSection("scan");
    fileResult.scanResult = Scan::scannerProcessText(&joosc->scanner,
                                                     fileResult.fileContent);
    if (!fileResult.scanResult.valid) {
      fileResult.failedStage = FrontendStageType::Scan;
      return fileResult;
    }
  }

  {
    profileSection("parse");
    fileResult.parseResult = Parse::parserParse(&joosc->parser, fileResult.scanResult.tokens);
    if (!fileResult.parseResult.valid) {
      fileResult.failedStage = FrontendStageType::Parse;
      return fileResult;
    }
  }

  {
    profileSection("weeder");
    fileResult.weederResult = Weeder::weederCheck(fileResult.parseResult.treeRoot, fileName);
    if (!fileResult.weederResult.valid) {
      fileResult.failedStage = FrontendStageType::Weed;
      return fileResult;
    }
  }

  {
    profileSection("ast");
    fileResult.astResult = AST::buildAST(fileResult.parseResult.treeRoot);
  }

  fileResult.failedStage = FrontendStageType::Pass;

  strdecl256(baseOutputPath, "output/%s", fileName);
  compileDumpSingleResult(baseOutputPath, fileResult);

  return fileResult;
}

MiddleendResult doMiddleend(JoosC* joosc, const vector<FrontendResult> &frontendResults) {
  MiddleendResult result;

  using namespace Semantic;
  semanticInit(&result.semanticDB, frontendResults);
  semanticDo(&result.semanticDB);

  if (result.semanticDB.error != SemanticErrorType::None) {
	  result.failedStage = MiddleendStageType::Semantic;
	  return result;
  }

  return result;
}

int compileMain(JoosC *joosc, const vector<string> &fileList) {
  vector<FrontendResult> frontendResult;
  MiddleendResult middleend;
  int retVal = 0;
  for (const string &file: fileList) {
    frontendResult.emplace_back(doFrontEndSingle(joosc, file.c_str()));

    if (frontendResult.back().failedStage != FrontendStageType::Pass)
    {
      retVal = 42;
      LOGR("%s failed", file.c_str());
      goto cleanup;
    }
  }

  middleend = doMiddleend(joosc, frontendResult);
  if (middleend.failedStage != MiddleendStageType::Pass) {
    retVal = 42;
    goto cleanup;
  }

 cleanup:
  { // clean ups
    for (FrontendResult &singleResult : frontendResult) {
      frontendResultDelete(&singleResult);
    }
  }

  return retVal;
}

void batchTesting(JoosC *joosc, const string &baseDir,
                  const vector<string> &stdlib) {
  profileSection("batch testing");

  // perform frontend compilation on stdlib only once to speed things up
  vector<FrontendResult> stdlibFrontendResult;
  {
    profileSection("stdlib frontend");
    for (const auto &libName: stdlib) {
      stdlibFrontendResult.emplace_back(doFrontEndSingle(joosc, libName.c_str()));
    }

    for (auto &frontendResult : stdlibFrontendResult) {
      // stdlibs are always correct
      assert(frontendResult.failedStage == FrontendStageType::Pass);
      // prevent copying list of tokens
      frontendResult.scanResult.tokens.clear();
    }
  }

  vector<string> topLevelFileList;

  { // sort file lists as on linux they are not sorted
    auto it = fs::directory_iterator(baseDir);
    for (const auto &e: it) {
      fs::path path = e;
      path.make_preferred();
      topLevelFileList.push_back(path.string());
    }
    sort(topLevelFileList.begin(), topLevelFileList.end());
  }

  s32 numTests = 0;
  s32 numPassed = 0;
  for (const string &topLevelName : topLevelFileList) {
    fs::path dupPath = fs::path(topLevelName);
    bool valid = true;

    // stdlib frontend result is reused each time, so don't free them
    vector<FrontendResult> frontendResults = stdlibFrontendResult;

	  {
	  	// regenerate ast, since ast contains per compilation fields
	  	for (auto &frontend : frontendResults) {
	  		frontend.astResult = AST::buildAST(frontend.parseResult.treeRoot);
	  	}
	  }

    MiddleendResult middleend;

    if (fs::is_regular_file(dupPath)) {
      frontendResults.emplace_back(doFrontEndSingle(joosc, topLevelName.c_str()));
    } else if (fs::is_directory(dupPath)) {
      vector<string> fileBundle;
      getJavaFilesRecursive(fileBundle, topLevelName);
      for (const string &file: fileBundle) {
        frontendResults.emplace_back(doFrontEndSingle(joosc, file.c_str()));
      }
    } else {
      continue;
    }

    ++numTests;

    { // if there are any errors in frontend stage, find and report them
      for (auto it = frontendResults.begin() + stdlibFrontendResult.size();
           it != frontendResults.end(); ++it) {
        if (it->failedStage == FrontendStageType::Pass)
          continue;

        valid = false;
        goto cleanup;
      }
    }

	  if (numTests == 225) {
		  int dummp = 1234; // for breakpointing
	  }

    {
      profileSection("middleend");
      // middle end
      middleend = doMiddleend(joosc, frontendResults);
      if (middleend.failedStage != MiddleendStageType::Pass) {
        valid = false;
        goto cleanup;
      }
    }

  cleanup:
    if (valid != isProgramValidFromFileName(topLevelName.c_str())) {
      LOG_RED("%3d %s: (Semantic: %s)", numTests, topLevelName.c_str(),
      		 Semantic::gSemanticErrorTypeName[static_cast<int>(middleend.semanticDB.error)]);
    } else {
	    LOG_GREEN("%3d %s: (Semantic: %s)", numTests, topLevelName.c_str(),
	         Semantic::gSemanticErrorTypeName[static_cast<int>(middleend.semanticDB.error)]);
      ++numPassed;
    }

    {
      // free frontend result except stdlib
      for (auto it = frontendResults.begin() + stdlibFrontendResult.size();
           it != frontendResults.end(); ++it) {
        frontendResultDelete(&(*it));
      }
    }
  }

  LOGR("%d/%d tests passed.", numPassed, numTests);

  {
    // free stdlib frontend result separately
    for (auto &r: stdlibFrontendResult) {
      frontendResultDelete(&r);
    }
  }
}

void checkTestMode(JoosC *joosc) {
  profileSection("check test mode");
  const char *mode = getenv("JOOSC_TEST");
  if (!mode)
    return;
  const char *assnNum = getenv("JOOSC_TEST_ASSN");
  if (!assnNum)
    return;

  s32 num = atoi(assnNum);
  const char *assnBase = "tests/assignment_testcases";
  strdecl256(progFolder, "%s/a%d/", assnBase, num);

  vector<string> stdlib;
  if (num >= 2) {
    const char *libBase = "tests/stdlib";
    strdecl256(libFolder, "%s/%d.0/", libBase, num);
    getJavaFilesRecursive(stdlib, string(libFolder));
  }
  batchTesting(joosc, string(progFolder), stdlib);
}

void checkScanner() {
  const char *mode = getenv("JOOSC_SCANNER");
  if (!mode)
    return;

  const char *file = getenv("JOOSC_SCANNER_FILE");
  if (!file)
    return;

  {
    using namespace Scan;

    s32 fileSize;
    std::unique_ptr<char[]> fileContents = readEntireFile(file, &fileSize);
    if (!fileContents)
      return;

    Scanner scanner;
    scannerRegularLanguageToNFA(&scanner, fileContents.get());
    scannerNFAtoDFA(&scanner);
    scannerDumpDFA(&scanner);
    LOGR("%lu tokens, %lu nstates, %lu dstates", scanner.tokens.size(),
         scanner.nstates.size(), scanner.dstates.size());
  }
}

int main(int argc, const char ** argv) {
  profileSection("main app");

  globalInit();
  atexit(globalFini);

  vector<string> fileList;
  for (int i = 1; i < argc; ++i) {
    fileList.push_back(string(argv[i]));
  }

  checkScanner();

  JoosC joosc;
  {
    profileSection("scanner load rule");
    scannerLoadJoosRule(&joosc.scanner);
  }
  {
    profileSection("parser load rule");
    parserReadJoosLR1(&joosc.parser);
  }

  checkTestMode(&joosc);

  {
    profileSection("compile main");
    if (fileList.empty())
      return 0;
    return compileMain(&joosc, fileList);
  }
}
