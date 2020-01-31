#include <time.h>
#include <dirent.h>

#include "utility.h"
#include "platform.h"

using namespace std;

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

void strAppend(std::string *str, const char *fmt, ...) {
  char buffer[TWO_TO_EIGHT];
	va_list arg;
	va_start(arg, fmt);
	vsnprintf(buffer, TWO_TO_EIGHT, fmt, arg);
	va_end(arg);

  str->append(buffer);
}

void logImplRaw(const char *str, ...) {
	char logEntry[TWO_TO_EIGHT];
	va_list arg;
	va_start(arg, str);
	vsnprintf(logEntry, ARRAY_SIZE(logEntry), str, arg);
	va_end(arg);

	fprintf(stdout, "%s\n", logEntry);
}

void logImpl(const char *str, const char *file, s32 line, const char *func, ...) {
	CivicTimeInfo info;
	getCivicTime(&info);

	char logHeader[TWO_TO_EIGHT];
	snprintf(logHeader, ARRAY_SIZE(logHeader),
								 "%d/%d %2d:%02d:%02d.%03d %s:%4d:\n",
								 info.month, info.day, info.hour, info.minute, info.second,
								 info.millisecond, file, line);

	fprintf(stdout, "%s", logHeader);

	char logEntry[TWO_TO_EIGHT];
	va_list arg;
	va_start(arg, func);
	vsnprintf(logEntry, ARRAY_SIZE(logEntry), str, arg);
	va_end(arg);

	fprintf(stdout, "%s", logEntry);
}

void globalInit() {
	srand(time(nullptr));
	platformInit();
}

void globalFini() {

}

std::unique_ptr<char[]> readEntireFile(const char *path, s32 *size) {
	*size = 0;

	FILE *file = fopen(path, "rb");
	if (!file)
		return nullptr;

	fseek(file, 0, SEEK_END);
	s32 fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	std::unique_ptr<char[]> filePtr(new char[fileSize + 1]);

	fread(filePtr.get(), fileSize, 1, file);
	filePtr[fileSize] = '\0';

	*size = fileSize;
	return std::move(filePtr);
}

char *getPrintableChar(char c) {
	static char buffer[8];
	if (c <= 0x20)
		snprintf(buffer, 8, "\\x%x", c);
	else
		snprintf(buffer, 8, "%c", c);
	return buffer;
}

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
