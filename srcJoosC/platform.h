#pragma once

#include "utility.h"

struct CivicTimeInfo {
  s32 year;
  s32 month;
  s32 day;
  s32 hour;
  s32 minute;
  s32 second;
  s32 millisecond;
};

void getCivicTime(CivicTimeInfo *);
void platformInit();

enum FileType
  {
   FileTypeUnknown,
   FileTypeDirectory,
   FileTypeRegular,
  };

FileType getFileType(const char *path);
s64 getFileSize(const char *path);
void createDirectoryChain(const char *path);
[[gnu::const]]
s32 getLeadingZeros(u64 val);
