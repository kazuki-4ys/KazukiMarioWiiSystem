#ifndef _COMMON_H_
#define _COMMON_H_

#include "actors.h"

#define MY_MEM_PTR_PTR 0x800001B0
#define CUR_LEVEL_WORLD 0x803159bE
#define CUR_LEVEL_STAGE 0x803159bF

#define EXIT_STAGE 0x801021e0
#define EVENT_TABLE 0x80429D98
#define OSREPORT 0x8015F540
#define ALLOC_FROM_GAME_HEAP 0x801626D0
#define MEM_ALLOC_FROM_ALLOCATOR 0x801D5350
#define CREATE_ACTOR 0x80064610
#define DVD_CONVERT_PATH_TO_ENTRY_NUM 0x801CA490
#define SPRINTF 0x802E15EC
#define STRCMP 0x802E18C4
#define MEMCPY 0x80004364
#define GENERATE_RANDOM_NUMBER 0x800B2EE0
#define UNKNOWN_STAGE_TIMER_STRUCT_PTR_PTR 0x80429D90

#define NULL 0

#define true 1
#define false 0

typedef unsigned char bool;

typedef struct{
	void *unk;
	unsigned int stageTimer;
}unknownStageTimerStruct;

enum PowerupStoreTypes {
	BEAT_LEVEL = 0, // Keeps powerups
	LOSE_LEVEL = 1, // Loses everything
	EXIT_LEVEL = 2  // Loses powerups, resets to previous state
};


enum Wipes {
	FADE_OUT = 0,
	CIRCLE_WIPE = 1,
	BOWSER_WIPE = 2,
	GOO_WIPE_DOWN = 3,	
	MARIO_WIPE = 4,
	CIRCLE_WIPE_SLOW = 5,
	GLITCH_GASM = 6
};

#define MAZE_SIZE_X 21
#define MAZE_SIZE_Y 21

enum mugendaiMeikyuTekiType{
	KURIBO = 0,
	NOKONOKO,
	METTO,
	TOGEZO,
	BOMUHEI,
	PATAPATA = 0x80,
	KIRA,
	KERONNPA,
	TERESA,
	INVALID_TEKI = 0xFF
};
#define NORM_MODE_MUGENDAI_MEIKYU_TEKI_COUNT 25
#define MUGENDAI_MEIKYU_TEKI_COUNT 50
#define MUGENDAI_MEIKYU_TEKI_TYPE_COUNT 5
#define MUGENDAI_MEIKYU_TEKI_TYPE_COUNT_TYU 4

typedef struct{
	unsigned int x;
	unsigned int y;
}mazePos;

typedef struct{
	mazePos pos;
	unsigned int type;
}mugendaiMeikyuTeki;

typedef struct{
	unsigned char *course2Bin;
	unsigned int course2BinSize;
	unsigned char *course2BgdatL1Bin;
	unsigned int course2BgdatL1BinSize;
	unsigned char *course2BgdatL2Bin;
	unsigned int course2BgdatL2BinSize;
	unsigned char *course3Bin;
	unsigned int course3BinSize;
	unsigned char *course3BgdatL1Bin;
	unsigned int course3BgdatL1BinSize;
	unsigned char *course3BgdatL2Bin;
	unsigned int course3BgdatL2BinSize;
	unsigned int curFloor;
	bool rawMazeData[MAZE_SIZE_Y][MAZE_SIZE_X];
	bool isInfinityMode;
	mazePos start;
	mazePos goal;
	mazePos item1;
	mazePos item2;
	mazePos starCoin;
	unsigned int item1Type;
	unsigned int item2Type;
	mugendaiMeikyuTeki teki[MUGENDAI_MEIKYU_TEKI_COUNT];
}mugendaiMeikyu;

typedef struct{
	void *patch4CodeEnd;
	void *patch5CodeEnd;
	void *allocator;
    unsigned int *timerPtr;
	bool hijackBrstm;
	unsigned char gameSpoofMusicId;
	unsigned char myMusicId;
	unsigned char *courseArcFile;
	mugendaiMeikyu mugenGame;
}myMemStruct;

float initializeFloat(unsigned int);
float abs(float);
unsigned int floatToInt(float);
void *my_malloc(unsigned int length);
void *my_malloc_via_allocator(unsigned int length);
Actor *CreateActor(unsigned short classID, int settings, VEC3 *pos, void* rot, char layer);
void setStageTimerRaw(int time);
unsigned int random(unsigned int max);
void u32ToBytes(unsigned char *mem, unsigned int val);
void u16ToBytes(unsigned char *mem, unsigned short val);
unsigned int bytesToU32(unsigned char *mem);
unsigned short bytesToU16(unsigned char *mem);
unsigned int makeBranchInstructionByAddrDelta(int addrDelta);
void injectBranchPatch(void *targetAddr, void *codeStart, void *codeEnd, bool doIcInvalidate);
void makeInArchiveCourseFileName(char *dest, unsigned int destSize, int area, int layer);
unsigned char *getARCChildFilePointer(unsigned char* arcFile, const char *targetFile, unsigned int *targetFileSize);
const char *getString6(void);
const char *getString7(void);
const char *getString8(void);
const char *getString9(void);
const char *getString10(void);
const char *getString11(void);
const char *getString12(void);
const char *getString13(void);
const char *getString14(void);
const char *getString15(void);
const char *getString16(void);
void ICInvalidateRange(void*, unsigned int);
void *get_patch1_run_1fr_asm(void);
void *get_patch1_run_1fr_asm_end(void);
void *get_patch2_coin_killer_asm(void);
void *get_patch2_coin_killer_asm_end(void);
void *get_patch3_save_timer_ptr_asm(void);
void *get_patch3_save_timer_ptr_asm_end(void);
void *get_patch4_dokan_coin_spawner_asm(void);
void *get_patch4_dokan_coin_spawner_asm_end(void);
void *get_patch5_coin_lakitu_spawner_asm(void);
void *get_patch5_coin_lakitu_spawner_asm_end(void);
void *get_patch6_get_music_id_asm(void);
void *get_patch6_get_music_id_asm_end(void);
void *get_patch7_brstm_hijacker_asm(void);
void *get_patch7_brstm_hijacker_asm_end(void);
void *get_patch8_auto_brsar_patch_asm(void);
void *get_patch8_auto_brsar_patch_asm_end(void);
void *get_patch9_arc_open_hook_asm(void);
void *get_patch9_arc_open_hook_asm_end(void);
void *get_patch10_mem_alloc_from_allocator_hook_asm(void);
void *get_patch10_mem_alloc_from_allocator_hook_asm_end(void);
void *get_patch11_bugmario_actorcreate_hook_asm(void);
void *get_patch11_bugmario_actorcreate_hook_asm_end(void);

#endif//_COMMON_H_