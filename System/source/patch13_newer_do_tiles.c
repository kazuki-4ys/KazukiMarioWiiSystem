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

void patch13_newer_do_tiles(void* self){
    void (*OSReport)(const char*, ...) = (void*)OSREPORT;
    void (*snprintf)(char*, unsigned int, const char*, ...) = (void*)SNPRINTF;
    void* (*BgTexMng__LoadAnimTile)() = (void*)BG_TEX_MNG_LOAD_ANIM_TILE;
	AnimDef_Header *header;

    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
	
	header = (AnimDef_Header*)LoadFile(&(myMem->animTilesBin), getString17());
	
	if (!header) {
		OSReport(getString18());
		return;
	}
	
	if (header->magic != 0x4E575261){
		OSReport(getString19());
		FreeFile(&(myMem->animTilesBin));
		return;
	}
	
	AnimDef_Entry *entries = (AnimDef_Entry*)(header+1);
	
	for (int i = 0; i < header->entryCount; i++) {
		AnimDef_Entry *entry = &entries[i];
		char *name = (char*)myMem->animTilesBin.filePtr+entry->texNameOffset;
		char *frameDelays = (char*)myMem->animTilesBin.filePtr+entry->frameDelayOffset;
		
		char realName[0x40];
		snprintf(realName, 0x40, getString20(), name);
		
		void *blah = BgTexMng__LoadAnimTile(self, entry->tilesetNum, entry->tileNum, realName, frameDelays, entry->reverse);
	}
}