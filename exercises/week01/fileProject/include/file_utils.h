#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <iosfwd>

int getFileLineCount(const char* file_path);

std::streampos getFileByteCount(const char* file_path);

#endif