#include "common.h"

bool patch5_coin_lakitu_spawner(void){
    unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
	if(curLevelStage == 1 && curLevelWorld == 1){
		return true;
	}
	return false;
}