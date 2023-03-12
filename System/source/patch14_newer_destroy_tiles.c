//from NewerSMBW
//https://github.com/Newer-Team/NewerSMBW/blob/cw/Kamek/src/animtiles.cpp

#include "common.h"
#include "dvd_file.h"

void freeAnimTilesBinInTilesetArc(myMemStruct *myMem, unsigned int index){
	if(myMem->animTilesBinInTilesetArc[index].filePtr){
		my_free_via_egg(myMem->animTilesBinInTilesetArc[index].filePtr);
		myMem->animTilesBinInTilesetArc[index].filePtr = NULL;
	}
}

void patch14_newer_destroy_tiles(void){
	myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
	for(unsigned int i = 0;i < 4;i++)freeAnimTilesBinInTilesetArc(myMem, i);
	FreeFile(&(myMem->animTilesBin));
}