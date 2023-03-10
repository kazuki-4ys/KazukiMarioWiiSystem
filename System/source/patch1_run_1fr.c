#include "common.h"

void *get_patch4_dokan_coin_spawner_asm(void);
void *get_patch4_dokan_coin_spawner_asm_end(void);
void *get_patch5_coin_lakitu_spawner_asm(void);
void *get_patch5_coin_lakitu_spawner_asm_end(void);

void anotherRemoveTitleReplay(void){
    //from AnotherSMBW
    //https://github.com/Newer-Team/NewerSMBW/blob/cw/Kamek/anotherhax.yaml
    unsigned int writeNopStartAddr = 0x80781E8C;
    if(*((unsigned char*)((void*)0x80000007)) == 2)writeNopStartAddr = 0x80781ECC;
    for(unsigned int i = 0;i < 3;i++)u32ToBytes((void*)(writeNopStartAddr + i * 4), 0x60000000);
    ICInvalidateRange((void*)0x80781E80, 0x80);
}

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

Actor *FindActorByTypeAndSettings(unsigned short type, unsigned int settings){
    Actor *act = NULL;
    while(true){
        act = FindActorByType(type, act);
        if(!act)return NULL;
        if(act->settings == settings)return act;
    }
    return NULL;
}

void patch1_run_1fr(void){
    void(*ExitStage)(unsigned int, unsigned int, unsigned int, unsigned int) = (void*)EXIT_STAGE;
    myMemStruct **myMemPtr = ((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!(*myMemPtr)){//自分が使うためのメモリを確保
        *myMemPtr = (myMemStruct*)my_malloc_via_egg(sizeof(myMemStruct));
        (*myMemPtr)->patch4CodeEnd = get_patch4_dokan_coin_spawner_asm_end();
        (*myMemPtr)->patch5CodeEnd = get_patch5_coin_lakitu_spawner_asm_end();
        (*myMemPtr)->patch15CodeEnd = get_patch15_get_houdai_slide_search_killer_flag_asm_end();
        (*myMemPtr)->patch16CodeEnd = get_patch16_houdai_slide_generate_killer_hook_asm_end();
        //get_XXXXXXX_asm_end()はinjectBranchPatch()を呼び出した後には使えないので保存しておく
        (*myMemPtr)->bossClearStageExitTimer = -1;
    }
    //rev1
    if(bytesToU32((void*)0x80ABB080) == 0x4B5A9591)injectBranchPatch((void*)0x80abb080, get_patch4_dokan_coin_spawner_asm(), (*myMemPtr)->patch4CodeEnd, true);
    if(bytesToU32((void*)0x80ABC414) == 0x38600053)injectBranchPatch((void*)0x80abc414, get_patch5_coin_lakitu_spawner_asm(), (*myMemPtr)->patch5CodeEnd, true);
    if(bytesToU32((void*)0x80A4FB5C) == 0x38C00014)injectBranchPatch((void*)0x80A4FB5C, get_patch15_get_houdai_slide_search_killer_flag_asm(), (*myMemPtr)->patch15CodeEnd, true);
    if(bytesToU32((void*)0x80a4c960) == 0x4B617CB1)injectBranchPatch((void*)0x80a4c960, get_patch16_houdai_slide_generate_killer_hook_asm(), (*myMemPtr)->patch16CodeEnd, true);
    //rev2
    if(bytesToU32((void*)0x80ABB0A0) == 0x4B5A9571)injectBranchPatch((void*)0x80abb0a0, get_patch4_dokan_coin_spawner_asm(), (*myMemPtr)->patch4CodeEnd, true);
    if(bytesToU32((void*)0x80ABC434) == 0x38600053)injectBranchPatch((void*)0x80abc434, get_patch5_coin_lakitu_spawner_asm(), (*myMemPtr)->patch5CodeEnd, true);
    if(bytesToU32((void*)0x80A4FB7C) == 0x38C00014)injectBranchPatch((void*)0x80A4FB7C, get_patch15_get_houdai_slide_search_killer_flag_asm(), (*myMemPtr)->patch15CodeEnd, true);
    if(bytesToU32((void*)0x80a4c980) == 0x4B617C91)injectBranchPatch((void*)0x80a4c980, get_patch16_houdai_slide_generate_killer_hook_asm(), (*myMemPtr)->patch16CodeEnd, true);
    anotherRemoveTitleReplay();
    unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;
    myMemStruct *myMem = *myMemPtr;
    if(myMem->bossClearStageExitTimer == 0){
        myMem->bossClearStageExitTimer = -1;
        ExitStage(3, 0, BEAT_LEVEL, MARIO_WIPE);
    }
    if(myMem->bossClearStageExitTimer > 0){
        void* (*GetPlayerOrYoshi)(int) = (void*)GET_PLAYER_OR_YOSHI;
        void (*setAnimePlayStandardType)(void*, int) = (void*)SET_ANIME_PLAY_STANDARD_TYPE;
        for(int i = 0;i < 4;i++){
            void *ptr = GetPlayerOrYoshi(i);
            if(ptr)setAnimePlayStandardType(ptr, 2);
        }
        myMem->bossClearStageExitTimer--;
    }
    if(curLevelWorld == 1 && curLevelStage == 2){//1-2は制限時間無限&イベント64が作動したらコースクリア
        setStageTimerRaw(0x003E6988);
        if(isEventEnabled(64)){
            bossClear();
        }
    }
    if(curLevelWorld == 1 && curLevelStage == 3){//1-3
        if(myMem->getMusicIdCalledCount < 2)*((unsigned char*)((void*)0x80354C03)) |= 2;
        void *yoshi = (void*)FindActorByType(YOSHI, NULL);
        if(yoshi){
            if(*((unsigned char*)yoshi + 0xD5) == 0x78)setStageTimerRaw(40960);
        }
    }
    return;
}