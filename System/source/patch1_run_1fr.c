#include "common.h"

void *get_patch4_dokan_coin_spawner_asm(void);
void *get_patch4_dokan_coin_spawner_asm_end(void);
void *get_patch5_coin_lakitu_spawner_asm(void);
void *get_patch5_coin_lakitu_spawner_asm_end(void);


/*bool isEventEnabled(unsigned char eventId){//特定のイベントが作動したかチェックEvent IDは最大64まで((多分)
    if(eventId == 0 || eventId > 64)return false;//0は常に無効(多分)
    unsigned char *eventTable = *((unsigned char**)((void*)EVENT_TABLE));
    if(!eventTable)return false;
    unsigned char internalEventId = eventId - 1;
    unsigned char eventIdFlag = 1 << (internalEventId & 7);
    unsigned char eventIdFlagByteIndex = 7 - (internalEventId >> 3);
    if((*(eventTable + eventIdFlagByteIndex) & eventIdFlag) != 0)return true;
    return false;
}*/

void patch1_run_1fr(void){
    void(*ExitStage)(unsigned int, unsigned int, unsigned int, unsigned int) = (void*)0x801021e0;
    void*(*AllocFromGameHeap1)(unsigned int) = (void*)0x801626D0;
    myMemStruct **myMemPtr = ((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!(*myMemPtr)){//first, we need to allocate memory fou us.
        *myMemPtr = (myMemStruct*)AllocFromGameHeap1(sizeof(myMemStruct));
        (*myMemPtr)->patch4CodeEnd = get_patch4_dokan_coin_spawner_asm_end();
        (*myMemPtr)->patch5CodeEnd = get_patch5_coin_lakitu_spawner_asm_end();
        //get_XXXXXXX_asm_end()はinjectBranchPatch()を呼び出した後には使えないので保存しておく
    }
    //rev1
    if(bytesToU32((void*)0x80ABB07C) == 0xD0010010)injectBranchPatch((void*)0x80abb080, get_patch4_dokan_coin_spawner_asm(), (*myMemPtr)->patch4CodeEnd, true);
    if(bytesToU32((void*)0x80ABC414) == 0x38600053)injectBranchPatch((void*)0x80abc414, get_patch5_coin_lakitu_spawner_asm(), (*myMemPtr)->patch5CodeEnd, true);
    //rev2
    if(bytesToU32((void*)0x80ABB09C) == 0xD0010010)injectBranchPatch((void*)0x80abb0a0, get_patch4_dokan_coin_spawner_asm(), (*myMemPtr)->patch4CodeEnd, true);
    if(bytesToU32((void*)0x80ABC434) == 0x38600053)injectBranchPatch((void*)0x80abc434, get_patch5_coin_lakitu_spawner_asm(), (*myMemPtr)->patch5CodeEnd, true);
    //if(isEventEnabled(3))ExitStage(3, 0, BEAT_LEVEL, MARIO_WIPE);
    //myMemStruct *myMem = *myMemPtr;
    return;
}