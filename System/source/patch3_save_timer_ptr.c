#include "common.h"

void patch3_save_timer_ptr(unsigned int *timerPtr){
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
	myMem->timerPtr = timerPtr;
}