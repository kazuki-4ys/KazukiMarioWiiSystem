#include "common.h"
#include "actors.h"

Actor* patch16_houdai_slide_generate_killer_hook(unsigned short classID, int settings, VEC3 *pos, void* rot, char layer){
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return NULL;
    if(myMem->killerHoudaiSearch){
        return CreateActor(EN_SEARCH_KILLER, settings, pos, rot, layer);
    }else{
        return CreateActor(classID, settings, pos, rot, layer);
    }
    return NULL;
}