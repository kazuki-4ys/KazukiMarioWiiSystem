#include "common.h"

void patch17_get_cur_area(unsigned char *r3){
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
    myMem->curArea = bytesToU32(r3 + 4) + 1;
}