#include "utility.h"

#include <time.h>

#include <filesystem>

#include "platform.h"
#include "profiler.h"

using namespace std;
namespace fs = std::filesystem;

void assertImpl(bool value, const char* str, ...) {
  if (!value) {
    LOGR("failed: %d (%s) ", value, str);
    UNIMPLEMENTED();
  }
}

void assertImpl_(bool value, const char* str, const char* fmt, ...) {
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

void strAppend(std::string* str, const char* fmt, ...) {
  char buffer[TWO_TO_EIGHT];
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buffer, TWO_TO_EIGHT, fmt, arg);
  va_end(arg);

  str->append(buffer);
}

void strFlushFILE(std::string* output, FILE* file) {
  fwrite(output->data(), output->length(), 1, file);
  output->clear();
}

void logImplRaw(const char* str, ...) {
  char logEntry[TWO_TO_EIGHT];
  va_list arg;
  va_start(arg, str);
  vsnprintf(logEntry, ARRAY_SIZE(logEntry), str, arg);
  va_end(arg);

  fprintf(stderr, "%s\n", logEntry);
}

void logImpl(const char* str,
             const char* file,
             s32 line,
             const char* func,
             ...) {
  CivicTimeInfo info;
  getCivicTime(&info);

  char logHeader[TWO_TO_EIGHT];
  snprintf(logHeader, ARRAY_SIZE(logHeader),
           "%d/%d %2d:%02d:%02d.%03d %s:%4d:\n", info.month, info.day,
           info.hour, info.minute, info.second, info.millisecond, file, line);

  fprintf(stderr, "%s", logHeader);

  char logEntry[TWO_TO_EIGHT];
  va_list arg;
  va_start(arg, func);
  vsnprintf(logEntry, ARRAY_SIZE(logEntry), str, arg);
  va_end(arg);

  fprintf(stderr, "%s", logEntry);
}

void globalInit() {
  srand(time(nullptr));
  platformInit();
}

void globalFini() {
	//profileReport();
#ifdef _MSC_VER
  fprintf(stderr, "Press enter to exit...\n");
  getchar();
#endif
}

std::unique_ptr<char[]> readEntireFile(const char* path, s32* size) {
  profileSection("read entire file");
  *size = 0;

  FILE* file = fopen(path, "rb");
  if (!file)
    return nullptr;

  fseek(file, 0, SEEK_END);
  s32 fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  std::unique_ptr<char[]> filePtr(new char[fileSize + 1]);

  fread(filePtr.get(), fileSize, 1, file);
  filePtr[fileSize] = '\0';

  *size = fileSize;
  fclose(file);
  return filePtr;
}

char* getPrintableChar(char c) {
  static char buffer[8];
  if (c <= 0x20)
    snprintf(buffer, 8, "\\x%x", c);
  else
    snprintf(buffer, 8, "%c", c);
  return buffer;
}

void getJavaFilesRecursive(vector<string>& fileList, const string& folder) {
	profileSection("get file recursive");
  auto it = fs::directory_iterator(folder);
  for (const auto& e : it) {
    if (fs::is_directory(e)) {
      getJavaFilesRecursive(fileList, e.path().string());
      continue;
    }

    if (fs::is_regular_file(e)) {
      if (e.path().extension().string() == ".java") {
        fs::path dup = e.path();
        fileList.push_back(dup.make_preferred().string());
      }
      continue;
    }
  }
}

[[noreturn]] void failedImpl(std::string str, const char *file, int line, const char *func) {
  logImplRaw("%s:%d %s: FAILED: %s", file, line, func, str.c_str());
  unimplementedImpl();
}
