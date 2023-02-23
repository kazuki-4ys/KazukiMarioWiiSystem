#include "common.h"

unsigned char after_course_getMusicForZone(unsigned char musicId, myMemStruct *myMem) {
	if (musicId < 28){
		myMem->hijackBrstm = false;
		return musicId;
	}
	myMem->hijackBrstm = true;
	myMem->myMusicId = musicId;
	if(musicId & 0x80){//最上位ビットが1ならマルチbrstmを使う
		return 1;//STRM_BGM_CHIJOU.brstmのmusicId
	}
	return 3;//BGM_SUICHU32.brstmのmusicId
}

unsigned char patch6_get_music_id(unsigned char musicId){
	myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return musicId;
	return after_course_getMusicForZone(musicId, myMem);
}