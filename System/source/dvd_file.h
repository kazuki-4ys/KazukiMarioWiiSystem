#ifndef _DVD_FILE_H_
#define _DVD_FILE_H_

#include "common.h"

void *LoadFile(FileHandle *handle, const char *name);
bool FreeFile(FileHandle *handle);

#endif//_DVD_FILE_H_