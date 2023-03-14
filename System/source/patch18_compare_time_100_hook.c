#include "common.h"

bool patch18_compare_time_100_hook(void){
    unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
    if(curLevelWorld == 1 && curLevelStage == 3)return true;
    return false;
}