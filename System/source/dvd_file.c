//from NewerSMBW
//https://github.com/Newer-Team/NewerSMBW/blob/cw/Kamek/src/fileload.cpp

#include "dvd_file.h"

void *LoadFile(simpleFileStruct *handle, const char *name){
    int (*DVDConvertPathToEntrynum)(const char*) = (void*)DVD_CONVERT_PATH_TO_ENTRY_NUM;
    int (*DVDFastOpen)(int, DVDFileInfo*) = (void*)DVD_FAST_OPEN;
    int (*DVDReadPrio)(DVDFileInfo*, void*, unsigned int, unsigned int, unsigned int) = (void*)DVD_READ_PRIO;
    void (*DVDClose)(DVDFileInfo*) = (void*)DVD_CLOSE;

	int entryNum = DVDConvertPathToEntrynum(name);

	DVDFileInfo dvdhandle;
	if (!DVDFastOpen(entryNum, &dvdhandle)) {
		handle->filePtr = NULL;
		return NULL;
	}

	handle->length = dvdhandle.length;
	handle->filePtr = my_malloc_via_egg(handle->length);
	DVDReadPrio(&dvdhandle, handle->filePtr, handle->length, 0, 2);

	DVDClose(&dvdhandle);


	return handle->filePtr;
}

bool FreeFile(simpleFileStruct *handle){
	if (!handle) return false;
	if (handle->filePtr) {
		my_free_via_egg(handle->filePtr);
	}

	handle->filePtr = 0;
	handle->length = 0;

	return true;
}