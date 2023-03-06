//from NewerSMBW
//https://github.com/Newer-Team/NewerSMBW/blob/cw/Kamek/src/animtiles.cpp

#include "common.h"
#include "dvd_file.h"

void patch14_newer_destroy_tiles(void){
	myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
	FreeFile(&(myMem->animTilesBin));
}