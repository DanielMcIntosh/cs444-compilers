#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <string>

#include "utility.h"
#include "platform.h"
#include "scanner.h"
#include "pt/parser.h"
#include "grammar.h"
#include "pt/parserAutoAST.h"
#include "weeder.h"

using namespace std;

enum class CompileStageType {
  Scan,
  Parse,
  Weed,
  Pass
};

const char *gCompileStageTypeName[] = {
  "Scan", "Parse", "Weed", "(Pass)"
};

struct JoosC {
	Scan::Scanner scanner;
	Parse::Parser parser;

  Parser::Grammar grammar;

  JoosC(): grammar(Parser::readLR1File("joos.lr1")) {}
};

struct CompileResult {
	s32 numValid = 0;
	s32 numCorrect = 0;
	s32 fileProcessed = 0;
};

struct CompileSingleResult {
  string fileName;
  s32 fileSize;
  unique_ptr<char[]> fileContent;

  CompileStageType failedStage;

  Scan::ScanResult scanResult;
  Parse::ParseResult parseResult;
  Weeder::WeederResult weederResult;
};

bool isProgramValidFromFileName(const char *name) {
  const char *lastSlash = strrchr(name, '/');
  return (lastSlash[2] != 'e');
}

void compileReportSingleFile(const CompileSingleResult &result) {
  const char *colorHead, *colorTail = "\033[0m";
  // determine the validity of the program from file name, if possible
  bool sourceValidity, ourVerdict;
  sourceValidity = isProgramValidFromFileName(result.fileName.c_str());
  ourVerdict = result.failedStage == CompileStageType::Pass;
  if (ourVerdict != sourceValidity) {
    colorHead = "\033[0;31m"; // red
  } else {
    colorHead = "\033[0;32m"; // green
  }

  if (ourVerdict != sourceValidity)
    LOGR("%s%s (Failed stage: %s) %s", colorHead, result.fileName.c_str(), gCompileStageTypeName[static_cast<s32>(result.failedStage)], colorTail);
}

void compileDumpSingleResult(char *baseOutputPath, const CompileSingleResult &singleResult) {
  { // create descending directories
    char *lastSlash = strrchr(baseOutputPath, '/');
    *lastSlash = '\0';
    createDirectoryChain(baseOutputPath);
    *lastSlash = '/';
  }

  { // copy the original source code file so that it appears in the same directory
    // as debug output files
    FILE *originalFile = fopen(baseOutputPath, "wb");
    fwrite(singleResult.fileContent.get(), singleResult.fileSize, 1, originalFile);
    fclose(originalFile);
  }

  Scan::scannerDumpDebugInfo(singleResult.scanResult, baseOutputPath);
  Parse::parserDumpDebugInfo(singleResult.parseResult, baseOutputPath);

  compileReportSingleFile(singleResult);
}

CompileSingleResult compileSingle(JoosC *joosc, const char *fileName) {
  s32 sourceFileSize;
  std::unique_ptr<char[]> sourceCode = readEntireFile(fileName, &sourceFileSize);

  CompileSingleResult fileResult;
  fileResult.fileName = string(fileName);
  fileResult.fileSize = sourceFileSize;
  fileResult.fileContent = move(sourceCode);

  fileResult.scanResult = Scan::scannerProcessText(&joosc->scanner,
          fileResult.fileContent.get());

  if (!fileResult.scanResult.valid) {
    fileResult.failedStage = CompileStageType::Scan;
    return fileResult;
  }

  fileResult.parseResult = Parse::parserParse(&joosc->parser, fileResult.scanResult.tokens);
  if (!fileResult.parseResult.valid) {
    fileResult.failedStage = CompileStageType::Parse;
    return fileResult;
  }

  fileResult.weederResult = Weeder::weederCheck(fileResult.parseResult.treeRoot, fileName);
  if (!fileResult.weederResult.valid) {
    fileResult.failedStage = CompileStageType::Weed;
    return fileResult;
  }

  fileResult.failedStage = CompileStageType::Pass;
  return fileResult;
}

CompileResult compileMain(JoosC *joosc, const vector<string> &fileList) {
	CompileResult compileResult;
	compileResult.numCorrect = 0;
	compileResult.numValid = 0;
	compileResult.fileProcessed = 0;

	for (const string &file: fileList) {
		const char *sourceFileName = file.c_str();
		const s64 size = getFileSize(sourceFileName);
		if (size < 0) {
			LOGR("%s is not accessible", sourceFileName);
			continue;
		}

		++compileResult.fileProcessed;

		CompileSingleResult fileResult = compileSingle(joosc, sourceFileName);
		if (fileResult.failedStage == CompileStageType::Pass)
		  ++compileResult.numValid;
		if (isProgramValidFromFileName(sourceFileName) ==
            (fileResult.failedStage == CompileStageType::Pass)) {
		  ++compileResult.numCorrect;
		}

		strdecl256(baseOutputPath, "output/%s", file.c_str());
    compileDumpSingleResult(baseOutputPath, fileResult);

    Parse::parserASTDelete(fileResult.parseResult.treeRoot);
	}
	return compileResult;
}

void batchTesting(JoosC *joosc, const string &baseDir,
									const vector<string> &stdlib) {
	DIR *dir = opendir(baseDir.c_str());
	if (!dir)
		return;

	auto fileList = stdlib;
	const s32 numLib = stdlib.size();
	s32 numTests = 0;
	s32 numPassed = 0;
	LOGR("Batch test starting...");
	while (true) {
		struct dirent *ent = readdir(dir);
		if (!ent)
			break;

		if (!strcmp(".", ent->d_name))
			continue;

		if (!strcmp("..", ent->d_name))
			continue;

		string name(ent->d_name);
		string fullPath = baseDir + name;

		CompileResult result;

		if (getFileType(fullPath.c_str()) == FileTypeRegular) {
			fileList.push_back(fullPath);
			result = compileMain(joosc, fileList);
			fileList.pop_back();
		} else if (getFileType(fullPath.c_str()) == FileTypeDirectory) {
			vector<string> fileBundle;
			getJavaFilesRecursive(fileBundle, fullPath + "/");
			fileList.insert(fileList.end(), fileBundle.begin(), fileBundle.end());
			result = compileMain(joosc, fileList);
			fileList.resize(numLib);
		} else {
			continue;
		}

		if (result.numCorrect == result.fileProcessed)
			++numPassed;
		++numTests;
	}
	LOGR("%d/%d tests passed.", numPassed, numTests);
	closedir(dir);
}

void checkTestMode(JoosC *joosc) {
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

void checkParser() {
	const char *mode = getenv("JOOSC_PARSER");
	if (!mode)
		return;

  s32 size;
  auto file = readEntireFile("joos.lr1", &size);

  using namespace Parse::AutoAST;
  AutoAST *ast = autoASTCreate();
  autoASTReadLR1(ast, file.get());
  autoASTOutputHeaders(ast);
  autoASTDestory(ast);
}

int main(int argc, const char ** argv) {
	vector<string> fileList;
	for (int i = 1; i < argc; ++i) {
		fileList.push_back(string(argv[i]));
	}

	globalInit();

	checkScanner();

  checkParser();

	JoosC joosc;
	scannerLoadJoosRule(&joosc.scanner);
  parserReadJoosLR1(&joosc.parser);

	checkTestMode(&joosc);

	CompileResult result = compileMain(&joosc, fileList);

	globalFini();

  return result.fileProcessed == result.numValid ? 0 : 42;
}
