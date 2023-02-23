#include "common.h"

void* patch4_dokan_coin_spawner(unsigned short classID, int settings, VEC3 *pos, char rot, char layer){
	void* (*CreateActor)(unsigned short classID, int settings, VEC3 *pos, char rot, char layer) = (void*)CREATE_ACTOR;
	unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
	if(curLevelStage != 1 || curLevelWorld != 1){
		return CreateActor(classID, settings, pos, rot, layer);
	}
	return CreateActor(403, 0, pos, 0, layer);
}