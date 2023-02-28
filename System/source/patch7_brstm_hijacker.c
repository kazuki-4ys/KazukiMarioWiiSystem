#include "common.h"

const char *getString0(void);
const char *getString1(void);
const char *getString2(void);
const char *getString3(void);
const char *getString4(void);
const char *getString5(void);

unsigned int patch7_brstm_hijacker(char *path){
	int (*DVDConvertPathToEntrynum)(const char*) = (void*)DVD_CONVERT_PATH_TO_ENTRY_NUM;
	int (*sprintf)(char * buf, const char * format, ...) = (void*)SPRINTF;
	int (*strcmp)(const char*, const char*) = (void*)STRCMP;
	char myBrstmPath[128];
	myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return DVDConvertPathToEntrynum(path);
	if(!myMem->hijackBrstm)return DVDConvertPathToEntrynum(path);
	if(strcmp(path, getString0()) == 0 || strcmp(path, getString1()) == 0 || strcmp(path, getString13()) == 0 || strcmp(path, getString14()) == 0){//通常bgm
		switch(myMem->myMusicId){
			case 3:
				return DVDConvertPathToEntrynum(getString0());
			case 1:
				return DVDConvertPathToEntrynum(getString1());
			case 4:
				return DVDConvertPathToEntrynum(getString13());
			case 2:
				return DVDConvertPathToEntrynum(getString14());
			default:
				sprintf(myBrstmPath, getString4(), myMem->myMusicId);
				return DVDConvertPathToEntrynum(myBrstmPath);
		}
		return DVDConvertPathToEntrynum(myBrstmPath);
	}else if(strcmp(path, getString2()) == 0 || strcmp(path, getString3()) == 0 || strcmp(path, getString15()) == 0 || strcmp(path, getString16()) == 0){//倍速bgm
		switch(myMem->myMusicId){
			case 3:
				return DVDConvertPathToEntrynum(getString2());
			case 1:
				return DVDConvertPathToEntrynum(getString3());
			case 4:
				return DVDConvertPathToEntrynum(getString15());
			case 2:
				return DVDConvertPathToEntrynum(getString16());
			default:
				sprintf(myBrstmPath, getString5(), myMem->myMusicId);
				return DVDConvertPathToEntrynum(myBrstmPath);
		}
	}else{
		return DVDConvertPathToEntrynum(path);
	}
}