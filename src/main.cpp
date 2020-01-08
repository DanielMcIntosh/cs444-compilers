#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>
#include <sys/stat.h>

#include <vector>
#include <string>
#include <algorithm>

#include "utility.h"

using namespace std;

void getJavaFilesRecursive(vector<string> &fileList, string folder) {
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

    if (ent->d_type == DT_REG && strstr(ent->d_name, ".java")) {      
      fileList.push_back(fullPath);
    } else if (ent->d_type == DT_DIR) {
      getJavaFilesRecursive(fileList, fullPath + string("/"));
    }
  }
  closedir(dir);
}

void compileMain(const vector<string> &fileList) {
  LOGR("Compilation starting...");
  for (const auto &file: fileList) {
    struct stat statBuf;
    const char *fileName = file.c_str();
    s32 value = stat(fileName, &statBuf);
    if (value) {
      LOGR("failed to open %s: %s", fileName, strerror(errno));
      continue;      
    }

    LOGR("%s: %ld bytes", fileName, statBuf.st_size);
  }
  LOGR("End of compilation");
}

void batchTesting(const string &baseDir, const vector<string> &stdlib) {
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

    if (ent->d_type == DT_REG) {
      fileList.push_back(fullPath);
      compileMain(fileList);
      fileList.pop_back();
    } else if (ent->d_type == DT_DIR) {
      vector<string> fileBundle;
      getJavaFilesRecursive(fileBundle, fullPath + "/");
      fileList.insert(fileList.end(), fileBundle.begin(), fileBundle.end());
      compileMain(fileList);
      fileList.resize(numLib);
    } else {
      continue;
    }

    ++numTests;
  }
  LOGR("%d tests.", numTests);
  closedir(dir);
}

void checkTestMode() {
  const char *mode = getenv("JOOSC_MODE");
  if (!mode || strcmp(mode, "test"))
    return;
  const char *assnNum = getenv("JOOSC_ASSN");
  if (!assnNum)
    return;
  
  s32 num = atoi(assnNum);
  const char *assnBase = "./tests/assignment_testcases";
  strdecl256(progFolder, "%s/a%d/", assnBase, num);

  vector<string> stdlib;
  if (num >= 2) {
    const char *libBase = "./tests/stdlib";
    strdecl256(libFolder, "%s/%d.0/", libBase, num);
    getJavaFilesRecursive(stdlib, string(libFolder));
  }
  batchTesting(string(progFolder), stdlib);    
}

int main(int argc, const char ** argv) {
  vector<string> fileList;
  for (int i = 1; i < argc; ++i) {
    fileList.push_back(string(argv[i]));
  }
  
  globalInit();

  checkTestMode();

  compileMain(fileList);
  
  globalFini();
}
