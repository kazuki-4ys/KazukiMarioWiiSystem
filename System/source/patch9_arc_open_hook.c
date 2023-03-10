#include "common.h"
#include "mugendai_meikyu.h"

void patch9_arc_open_hook(unsigned char **r3, char fileName){
    unsigned char *arcFilePtr = *r3;//今読み込まれているarcファイルのポインタを取得
    if(!arcFilePtr)return;
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
    unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;

    //course1.binがあれば、このarcはステージファイル
    char inArcCourseFileName[128];
    makeInArchiveCourseFileName(inArcCourseFileName, 128, 1, -1);
    unsigned int course1BinSize;
    unsigned char *course1Bin = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &course1BinSize);
    if(!course1Bin){
        return;
    }
    myMem->courseArcFile = arcFilePtr;
    //無限大迷宮用の処理
    destroyMugendaiMeikyuGame(myMem);
    if(curLevelWorld == 1 && curLevelStage == 2)createMugendaiMeikyuGame(myMem);

    if(curLevelWorld == 1 && curLevelStage == 3)myMem->getMusicIdCalledCount = 0;
}