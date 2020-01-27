#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
#include <string>

#include "utility.h"
#include "platform.h"
#include "scanner.h"

using namespace std;

struct JoosC {
	Scan::Scanner scanner;
};

void getJavaFilesRecursive(vector<string> &fileList, const string &folder) {
	DIR *dir = opendir(folder.c_str());
	if (!dir)
		return;

	while (true) {
		struct dirent *ent = readdir(dir);
		if (!ent)
			break;

		if (!strcmp(".", ent->d_name))
			continue;

		if (!strcmp("..", ent->d_name))
			continue;

		string name(ent->d_name);
		string fullPath = folder + name;

		if (getFileType(fullPath.c_str()) == FileTypeRegular &&
				strstr(ent->d_name, ".java")) {
			fileList.push_back(fullPath);
		} else if (getFileType(fullPath.c_str()) == FileTypeDirectory) {
			getJavaFilesRecursive(fileList, fullPath + string("/"));
		}
	}
	closedir(dir);
}

struct CompileResult {
	s32 numValid;
	s32 numCorrect;
	s32 fileProcessed;
};

CompileResult compileMain(JoosC *joosc, const vector<string> &fileList) {
	CompileResult compileResult;
	compileResult.numCorrect = 0; compileResult.numValid = 0; compileResult.fileProcessed = 0;

	for (const string &file: fileList) {
		const char *sourceFileName = file.c_str();
		const s64 size = getFileSize(sourceFileName);
		if (size < 0) {
			LOGR("%s is not accessible", sourceFileName);
			continue;
		}

		++compileResult.fileProcessed;

		s32 sourceFileSize;
		std::unique_ptr<char[]> sourceCode = readEntireFile(sourceFileName, &sourceFileSize);

		Scan::ScanResult result = Scan::scannerProcessText(&joosc->scanner,
		                                                   sourceCode.get());

		const char *colorHead, *colorTail = "\033[0m";
		{ // determine the validity of the program from file name, if possible
			bool sourceValidity;
			const char *lastSlash = strrchr(sourceFileName, '/');
			sourceValidity = (lastSlash[2] != 'e');
			if (result.valid != sourceValidity) {
				colorHead = "\033[0;31m"; // red
			} else {
				colorHead = "\033[0;32m"; // green
				++compileResult.numCorrect;
			}
		}

		strdecl256(fileInfo, "%s, %d bytes, %ld tokens", sourceFileName,
						sourceFileSize, result
		.tokens.size());

		if (result.valid) {
			++compileResult.numValid;
			LOGR("%s%s%s", colorHead, fileInfo, colorTail);
		} else {
			char snapshot[TWO_TO_EIGHT];
			const char *snapshotStart = max(sourceCode.get(), sourceCode.get() + result.errorPosition - 6);
			s32 snapshotLen = min(sourceFileSize - result.errorPosition, 6);
			snprintf(snapshot, snapshotLen, "%s", snapshotStart);
			LOGR("%s%s (%s) %s", colorHead, fileInfo, snapshot, colorTail);
		}

		strdecl256(baseOutputPath, "output/%s", file.c_str());

		{ // create descending directories
			char *lastSlash = strrchr(baseOutputPath, '/');
			*lastSlash = '\0';
			createDirectoryChain(baseOutputPath);
			*lastSlash = '/';
		}

		{ // copy the original source code file so that it appears in the same directory
			// as debug output files
			FILE *originalFile = fopen(baseOutputPath, "wb");
			fwrite(sourceCode.get(), sourceFileSize, 1, originalFile);
			fclose(originalFile);
		}

		{ // scanner debug output
			strdecl512(scannerOutputPath, "%s.tokens.txt", baseOutputPath);
			FILE *scannerDump = fopen(scannerOutputPath, "w");
			s32 curLineLen = 0;
			for (const Scan::LexToken &token : result.tokens) {
				curLineLen += token.name.length();
				curLineLen += 2;
				curLineLen += 3;

				fprintf(scannerDump, "%s(%2s) ", token.lexeme.c_str(), token.name.c_str());
				if (curLineLen > 70) {
					fprintf(scannerDump, "\r\n");
					curLineLen = 0;
				}
			}
			fclose(scannerDump);

			snprintf(scannerOutputPath, 512, "%s.scanner.txt", baseOutputPath);
			scannerDump = fopen(scannerOutputPath, "w");
			fwrite(result.detailedStep.c_str(), result.detailedStep.size(), 1, scannerDump);
			fclose(scannerDump);
		}
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
	if (!file) {
		Scan::scannerTest();
		return;
	}

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
	vector<string> fileList;
	for (int i = 1; i < argc; ++i) {
		fileList.push_back(string(argv[i]));
	}

	globalInit();

	checkScanner();

	JoosC joosc;
	scannerLoadJoosRule(&joosc.scanner);

	checkTestMode(&joosc);

	CompileResult result = compileMain(&joosc, fileList);

	globalFini();

  return result.fileProcessed == result.numValid ? 0 : 42;
}
