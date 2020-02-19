#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <memory>
#include <string>
#include <vector>

//
// handy macros
//

typedef uint8_t u8;
typedef uint32_t u32;
typedef int8_t s8;
typedef int32_t s32;
typedef float f32;
typedef double f64;
typedef uint64_t u64;
typedef int64_t s64;
typedef uint16_t u16;
typedef int16_t s16;

#define ARRAY_SIZE(_exp) (s32)(sizeof((_exp)) / sizeof((_exp)[0]))

#define TWO_TO_THREE 8
#define TWO_TO_FOUR 16
#define TWO_TO_FIVE 32
#define TWO_TO_SIX 64
#define TWO_TO_EIGHT 256
#define TWO_TO_NINE 512

#define strdecl(_name, _len, _format, ...) \
  char _name[_len];                        \
  snprintf(_name, _len, _format, __VA_ARGS__)
#define strdecl32(_name, _format, ...) \
  strdecl(_name, TWO_TO_FIVE, _format, __VA_ARGS__)
#define strdecl256(_name, _format, ...) \
  strdecl(_name, TWO_TO_EIGHT, _format, __VA_ARGS__)
#define strdecl512(_name, _format, ...) \
  strdecl(_name, TWO_TO_NINE, _format, __VA_ARGS__)

//
// assert and logging and others
//

#define ASSERT(_exp, ...) assertImpl((bool)(_exp), #_exp, ##__VA_ARGS__)
#define ASSERT2(_exp, _fmt, ...) \
  assertImpl_((bool)(_exp), #_exp, _fmt, ##__VA_ARGS__)
#define FAILED(_str) \
  failedImpl(_str, __FILE__, __LINE__, __func__)
#define LOG(fmt, ...) \
  logImpl((fmt), __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#define LOGR(fmt, ...) logImplRaw((fmt), ##__VA_ARGS__)
#define LOGI(_level, _fmt, ...) LOG("%*s" _fmt, _level, "", ##__VA_ARGS__)
#define LOGIR(_level, _fmt, ...) LOGR("%*s" _fmt, _level, "", ##__VA_ARGS__)

#ifndef _MSC_VER
#define LOG_RED(_fmt, ...) LOGR("\033[0;91m" _fmt "\033[0m", ##__VA_ARGS__)
#define LOG_GREEN(_fmt, ...) LOGR("\033[0;92m" _fmt "\033[0m", ##__VA_ARGS__)
#else
#define LOG_RED(_fmt, ...) LOGR("XXXXX " _fmt, ##__VA_ARGS__)
#define LOG_GREEN(_fmt, ...) LOGR("      " _fmt, ##__VA_ARGS__)
#endif

#define UNIMPLEMENTED unimplementedImpl
[[noreturn]] void unimplementedImpl();

//
// Log and asserts
//

[[gnu::format(printf, 1, 5)]] void logImpl(const char* str,
                                           const char* file,
                                           s32 line,
                                           const char* func,
                                           ...);

[[gnu::format(printf, 1, 2)]] void logImplRaw(const char* str, ...);
[[gnu::format(printf, 2, 3)]] void assertImpl(bool val, const char* str, ...);
[[gnu::format(printf, 3, 4)]] void assertImpl_(bool val,
                                               const char* str,
                                               const char* fmt,
                                               ...);
[[noreturn]] void failedImpl(std::string str, const char* file, int line, const char* func);

[[gnu::format(printf, 2, 3)]] void strAppend(std::string* str,
                                             const char* fmt,
                                             ...);
void strFlushFILE(std::string* str, FILE* file);
char* getPrintableChar(char c);

void globalInit();
void globalFini();

//
// File operations
//

std::unique_ptr<char[]> readEntireFile(const char* path, s32* size);
void getJavaFilesRecursive(std::vector<std::string>& fileList,
                           const std::string& folder);

#pragma once

// Combine lambdas into a visitor.
// Taken from https://en.cppreference.com/w/cpp/utility/variant/visit
template <class... Ts>
struct visitor : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
visitor(Ts...)->visitor<Ts...>;
