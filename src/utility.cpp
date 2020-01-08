#include "utility.h"

void assertImpl(bool value, const char *str, ...) {
  if (!value) {
    LOG("failed: %d (%s) ", value, str);
    UNIMPLEMENTED();
  }
}

void assertImpl_(bool value, const char *str, const char *fmt, ...) {
  if (!value) {
    LOG("failed: %d (%s) ", value, str);
    va_list arg;
    va_start(arg, fmt);
    vfprintf(stderr, fmt, arg);
    va_end(arg);
    UNIMPLEMENTED();
  }
}

void unimplementedImpl() {
  raise(SIGTRAP);
  abort();
}

void logImplRaw(const char *str, ...) {
  char logEntry[TWO_TO_EIGHT];
  va_list arg;
  va_start(arg, str);
  vsnprintf(logEntry, ARRAY_SIZE(logEntry), str, arg);
  va_end(arg);
  
  fprintf(stderr, "\n%s", logEntry);
}

void logImpl(const char *str, const char *file, s32 line, const char *func, ...) {
  CivicTimeInfo info;
  getCivicTime(&info);

  char logHeader[TWO_TO_EIGHT];
  snprintf(logHeader, ARRAY_SIZE(logHeader),
                 "\n%d/%d %2d:%02d:%02d.%03d %s:%4d:",
                 info.month, info.day, info.hour, info.minute, info.second,
                 info.millisecond, file, line);

  fprintf(stderr, "%s", logHeader);

  char logEntry[TWO_TO_EIGHT];
  va_list arg;
  va_start(arg, func);
  vsnprintf(logEntry, ARRAY_SIZE(logEntry), str, arg);
  va_end(arg);

  fprintf(stderr, "%s", logEntry);  
}

void getCivicTime(CivicTimeInfo *info) {
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

void signalHandler(int num) {
  void *frames[128];
  s32 numTrace = backtrace(frames, 128);
  fprintf(stderr, "\nReceived signal: %s\n", strsignal(num));
  backtrace_symbols_fd(frames, numTrace, STDERR_FILENO);
  fprintf(stderr, "Exiting\n");
  exit(1);
}

void globalInit() {
  setlocale(LC_ALL, "en_US.UTF-8");
  srand(time(0));
  signal(SIGSEGV, signalHandler);
  signal(SIGBUS, signalHandler);
  signal(SIGILL, signalHandler);    
}

void globalFini() {
  fprintf(stderr, "\n");
}
