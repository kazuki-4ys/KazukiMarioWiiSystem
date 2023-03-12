#ifndef _DVD_FILE_H_
#define _DVD_FILE_H_

#include "common.h"

void *LoadFile(simpleFileStruct *handle, const char *name);
bool FreeFile(simpleFileStruct *handle);

#endif//_DVD_FILE_H_