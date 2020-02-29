#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <filesystem>
#include <string>
#include <thread>
#include <vector>

#include "ast/ast.h"
#include "ast/node.h"
#include "ast/type.h"
#include "middleend.h"
#include "parse/parser.h"
#include "profiler.h"
#include "scanner.h"
#include "semantic/semantic.h"
#include "weeder.h"

using namespace std;
namespace fs = std::filesystem;

const char* gFrontendStageName[] = {"Scan", "Parse", "Weed", "(Pass)"};

struct JoosC {
  Scan::Scanner scanner;
  Parse::Parser parser;
};

bool isProgramValidFromFileName(const char* name) {
  auto path = fs::path(string(name));
  const string stem = path.stem().string();
  return stem[1] != 'e';
}

void compileDumpSingleResult(char* baseOutputPath,
                             const FrontendResult& singleResult) {
  {  // create descending directories
    auto p = fs::path(string(baseOutputPath));
    fs::create_directories(p.parent_path());
  }

  {  // copy the original source code file so that it appears in the same
     // directory
    // as debug output files
    FILE* originalFile = fopen(baseOutputPath, "wb");
    fwrite(singleResult.fileContent, singleResult.fileSize, 1, originalFile);
    fclose(originalFile);

    // Scan::scannerDumpDebugInfo(singleResult.scanResult, baseOutputPath);
    // Parse::parserDumpDebugInfo(singleResult.parseResult, baseOutputPath);
    // AST::astDumpDebugInfo(singleResult.astResult, baseOutputPath);
  }
}

