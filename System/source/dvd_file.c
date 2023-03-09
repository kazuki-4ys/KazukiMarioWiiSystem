//from NewerSMBW
//https://github.com/Newer-Team/NewerSMBW/blob/cw/Kamek/src/fileload.cpp

#include "dvd_file.h"

void *LoadFile(FileHandle *handle, const char *name){
    void* (*EGG__Heap__alloc)(unsigned int, unsigned int, void*) = (void*)EGG_HEAP_ALLOC;
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
	//handle->filePtr = EGG__Heap__alloc(handle->length, 0x20, (void*)ARCHIVE_HEAP);
	handle->allocPtr = my_malloc(handle->length + 0x1F);
	unsigned int ptr = (unsigned int)handle->allocPtr;
	if(ptr & 0x1F){
		ptr = ptr & 0xFFFFFFE0;
		ptr += 0x20;
	}
	handle->filePtr = (void*)ptr;

	int ret = DVDReadPrio(&dvdhandle, handle->filePtr, handle->length, 0, 2);

	DVDClose(&dvdhandle);


	return handle->filePtr;
}

bool FreeFile(FileHandle *handle){
    void (*EGG__Heap__free)(void*, void*) = (void*)EGG_HEAP_FREE;
	if (!handle) return false;

	if (handle->filePtr) {
		//EGG__Heap__free(handle->filePtr, (void*)ARCHIVE_HEAP);
		my_free(handle->allocPtr);
	}

	handle->filePtr = 0;
	handle->length = 0;

	return true;
}