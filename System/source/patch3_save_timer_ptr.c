#include "common.h"

void patch3_save_timer_ptr(unsigned int *timerPtr){
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
	myMem->timerPtr = timerPtr;
    unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
    if(curLevelWorld == 1 && curLevelStage == 2 && myMem->timerPtr){
        *(myMem->timerPtr) = 0x3E61FC;
    }
}