FrontendResult doFrontEndSingle(JoosC* joosc, const char* fileName) {
  profileSection("compile single");
  s32 sourceFileSize;
  std::unique_ptr<char[]> sourceCode =
      readEntireFile(fileName, &sourceFileSize);

  FrontendResult fileResult;
  fileResult.fileName = string(fileName);
  fileResult.fileSize = sourceFileSize;
  fileResult.fileContent = sourceCode.release();

  {
    profileSection("scan");
    fileResult.scanResult =
        Scan::scannerProcessText(&joosc->scanner, fileResult.fileContent);
    if (!fileResult.scanResult.valid) {
      fileResult.failedStage = FrontendStageType::Scan;
      return fileResult;
    }
  }

  {
    profileSection("parse");
    fileResult.parseResult =
        Parse::parserParse(&joosc->parser, fileResult.scanResult.tokens);
    if (!fileResult.parseResult.valid) {
      fileResult.failedStage = FrontendStageType::Parse;
      return fileResult;
    }
  }

  {
    profileSection("weeder");
    fileResult.weederResult =
        Weeder::weederCheck(fileResult.parseResult.treeRoot, fileName);
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
  // compileDumpSingleResult(baseOutputPath, fileResult);

  return fileResult;
}

void doMiddleend(JoosC* joosc, const vector<FrontendResult>& frontendResults,
                 MiddleendResult* result) {
  using namespace Semantic;
  semanticInit(&result->semanticDB, frontendResults);
  semanticDo(&result->semanticDB);

  if (result->semanticDB.error != SemanticErrorType::None) {
    result->failedStage = MiddleendStageType::Semantic;
  }
}

int compileMain(JoosC* joosc, const vector<string>& fileList) {
  vector<FrontendResult> frontendResult;
  MiddleendResult middleend;
  int retVal = 0;
  for (const string& file : fileList) {
    frontendResult.emplace_back(doFrontEndSingle(joosc, file.c_str()));

    if (frontendResult.back().failedStage != FrontendStageType::Pass) {
      retVal = 42;
      LOGR("%s failed", file.c_str());
      goto cleanup;
    }
  }

  doMiddleend(joosc, frontendResult, &middleend);
  if (middleend.failedStage != MiddleendStageType::Pass) {
    retVal = 42;
    goto cleanup;
  }

cleanup : {  // clean ups
  for (FrontendResult& singleResult : frontendResult) {
    frontendResultDelete(&singleResult);
  }
}

  return retVal;
}

struct BatchTestResult {
  FrontendStageType frontendStage;
  MiddleendResult middleend;

  BatchTestResult();
};

BatchTestResult::BatchTestResult() : frontendStage(FrontendStageType::Pass) {}

struct BatchTestThreadCtx {
  // input
  JoosC* joosc;
  const vector<string>* topLevel;
  int begin;
  int end;
  int assgnNum;
  const vector<FrontendResult>* stdlibFrontendResult;

  // output
  vector<BatchTestResult>* result;
};

void batchTestingThread(BatchTestThreadCtx ctx) {
  for (int i = ctx.begin; i < ctx.end; ++i) {
    const string& topLevelName = (*ctx.topLevel)[i];
    BatchTestResult* caseResult = &(*ctx.result)[i];
    gTestIndex = i + 1;

    fs::path dupPath = fs::path(topLevelName);

    // stdlib frontend result is reused each time, so don't free them
    vector<FrontendResult> frontendResults;
	  {
		  {
			  profileSection("copy stdlib frontend result");
			  frontendResults = *ctx.stdlibFrontendResult;
		  }

		  {
			  // regenerate ast, since ast contains per compilation fields
			  profileSection("stdlib ast regen");
			  for (auto& frontend : frontendResults) {
				  frontend.astResult = AST::buildAST(frontend.parseResult.treeRoot);
			  }
		  }
	  }

    if (fs::is_regular_file(dupPath)) {
      frontendResults.emplace_back(
          doFrontEndSingle(ctx.joosc, topLevelName.c_str()));
    } else {
      ASSERT(fs::is_directory(dupPath));
      vector<string> fileBundle;
      getJavaFilesRecursive(fileBundle, topLevelName);
      for (const string& file : fileBundle) {
        frontendResults.emplace_back(doFrontEndSingle(ctx.joosc, file.c_str()));
      }
    }

    {  // if there are any errors in frontend stage, find and report them
      for (auto it = frontendResults.begin() + ctx.stdlibFrontendResult->size();
           it != frontendResults.end(); ++it) {
        if (it->failedStage == FrontendStageType::Pass) continue;

        caseResult->frontendStage = it->failedStage;
        goto cleanup;
      }
    }

    if (ctx.assgnNum >= 2) {
      profileSection("middleend");
      // middle end
      MiddleendResult* middleend = &caseResult->middleend;
      doMiddleend(ctx.joosc, frontendResults, middleend);
      if (middleend->failedStage != MiddleendStageType::Pass) {
        goto cleanup;
      }
    }

  cleanup : {
    // free frontend result except stdlib
    profileSection("test case frontend result free");
    for (auto it = frontendResults.begin() + ctx.stdlibFrontendResult->size();
         it != frontendResults.end(); ++it) {
      frontendResultDelete(&(*it));
    }
  }
  }
}

void batchTesting(JoosC* joosc, const string& baseDir,
                  const vector<string>& stdlib, int assignNum) {
  profileSection("batch testing");

  // perform frontend compilation on stdlib only once to speed things up
  vector<FrontendResult> stdlibFrontendResult;
  if (!gStandAloneMode) {
    profileSection("stdlib frontend");
    for (const auto& libName : stdlib) {
      stdlibFrontendResult.emplace_back(
          doFrontEndSingle(joosc, libName.c_str()));
    }

    for (auto& frontendResult : stdlibFrontendResult) {
      // stdlibs are always correct
      assert(frontendResult.failedStage == FrontendStageType::Pass);
      // prevent copying list of tokens
      frontendResult.scanResult.tokens.clear();
    }
  }

  vector<string> topLevelFileList;

  {  // sort file lists as on linux they are not sorted
    auto it = fs::directory_iterator(baseDir);
    for (const auto& e : it) {
      fs::path path = e;
      path.make_preferred();
      topLevelFileList.push_back(path.string());
    }
    sort(topLevelFileList.begin(), topLevelFileList.end());
  }

  int numTests = topLevelFileList.size();
  int numThreads = 1;

  vector<thread> threads;
  vector<BatchTestResult> results(numTests);

  for (int i = 0; i < numThreads; ++i) {
    int beginIdx = numTests / numThreads * i;
    int endIdx;
    if (numTests / numThreads < 1 || i == numThreads - 1)
      endIdx = numTests;
    else
      endIdx = numTests / numThreads * (i + 1);
    threads.push_back(
        thread(batchTestingThread,
               BatchTestThreadCtx{joosc, &topLevelFileList, beginIdx, endIdx,
                                  assignNum, &stdlibFrontendResult, &results}));
    if (endIdx == numTests) break;
  }

  for (auto& thr : threads) {
    thr.join();
  }

  int numPassed = 0;
  for (int i = 0; i < numTests; ++i) {
    const BatchTestResult& result = results[i];
    const string& topLevelName = topLevelFileList[i];
    bool valid = result.frontendStage == FrontendStageType::Pass &&
                 result.middleend.failedStage == MiddleendStageType::Pass;
	  if (valid == isProgramValidFromFileName(topLevelName.c_str())) {
		  ++numPassed;
	  }
	  const char *frontEndStageName = gFrontendStageName[static_cast<int>(result.frontendStage)];
	  const char *semanticError = Semantic::gSemanticErrorTypeName[static_cast<int>(
					  result.middleend.semanticDB.error)];

    #define logFmt "%3d %s: (FT: %s, Semantic: %s)"

    if (!gStandAloneMode) {
	    if (valid != isProgramValidFromFileName(topLevelName.c_str())) {
		    LOG_RED(logFmt, i + 1, topLevelName.c_str(), frontEndStageName, semanticError);
	    } else {
		    LOG_GREEN(logFmt, i + 1, topLevelName.c_str(), frontEndStageName, semanticError);
	    }
    } else {
    	// In standalone mode,
    	// ignore NotFoundImport error
    	if (result.middleend.semanticDB.error !=
	        Semantic::SemanticErrorType::NotFoundImport) {
		    if (valid != isProgramValidFromFileName(topLevelName.c_str())) {
			    LOG_RED(logFmt, i + 1, topLevelName.c_str(), frontEndStageName, semanticError);
		    } else {
			    LOG_GREEN(logFmt, i + 1, topLevelName.c_str(), frontEndStageName, semanticError);
		    }
	    }
    }
  }

  LOGR("%d/%lu tests passed.", numPassed, topLevelFileList.size());

  {
    // free stdlib frontend result separately
    profileSection("stdlib frontend result free");
    for (auto& r : stdlibFrontendResult) {
      frontendResultDelete(&r);
    }
  }
}

int checkEnvForTest() {
	const char* mode = getenv("JOOSC_TEST");
	if (!mode) return 0;
	const char* assnNum = getenv("JOOSC_TEST_ASSN");
	if (!assnNum) return 0;
	return atoi(assnNum);
}

void checkTestMode(JoosC* joosc, const char *argv1) {
  profileSection("check test mode");

  int num = checkEnvForTest();
  if (!num) {
  	if (argv1 && strlen(argv1) == 1) num = atoi(argv1);
  }
  if (!num) return;

  const char* assnBase = "tests/assignment_testcases";
  strdecl256(progFolder, "%s/a%d/", assnBase, num);

  vector<string> stdlib;
  if (num >= 2 && num <= 5) {
    const char* libBase = "tests/stdlib";
    strdecl256(libFolder, "%s/%d.0/", libBase, num);
    getJavaFilesRecursive(stdlib, string(libFolder));
    stdlib.push_back("tests/stdlib/IObject.java");
  }
  if (num >= 6||num == 3)
  	gStandAloneMode = true;
  batchTesting(joosc, string(progFolder), stdlib, num);
}

void checkScanner() {
  const char* mode = getenv("JOOSC_SCANNER");
  if (!mode) return;

  const char* file = getenv("JOOSC_SCANNER_FILE");
  if (!file) return;

  {
    using namespace Scan;

    s32 fileSize;
    std::unique_ptr<char[]> fileContents = readEntireFile(file, &fileSize);
    if (!fileContents) return;

    Scanner scanner;
    scannerRegularLanguageToNFA(&scanner, fileContents.get());
    scannerNFAtoDFA(&scanner);
    scannerDumpDFA(&scanner);
    LOGR("%lu tokens, %lu nstates, %lu dstates", scanner.tokens.size(),
         scanner.nstates.size(), scanner.dstates.size());
  }
}

int main(int argc, const char** argv) {
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

  const char *argv1 = nullptr;
	if (argc > 1)
		argv1 = argv[1];
  checkTestMode(&joosc, argv1);

  {
    profileSection("compile main");
    if (fileList.empty()) return 0;
    fileList.push_back("tests/stdlib/IObject.java");
    return compileMain(&joosc, fileList);
  }
}
