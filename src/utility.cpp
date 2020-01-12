#include <time.h>

#include "utility.h"
#include "platform.h"

void assertImpl(bool value, const char *str, ...) {
  if (!value) {
    LOGR("failed: %d (%s) ", value, str);
    UNIMPLEMENTED();
  }
}

void assertImpl_(bool value, const char *str, const char *fmt, ...) {
  if (!value) {
    LOGR("failed: %d (%s) ", value, str);
    va_list arg;
    va_start(arg, fmt);
    vfprintf(stderr, fmt, arg);
    va_end(arg);
    UNIMPLEMENTED();
  }
}

[[noreturn]] void unimplementedImpl() {
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

void globalInit() {
  srand(time(0));
  platformInit();
}

void globalFini() {
  fprintf(stderr, "\n");
}

void readEntireFile(const char *path, char **content, s32 *size) {
  *content = 0;
  *size = 0;
  
  FILE *file = fopen(path, "rb");
  if (!file)
    return;

  fseek(file, 0, SEEK_END);
  s32 fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *filePtr = (char *)malloc(fileSize + 1);
  
  fread(filePtr, fileSize, 1, file);
  filePtr[fileSize] = 0;
  
  *content = filePtr;
  *size = fileSize;
}
