#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#include <filesystem>
#include <string>
#include <thread>
#include <vector>

#include "ast/ast.h"
#include "ast/node.h"
#include "ast/type.h"
#include "codegen/codegen.h"
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

bool isProgramValidFromFileName(const char* name, int index) {
  auto path = fs::path(string(name));
  const string stem = path.stem().string();
  return stem[index] != 'e';
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

  strdecl256(baseOutputPath, "outputDebug/%s", fileName);
  // compileDumpSingleResult(baseOutputPath, fileResult);

  return fileResult;
}

void doMiddleend(const vector<FrontendResult>& frontendResults,
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
  BackendResult backend;
  string basePath = "output/";
  int retVal = 0;
  for (const string& file : fileList) {
    frontendResult.emplace_back(doFrontEndSingle(joosc, file.c_str()));

    if (frontendResult.back().failedStage != FrontendStageType::Pass) {
      retVal = 42;
      LOGR("%s failed", file.c_str());
      goto cleanup;
    }
  }

  doMiddleend(frontendResult, &middleend);
  if (middleend.failedStage != MiddleendStageType::Pass) {
    retVal = 42;
    goto cleanup;
  }

  backend = doBackend(middleend);
  for (const auto& sFile : backend.sFiles) {
    string thePath = basePath + sFile.fileName;
    FILE* f = fopen(thePath.c_str(), "wb");
    ASSERT(f);
    const string& content = sFile.fileContent;
    ASSERT(fwrite(content.c_str(), content.length(), 1, f) == 1);
    fclose(f);
  }

cleanup : {  // clean ups
  for (FrontendResult& singleResult : frontendResult) {
    frontendResultDelete(&singleResult);
  }
}

  return retVal;
}

struct BackendExecResult {
  string output;
  int retCode;
};

