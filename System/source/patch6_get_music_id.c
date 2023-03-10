#include "common.h"
#include "mugendai_meikyu.h"

unsigned char after_course_getMusicForZone(unsigned char musicId, myMemStruct *myMem) {
	if(musicId == myMem->myMusicId)return myMem->gameSpoofMusicId;//前回と同じMusic IDなら何もしない
	if (musicId < 28 && (musicId == 0 || musicId > 4)){
		myMem->hijackBrstm = false;
		myMem->myMusicId = musicId;
		myMem->gameSpoofMusicId = musicId;
		return musicId;
	}
	myMem->hijackBrstm = true;
	myMem->myMusicId = musicId;
	if((musicId & 0x80) || musicId < 3){//最上位ビットが1ならマルチbrstmを使う
		if(myMem->gameSpoofMusicId == 1){
			myMem->gameSpoofMusicId = 2;
			return 2;//STRM_BGM_CHIKA.brstmのmusicId
		}
		myMem->gameSpoofMusicId = 1;
		return 1;//STRM_BGM_CHIJOU.brstmのmusicId
	}
	if(myMem->gameSpoofMusicId == 3){
		myMem->gameSpoofMusicId = 4;
		return 4;//athletic_fast_lr.n.32.brstmのmusicId
	}
	myMem->gameSpoofMusicId = 3;
	return 3;//BGM_SUICHU32.brstmのmusicId
}

unsigned char patch6_get_music_id(unsigned char musicId){
	myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return musicId;
	unsigned char curLevelWorld = *((unsigned char*)((void*)CUR_LEVEL_WORLD)) + 1;
    unsigned char curLevelStage = *((unsigned char*)((void*)CUR_LEVEL_STAGE)) + 1;

	//無限大迷宮用の処理
	if(curLevelWorld == 1 && curLevelStage == 2 && (myMem->curArea == 2 || myMem->curArea == 3)){
		doMugendaiMeikyuGame(myMem, myMem->curArea);
	}
	myMem->getMusicIdCalledCount++;
	return after_course_getMusicForZone(musicId, myMem);
}