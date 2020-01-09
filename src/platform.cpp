#include "platform.h"

#ifdef __linux__

#include <locale.h>
#include <execinfo.h>
#include <signal.h>
#include <time.h>

void getCivicTime(CivicTimeInfo *) {
  struct tm ts;
  time_t timePoint = time(0);
  localtime_r(&timePoint, &ts);

  info->year = ts.tm_year + 1900;
  info->month = ts.tm_mon;
  info->day = ts.tm_mday;
  info->hour = ts.tm_hour;
  info->minute = ts.tm_min;
  info->second = ts.tm_sec;
  info->millisecond = 0;  
}

[[noreturn]] void signalHandler(int num) {
  void *frames[128];
  s32 numTrace = backtrace(frames, 128);
  fprintf(stderr, "\nReceived signal: %s\n", strsignal(num));
  backtrace_symbols_fd(frames, numTrace, STDERR_FILENO);
  fprintf(stderr, "Exiting\n");
  exit(1);
}

void platformInit() {
  signal(SIGSEGV, signalHandler);
  signal(SIGBUS, signalHandler);
  signal(SIGILL, signalHandler);
  setlocale(LC_ALL, "en_US.UTF-8");  
}

FileType getFileType(const char *path) {
  
}

s64 getFileSize(const char *path) {
  
}

#endif // __linux__

#ifdef _WIN32

void getCivicTime(CivicTimeInfo *) {  
}

void platformInit() {
}

FileType getFileType(const char *path) {
  
}

s64 getFileSize(const char *path) {
  
}

#endif // _WIN32
