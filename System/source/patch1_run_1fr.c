#include "common.h"

void *get_patch4_dokan_coin_spawner_asm(void);
void *get_patch4_dokan_coin_spawner_asm_end(void);
void *get_patch5_coin_lakitu_spawner_asm(void);
void *get_patch5_coin_lakitu_spawner_asm_end(void);

bool isEventEnabled(unsigned char eventId){//特定のイベントが作動したかチェックEvent IDは最大64まで((多分)
    if(eventId == 0 || eventId > 64)return false;//0は常に無効(多分)
    unsigned char *eventTable = *((unsigned char**)((void*)EVENT_TABLE));
    if(!eventTable)return false;
    unsigned char internalEventId = eventId - 1;
    unsigned char eventIdFlag = 1 << (internalEventId & 7);
    unsigned char eventIdFlagByteIndex = 7 - (internalEventId >> 3);
    if((*(eventTable + eventIdFlagByteIndex) & eventIdFlag) != 0)return true;
    return false;
}

void patch1_run_1fr(void){
    void(*ExitStage)(unsigned int, unsigned int, unsigned int, unsigned int) = (void*)EXIT_STAGE;
    void*(*AllocFromGameHeap1)(unsigned int) = (void*)0x801626D0;
    myMemStruct **myMemPtr = ((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!(*myMemPtr)){//first, we need to allocate memory fou us.
        *myMemPtr = (myMemStruct*)AllocFromGameHeap1(sizeof(myMemStruct));
        (*myMemPtr)->patch4CodeEnd = get_patch4_dokan_coin_spawner_asm_end();
        (*myMemPtr)->patch5CodeEnd = get_patch5_coin_lakitu_spawner_asm_end();
        (*myMemPtr)->patch15CodeEnd = get_patch15_get_houdai_slide_search_killer_flag_asm_end();
        (*myMemPtr)->patch16CodeEnd = get_patch16_houdai_slide_generate_killer_hook_asm_end();
        //get_XXXXXXX_asm_end()はinjectBranchPatch()を呼び出した後には使えないので保存しておく
    }
    //rev1
    if(bytesToU32((void*)0x80ABB07C) == 0xD0010010)injectBranchPatch((void*)0x80abb080, get_patch4_dokan_coin_spawner_asm(), (*myMemPtr)->patch4CodeEnd, true);
    if(bytesToU32((void*)0x80ABC414) == 0x38600053)injectBranchPatch((void*)0x80abc414, get_patch5_coin_lakitu_spawner_asm(), (*myMemPtr)->patch5CodeEnd, true);
    //rev2
    if(bytesToU32((void*)0x80ABB09C) == 0xD0010010)injectBranchPatch((void*)0x80abb0a0, get_patch4_dokan_coin_spawner_asm(), (*myMemPtr)->patch4CodeEnd, true);
    if(bytesToU32((void*)0x80ABC434) == 0x38600053)injectBranchPatch((void*)0x80abc434, get_patch5_coin_lakitu_spawner_asm(), (*myMemPtr)->patch5CodeEnd, true);
    if(bytesToU32((void*)0x80A4FB7C) == 0x38C00014)injectBranchPatch((void*)0x80A4FB7C, get_patch15_get_houdai_slide_search_killer_flag_asm(), (*myMemPtr)->patch15CodeEnd, true);
    if(bytesToU32((void*)0x80a4c980) == 0x4B617C91)injectBranchPatch((void*)0x80a4c980, get_patch16_houdai_slide_generate_killer_hook_asm(), (*myMemPtr)->patch16CodeEnd, true);
    unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
    myMemStruct *myMem = *myMemPtr;
    if(curLevelWorld == 1 && curLevelStage == 2){//1-2は制限時間無限&イベント64が作動したらコースクリア
        setStageTimerRaw(0x003E6988);
        if(isEventEnabled(64))ExitStage(3, 0, BEAT_LEVEL, MARIO_WIPE);;
    }
    return;
}