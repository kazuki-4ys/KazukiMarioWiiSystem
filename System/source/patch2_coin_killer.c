#include "common.h"

void patch2_coin_killer(void){
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
    unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
    if(curLevelWorld == 1 && curLevelStage == 1 && myMem->timerPtr){
        if(*(myMem->timerPtr) > 0xC8)*(myMem->timerPtr) = 0xC8;
    }
}