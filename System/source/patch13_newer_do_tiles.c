//from NewerSMBW
//https://github.com/Newer-Team/NewerSMBW/blob/cw/Kamek/src/animtiles.cpp

#include "common.h"
#include "dvd_file.h"

typedef struct{
	unsigned int magic;
	unsigned int entryCount;
}AnimDef_Header;

typedef struct{
	unsigned short texNameOffset;
	unsigned short frameDelayOffset;
	unsigned short tileNum;
	unsigned char tilesetNum;
	unsigned char reverse;
}AnimDef_Entry;

void getCurAreaTilesetsPath(myMemStruct *myMem, char *tilesetsPath, unsigned int tilesetPathLength){
    int (*sprintf)(char * buf, const char * format, ...) = (void*)SPRINTF;
    unsigned int (*strlen)(char*) = (void*)STRLEN;
    char course[32];
    makeInArchiveCourseFileName(course, 32, myMem->curArea, -1);
    unsigned int courseBinSize;
    unsigned char *courseBin = getARCChildFilePointer(myMem->courseArcFile, course, &courseBinSize);
    if(!courseBin)return;
    unsigned int block0Size;
    unsigned char *block0 = getCourseBinBlock(courseBin, 0, &block0Size);//block0取得ok
    for(unsigned int i = 0;i < 4;i++){
        if(strlen(block0 + i * 0x20) == 0)continue;
        sprintf(tilesetsPath + i * tilesetPathLength, getString21(), block0 + i * 0x20);
    }
}

void getAnimTilesBinInTilesetArc(myMemStruct *myMem, char *tilesetsPath, unsigned int tilesetPathLength, unsigned int index){
	void *(*memcpy)(void*, void*, unsigned int) = (void*)MEMCPY;
	myMem->animTilesBinInTilesetArc[index].filePtr = NULL;
	simpleFileStruct arcFile;
	LoadFile(&arcFile, tilesetsPath + index * tilesetPathLength);
	if(!arcFile.filePtr)return;
	unsigned int animTilesBinSize;
	unsigned char *animTilesBin;
	animTilesBin = getARCChildFilePointer(arcFile.filePtr, getString22(), &animTilesBinSize);
	if(!animTilesBin){
		FreeFile(&arcFile);
		return;
	}
	myMem->animTilesBinInTilesetArc[index].filePtr = my_malloc_via_egg(animTilesBinSize);
	myMem->animTilesBinInTilesetArc[index].length = animTilesBinSize;
	memcpy(myMem->animTilesBinInTilesetArc[index].filePtr, animTilesBin, animTilesBinSize);
	FreeFile(&arcFile);
}

void handleNWRA(void* self, unsigned char *nwra){
    void (*OSReport)(const char*, ...) = (void*)OSREPORT;
    void (*snprintf)(char*, unsigned int, const char*, ...) = (void*)SNPRINTF;
    void* (*BgTexMng__LoadAnimTile)(void *self, int tileset, short tile, char *name, char *delays, char reverse) = (void*)BG_TEX_MNG_LOAD_ANIM_TILE;
    if(bytesToU32(nwra) != 0x4E575261){
        OSReport(getString19());
		return;
    }
    unsigned int count = bytesToU32(nwra + 4);
    for (int i = 0; i < count; i++) {
		char *name = (char*)(nwra + bytesToU16(nwra + 8 + i * 8));
		char *frameDelays = (char*)(nwra + bytesToU16(nwra + 8 + i * 8 + 2));
		char realName[0x40];
		snprintf(realName, 0x40, getString20(), name);
		short tileNum = (short)bytesToU16(nwra + 8 + i * 8 + 4);
        char tilesetNum = *(nwra + 8 + i * 8 + 6);
        char reverse = *(nwra + 8 + i * 8 + 7);
		BgTexMng__LoadAnimTile(self, tilesetNum, tileNum, realName, frameDelays, reverse);
	}
}

void patch13_newer_do_tiles(void* self){
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
	unsigned char *resAnimTilesBin = LoadFile(&(myMem->animTilesBin), getString17());
	if(resAnimTilesBin)handleNWRA(self, resAnimTilesBin);
	/*char tilesetsPath[256];
	getCurAreaTilesetsPath(myMem, tilesetsPath, 64);
	for(unsigned int i = 0;i < 4;i++){
		getAnimTilesBinInTilesetArc(myMem, tilesetsPath, 64, i);
		if(myMem->animTilesBinInTilesetArc[i].filePtr)handleNWRA(self, myMem->animTilesBinInTilesetArc[i].filePtr);
	}*/
}