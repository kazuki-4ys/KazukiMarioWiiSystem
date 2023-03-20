#include "common.h"

void patch10_get_layout(void *r3, char *r4){
    int (*sprintf)(char * buf, const char * format, ...) = (void*)SPRINTF;
    int (*strcmp)(const char*, const char*) = (void*)STRCMP;
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
    if(strcmp(r4, getString23()) != 0)return;
    nw4r__lyt__TextBox_Struct *T_level_hint = EmbedLayoutBase_c__findTextBoxByName(r3, getString24());
    if(!T_level_hint)return;
    myMem->T_level_hint = T_level_hint;
    /*unsigned int *test = (void*)0x800001C0;
    *test = ((unsigned int)T_level_hint->vtable);*/
    unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
    if(curLevelWorld == 1 && curLevelStage == 1){
        nw4r__lyt__TextBox__SetString(T_level_hint, getU16String0(), 0);
    }else if(curLevelWorld == 1 && curLevelStage == 2 && (myMem->curArea == 2 || myMem->curArea == 3)){
        char tmpString[64];
        if(myMem->mugenGame.isInfinityMode){
            sprintf(tmpString, getString26(), myMem->mugenGame.curFloor);
        }else{
            sprintf(tmpString, getString25(), myMem->mugenGame.curFloor);
        }
        unsigned short *tmpString16 = utf8ToUtf16(tmpString);
        nw4r__lyt__TextBox__SetString(T_level_hint, tmpString16, 0);
        my_free_via_egg(tmpString16);
    }else if(curLevelWorld == 1 && curLevelStage == 2 && myMem->curArea == 4){
        nw4r__lyt__TextBox__SetString(T_level_hint, getU16String1(), 0);
    }else if(curLevelWorld == 1 && curLevelStage == 3){
        nw4r__lyt__TextBox__SetString(T_level_hint, getU16String2(), 0);
    }
}