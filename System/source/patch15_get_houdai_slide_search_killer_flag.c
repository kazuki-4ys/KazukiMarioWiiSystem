#include "common.h"
#include "actors.h"

void patch15_get_houdai_slide_search_killer_flag(Actor *act){
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
    if(act->field_0x80 == 1){
        myMem->killerHoudaiSearch = true;
    }else{
        myMem->killerHoudaiSearch = false;
    }
}