#include "platform.h"

#ifdef __linux__

#include <locale.h>
#include <execinfo.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

void getCivicTime(CivicTimeInfo *info) {
  struct tm ts;
  time_t timePoint = time(nullptr);
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
  exit(42);
}

void platformInit() {
  signal(SIGSEGV, signalHandler);
  signal(SIGBUS, signalHandler);
  signal(SIGILL, signalHandler);
  setlocale(LC_ALL, "en_US.UTF-8");
}

FileType getFileType(const char *path) {
  struct stat statBuf;
  s32 value = stat(path, &statBuf);
  if (value)
    return FileTypeUnknown;
  if ((statBuf.st_mode & S_IFMT) == S_IFREG)
    return FileTypeRegular;
  if ((statBuf.st_mode & S_IFMT) == S_IFDIR)
    return FileTypeDirectory;
  return FileTypeUnknown;
}

s64 getFileSize(const char *path) {
  struct stat statBuf;
  s32 value = stat(path, &statBuf);
  if (value)
    return -1;
  return statBuf.st_size;
}

[[gnu::const]]
s32 getLeadingZeros(u64 val) {
  return __builtin_clzll(val);

}

#endif // __linux__

#ifdef _WIN32

#include <windows.h>
#include <fileapi.h>

#ifdef _MSC_VER
#include <intrin.h>
#pragma intrinsic(_BitScanReverse)
#endif

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void getCivicTime(CivicTimeInfo *) {
}

void platformInit() {
}

FileType getFileType(const char *path) {
  DWORD result = GetFileAttributesA(path);
  if (result & FILE_ATTRIBUTE_DIRECTORY)
    return FileTypeDirectory;
  if ((result & FILE_ATTRIBUTE_NORMAL) || (result & FILE_ATTRIBUTE_ARCHIVE))
    return FileTypeRegular;
  return FileTypeUnknown;
}

s64 getFileSize(const char *path) {
  WIN32_FILE_ATTRIBUTE_DATA attrData;
  DWORD result = GetFileAttributesExA(path, GetFileExInfoStandard, &attrData);
  if (!result)
    return -1;
  LARGE_INTEGER size;
  size.HighPart = attrData.nFileSizeHigh;
  size.LowPart = attrData.nFileSizeLow;
  return size.QuadPart;
}

void createDirectoryChain(const char *path) {
  fs::create_directories(fs::path(std::string(path)));
}

#ifdef _MSC_VER

s32 getLeadingZeros(u64 val) {
  unsigned long index;
  _BitScanReverse64(&index, val);
  return 63 - index;
}

#else

s32 getLeadingZeros(u64 val) {
  return __builtin_clzll(val);
}

#endif

#endif // _WIN32