struct BatchTestResult {
  FrontendStageType frontendStage;
  MiddleendResult middleend;
  BackendExecResult execResult;

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

bool waitChild(pid_t pid) {
  ASSERT(pid != -1);

  pid_t childStat;
  auto ret = waitpid(pid, &childStat, 0);
  if (ret != pid)
  	return false;
  if (!WIFEXITED(childStat))
  	return false;
  if (WEXITSTATUS(childStat))
  	return false;
  return true;
}

struct ExecArg {
  vector<string> args;
  char** argv;
};

void execArgAdd(ExecArg* e, const string& str) { e->args.push_back(str); }

void execArgAdd(ExecArg* e, const char* str) { e->args.push_back(string(str)); }

void execArgPop(ExecArg* e, int num) {
  for (int i = 0; i < num; ++i) {
    e->args.pop_back();
  }
}

void execArgGen(ExecArg* e) {
  const int numArg = e->args.size();
  e->argv = new char*[numArg + 1];
  for (int i = 0; i < numArg; ++i) {
    e->argv[i] = strdup(e->args[i].c_str());
  }
  e->argv[numArg] = nullptr;
}

void execArgFree(ExecArg* e) {
  int size = e->args.size();
  for (int i = 0; i < size; ++i) {
    free(e->argv[i]);
  }
  delete[] e->argv;
  e->argv = nullptr;
}

void addr2lineHelper(const char *childPath, const char *inst, int memfd) {
  auto addrPid = fork();
  if (!addrPid) {
    const char* addr2line = "/usr/bin/addr2line";
    ASSERT(!close(STDOUT_FILENO));            
    ASSERT(dup2(memfd, STDOUT_FILENO) == STDOUT_FILENO);
    ASSERT(!close(memfd));
    execl(addr2line, addr2line, "-e", childPath, inst, nullptr);
    ASSERT2(false, "unreachable");
  }
  waitChild(addrPid);  
}

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
      ASSERT(topLevelName.find(".java") != string::npos);
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
      doMiddleend(frontendResults, middleend);
      if (middleend->failedStage != MiddleendStageType::Pass) {
        goto cleanup;
      }
    }

    if (ctx.assgnNum >= 5) {
      BackendResult backend = doBackend(caseResult->middleend);

      caseResult->execResult.retCode = -1;

      const string basePath = "outputDebug/" + to_string(i) + "/";
      fs::remove_all(basePath);
      fs::create_directories(basePath);

      {
        // save .s files to filesystem
        fs::create_directory(basePath + "sources");

        for (const auto& sFile : backend.sFiles) {
          const string thePath = basePath + "sources/" + sFile.fileName;
          FILE* f = fopen(thePath.c_str(), "wb");
          ASSERT(f);
          const string& content = sFile.fileContent;
          ASSERT(fwrite(content.c_str(), content.length(), 1, f) == 1);
          fclose(f);
        }
      }

      {
        // copy runtime.s
        fs::copy_file("tests/stdlib/5.0/runtime.s",
                      basePath + "sources/runtime.s");
      }

      {
        // assemble all .s files
        ExecArg nasmArg;
        execArgAdd(&nasmArg, "/usr/bin/nasm");
        execArgAdd(&nasmArg, "-O1");
        execArgAdd(&nasmArg, "-f");
        execArgAdd(&nasmArg, "elf");
        execArgAdd(&nasmArg, "-g");
        execArgAdd(&nasmArg, "-F");
        execArgAdd(&nasmArg, "dwarf");

        fs::create_directory(basePath + "objects");
        auto it = fs::directory_iterator(basePath + "sources");
        for (const auto& e : it) {
          fs::path path = e;
          const string strPath = path.string();
          auto pos = strPath.rfind(".s");
          if (pos == string::npos || pos != strPath.length() - 2) continue;

          const string objectPath =
              basePath + "objects/" + path.stem().string() + ".o";
          execArgAdd(&nasmArg, strPath);
          execArgAdd(&nasmArg, "-o");
          execArgAdd(&nasmArg, objectPath);
          execArgGen(&nasmArg);
          
          auto pid = vfork();
          if (!pid) {
            execv(nasmArg.argv[0], nasmArg.argv);
            ASSERT2(false, "unreachable");
          }
          execArgFree(&nasmArg);
          execArgPop(&nasmArg, 3);

          if (!waitChild(pid))
          	goto cleanup;
        }
      }

      {
        // link
        ExecArg ldArg;
        execArgAdd(&ldArg, "/usr/bin/ld");
        execArgAdd(&ldArg, "-melf_i386");
        execArgAdd(&ldArg, "-o");
        execArgAdd(&ldArg, string(basePath) + "main");
        {
          auto it = fs::directory_iterator(basePath + "objects");
          for (const auto& e : it) {
            fs::path path = e;
            const string strPath = path.string();
            auto pos = strPath.rfind(".o");
            if (pos == string::npos || pos != strPath.length() - 2) continue;
            execArgAdd(&ldArg, strPath);
          }
        }

        execArgGen(&ldArg);
        auto pid = vfork();
        if (!pid) {
          execv(ldArg.argv[0], ldArg.argv);
          ASSERT2(false, "unreachable");
        }

	      execArgFree(&ldArg);
        if (!waitChild(pid))
        	goto cleanup;

      }

      {
        // run main
        const string childPathStr = basePath + "main";
        const char* childPath = childPathStr.c_str();

        strdecl32(memfdName, "main_%d", i);
        int memfd = memfd_create(memfdName, 0);
        ASSERT(memfd > 0);

        string& outputBuffer = caseResult->execResult.output;

        auto pid = fork();
        if (!pid) {
          ASSERT(!ptrace(PTRACE_TRACEME, 0, nullptr, nullptr));
          ASSERT(!close(STDOUT_FILENO));
          ASSERT(dup2(memfd, STDOUT_FILENO) == STDOUT_FILENO);
          ASSERT(!close(memfd));
          execl(childPath, childPath, nullptr);
          ASSERT2(false, "unreachable");
        }
        ASSERT(pid != -1);

        int retCode = 1;

        while (true) {
          pid_t childStat;
          auto ret = waitpid(pid, &childStat, __WALL);
          ASSERT(ret == pid);

          if (WIFEXITED(childStat)) {
            retCode = WEXITSTATUS(childStat);
            LOGS(outputBuffer, "(Exited with %d)", retCode);
            break;
          }

          ASSERT(WIFSTOPPED(childStat));
          int sig = WSTOPSIG(childStat);
          if (sig == SIGTRAP) {
            ASSERT(!ptrace(PTRACE_CONT, pid, nullptr, nullptr));
            continue;
          }

          struct user_regs_struct regs;
          ASSERT(!ptrace(PTRACE_GETREGS, pid, nullptr, &regs));

          siginfo_t siginfo;
          ASSERT(!ptrace(PTRACE_GETSIGINFO, pid, nullptr, &siginfo));

#define LOWER(_x) (uint32_t)(_x & 0xffffffff)

          strdecl32(ip, "0x%x", LOWER(regs.rip));
          addr2lineHelper(childPath, ip, memfd);

          LOGS(outputBuffer, "Received %d (%s)\n", siginfo.si_signo,
               strsignal(siginfo.si_signo));
          LOGS(outputBuffer, "eax %8x ebx %8x ecx %8x edx %8x\n",
               LOWER(regs.rax), LOWER(regs.rbx), LOWER(regs.rcx),
               LOWER(regs.rdx));
          LOGS(outputBuffer, "esi %8x edi %8x esp %8x ebp %8x eip %8x\n",
               LOWER(regs.rsi), LOWER(regs.rdi), LOWER(regs.rsp),
               LOWER(regs.rbp), LOWER(regs.rip));

          outputBuffer += "\n\n";          

          for (int k = 16; k >= -16;) {
          	unsigned long long address = regs.rbp + k;
	          long result = ptrace(PTRACE_PEEKDATA, pid, address, nullptr);

            uint64_t half2 = (result & 0xffffffffULL);
            uint64_t half1 = (result & ~0xffffffffULL) >> 32;

            if (k == 0) outputBuffer += '\n';

            k += 4;
            
	          strdecl32(value1, "ebp%c%2d: %8lx ", k < 0 ? '-' : '+',
	          				  (k < 0 ? -k : k), half1);
	          outputBuffer += value1;

            if (k == 4) {
              strdecl32(caller, "0x%lx", half1);
              addr2lineHelper(childPath, caller, memfd);
            }            
           
            k -= 4;

	          strdecl32(value2, "ebp%c%2d: %8lx ", k < 0 ? '-' : '+',
	          				  (k < 0 ? -k : k), half2);
	          outputBuffer += value2;

            k -= 8;
          }

          outputBuffer += "\n\n";

          for (int k = 16; k >= 0;) {
          	unsigned long long address = regs.rsp + k;
	          long result = ptrace(PTRACE_PEEKDATA, pid, address, nullptr);

            uint64_t half2 = (result & 0xffffffffULL);
            uint64_t half1 = (result & ~0xffffffffULL) >> 32;

            if (k == 0) outputBuffer += '\n';

            k += 4;
            
	          strdecl32(value1, "esp%c%2d: %8lx ", k < 0 ? '-' : '+',
	          				  (k < 0 ? -k : k), half1);
	          outputBuffer += value1;
           
            k -= 4;

	          strdecl32(value2, "esp%c%2d: %8lx ", k < 0 ? '-' : '+',
	          				  (k < 0 ? -k : k), half2);
	          outputBuffer += value2;

            k -= 8;
          }          

	        kill(pid, SIGKILL);

          break;
        }

        ASSERT(!fsync(memfd));
        FILE* childOut = fdopen(memfd, "rb");
        ASSERT(childOut);
        fseek(childOut, 0, SEEK_END);
        int childOutSize = ftell(childOut);
        fseek(childOut, 0, SEEK_SET);
        string childOutStr(childOutSize, 0);
        if (childOutSize > 0) {
	        ASSERT(fread((void*)childOutStr.data(), childOutSize, 1, childOut) ==
	               1);
        }
        caseResult->execResult.output =
          childOutStr + "\n" + caseResult->execResult.output;

        caseResult->execResult.retCode = retCode;
        fclose(childOut);
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
  int numThreads = 12;

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
    BatchTestResult& result = results[i];
    const string& topLevelName = topLevelFileList[i];
    bool valid = result.frontendStage == FrontendStageType::Pass &&
                 result.middleend.failedStage == MiddleendStageType::Pass;

    const Semantic::SemanticDB* sdb = &result.middleend.semanticDB;
    const char* frontEndStageName =
        gFrontendStageName[static_cast<int>(result.frontendStage)];
    const char* semanticError =
        Semantic::gSemanticErrorTypeName[static_cast<int>(
            result.middleend.semanticDB.error)];

#define logFmt "%3d %s:1 FT: %s, Semantic: %s %s"

    bool correctness;
    if (assignNum < 5) {
      correctness =
          valid == isProgramValidFromFileName(topLevelName.c_str(), 1);
    } else {
      if (!isProgramValidFromFileName(topLevelName.c_str(), 2))
        correctness = result.execResult.retCode == 13;
      else
        correctness = result.execResult.retCode == 123;
    }

    if (correctness) ++numPassed;

    if (!correctness) {
      LOG_RED(logFmt, i, topLevelName.c_str(), frontEndStageName,
              semanticError, sdb->errMsg.c_str());
    } else {
      LOG_GREEN(logFmt, i, topLevelName.c_str(), frontEndStageName,
                semanticError, sdb->errMsg.c_str());
    }

    if (assignNum >= 5) {
    	fprintf(stderr, "%s\n", result.execResult.output.c_str());
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

void checkTestMode(JoosC* joosc, const char* argv1) {
  profileSection("check test mode");

  int num = checkEnvForTest();
  if (!num) {
    if (argv1 && strlen(argv1) == 1) num = atoi(argv1);
  }
  if (!num) return;

  const char* assnBase = CUR_DIR_MARKER "tests/assignment_testcases";
  strdecl256(progFolder, "%s/a%d/", assnBase, num);

  vector<string> stdlib;
  if (num >= 2) {
    const char* libBase = CUR_DIR_MARKER "tests/stdlib";
    strdecl256(libFolder, "%s/%d.0/", libBase, num);
    getJavaFilesRecursive(stdlib, string(libFolder));
    stdlib.push_back(CUR_DIR_MARKER "tests/stdlib/IObject.java");
  }
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

  if (argc > 1)
	  gEntryPointFile = argv[1];

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

  const char* argv1 = nullptr;
  if (argc > 1) argv1 = argv[1];
  checkTestMode(&joosc, argv1);

  {
    profileSection("compile main");
    if (fileList.empty()) return 0;
    if (!gStandAloneMode) {
      fileList.push_back(CUR_DIR_MARKER "tests/stdlib/IObject.java");
    }
    return compileMain(&joosc, fileList);
  }
}
