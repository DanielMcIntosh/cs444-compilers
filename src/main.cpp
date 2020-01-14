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

void compileMain(JoosC *joosc, const vector<string> &fileList) {
  for (const string &file: fileList) {
    const char *fileName = file.c_str();
    const s64 size = getFileSize(fileName);
    if (size < 0) {
      LOGR("%s is not accessible", fileName);
      continue;
    }

    char *contents;
    s32 fileSize;
    readEntireFile(fileName, &contents, &fileSize);
    Scan::ScanResult result = Scan::scannerProcessFile(&joosc->scanner, contents);
    if (result.valid) {
      LOGR("Valid, %ld bytes, %s", size, fileName);
    } else {
      char snapshot[TWO_TO_EIGHT];
      const char *snapshotStart = max(contents, contents + result.errorPosition - 4);
      s32 snapshotLen = min(fileSize - result.errorPosition, 4);
      snprintf(snapshot, snapshotLen, "%s", snapshotStart);
      LOGR("Invalid (%s), %ld bytes, %s", snapshot, size, fileName);
    }
    free(contents);

    strdecl256(scannerOutputPath, "output/scanner/%s", file.c_str());
    char *lastSlash = strrchr(scannerOutputPath, '/');
    *lastSlash = 0;
    strdecl512(mkdirCommand, "mkdir -p %s", scannerOutputPath);
    system(mkdirCommand);
    *lastSlash = '/';

    FILE *scannerDump = fopen(scannerOutputPath, "w");
    s32 curLineLen = 0;
    for (const Scan::LexToken &token : result.tokens) {
      curLineLen += token.name.length();
      curLineLen += token.lexeme.length();
      curLineLen += 3;

      fprintf(scannerDump, "%s(%s) ", token.name.c_str(), token.lexeme.c_str());
      if (curLineLen > 80) {
        fprintf(scannerDump, "\r\n");
        curLineLen = 0;
      }
    }
    fclose(scannerDump);
  }
}

void batchTesting(JoosC *joosc, const string &baseDir,
                  const vector<string> &stdlib) {
  DIR *dir = opendir(baseDir.c_str());
  if (!dir)
    return;

  auto fileList = stdlib;
  const s32 numLib = stdlib.size();
  s32 numTests = 0;
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

    if (getFileType(fullPath.c_str()) == FileTypeRegular) {
      fileList.push_back(fullPath);
      compileMain(joosc, fileList);
      fileList.pop_back();
    } else if (getFileType(fullPath.c_str()) == FileTypeDirectory) {
      vector<string> fileBundle;
      getJavaFilesRecursive(fileBundle, fullPath + "/");
      fileList.insert(fileList.end(), fileBundle.begin(), fileBundle.end());
      compileMain(joosc, fileList);
      fileList.resize(numLib);
    } else {
      continue;
    }

    ++numTests;
  }
  LOGR("%d tests.", numTests);
  closedir(dir);
}

void checkTestMode(JoosC *joosc) {
  const char *mode = getenv("JOOSC_MODE");
  if (!mode || strcmp(mode, "test"))
    return;
  const char *assnNum = getenv("JOOSC_ASSN");
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
  const char *mode = getenv("JOOSC_MODE");
  if (!mode || strcmp(mode, "scanner"))
    return;

  const char *file = getenv("JOOSC_SCANNER_FILE");
  if (!file)
    file = "lex.txt";

  {       
    using namespace Scan;

    char *fileContents;
    s32 fileSize;
    readEntireFile(file, &fileContents, &fileSize);
    if (!fileContents)
      return;
    
    Scanner scanner;
    scannerRegularLanguageToNFA(&scanner, fileContents);
    scannerNFAtoDFA(&scanner);
    scannerDumpDFA(&scanner);
    LOGR("%lu tokens, %lu nstates, %lu dstates", scanner.tokens.size(),
         scanner.nstates.size(), scanner.dstates.size());

    free(fileContents);
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
  
  compileMain(&joosc, fileList);
  
  globalFini();
}
