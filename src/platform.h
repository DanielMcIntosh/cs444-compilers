#pragma once

#include "utility.h"

typedef struct {
  s32 year;
  s32 month;
  s32 day;
  s32 hour;
  s32 minute;
  s32 second;
  s32 millisecond;
} CivicTimeInfo;

void getCivicTime(CivicTimeInfo *);
void platformInit();

enum FileType
{
  FileTypeDirectory,
  FileTypeRegular,   
};

FileType getFileType(const char *path);
s64 getFileSize(const char *path);



