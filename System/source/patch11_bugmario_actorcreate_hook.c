#include "common.h"
#include "mugendai_meikyu.h"
#include "actors.h"

void convertPos3ToMazePos(VEC3 *pos, mazePos *mp){
	unsigned int vec3X = floatToInt(pos->x);
	unsigned int vec3Y = floatToInt(abs(pos->y));
	unsigned int reggieBlockX = vec3X / 16;
	unsigned int reggieBlockY = vec3Y / 16;
	mp->x = (reggieBlockX - MAZE_START_X_POS) / MAZE_BLOCK_X_SIZE;
	mp->y = (reggieBlockY - MAZE_START_Y_POS) / MAZE_BLOCK_Y_SIZE;
}


void* patch11_bugmario_actorcreate_hook(unsigned short classID, int settings, VEC3 *pos, char rot, char layer){
	void* (*CreateActor)(unsigned short classID, int settings, VEC3 *pos, char rot, char layer) = (void*)CREATE_ACTOR;
	myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
	unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
	if(classID == EN_KURIBO && curLevelWorld == 1 && curLevelStage == 2 && myMem){
		mazePos mp;
		convertPos3ToMazePos(pos, &mp);
		unsigned int tekiType = samePosTekiType(&(myMem->mugenGame), &mp);
		if(tekiType == INVALID_TEKI)return CreateActor(747, 0, pos, rot, layer);
		switch(tekiType){
			case NOKONOKO:
				return CreateActor(EN_NOKONOKO, 1, pos, rot, layer);
			case METTO:
				return CreateActor(EN_MET, 0, pos, rot, layer);
			case TOGEZO:
				return CreateActor(EN_TOGEZO, 0, pos, rot, layer);
			case BOMUHEI:
				return CreateActor(EN_BOMHEI, 0, pos, rot, layer);
			case KIRA:
				return CreateActor(EN_KILLER, 0, pos, rot, layer);
			case PATAPATA:
				return CreateActor(EN_PATAPATA, 0x11, pos, rot, layer);
			case TERESA:
				return CreateActor(EN_KERONPA, 0, pos, rot, layer);
			case KERONNPA:
				return CreateActor(EN_TERESA, 0, pos, rot, layer);
			default:
				return CreateActor(EN_KURIBO, settings, pos, rot, layer);
		}
	}
	return CreateActor(classID, settings, pos, rot, layer);
}