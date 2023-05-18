#ifndef _COMMON_H_
#define _COMMON_H_

#include "actors.h"
#include "lyt.h"

#define MY_MEM_PTR_PTR 0x800001B0
#define CUR_LEVEL_WORLD 0x803159bE
#define CUR_LEVEL_STAGE 0x803159bF

#define ARCHIVE_HEAP 0x8042A16C
#define EGG_HEAP_ALLOC 0x802B8AD0
#define EGG_HEAP_FREE 0x802B8D80
#define EXIT_STAGE 0x801021e0
#define EVENT_TABLE 0x80429D98
#define OSREPORT 0x8015F540
#define FREE_FROM_GAME_HEAP 0x80162730
#define ALLOC_FROM_GAME_HEAP 0x801626D0
#define MEM_ALLOC_FROM_ALLOCATOR 0x801D5350
#define CREATE_ACTOR 0x80064610
#define FIND_ACTOR_BY_TYPE 0x80162B60
#define DVD_CONVERT_PATH_TO_ENTRY_NUM 0x801CA490
#define DVD_FAST_OPEN 0x801CA7A0
#define DVD_READ_PRIO 0x801CA930
#define DVD_CLOSE 0x801CA810
#define SPRINTF 0x802E15EC
#define STRCMP 0x802E18C4
#define MEMCPY 0x80004364
#define STRLEN 0x802DC4AC
#define GENERATE_RANDOM_NUMBER 0x800B2EE0
#define SNPRINTF 0x802E14F8
#define BG_TEX_MNG_LOAD_ANIM_TILE 0x80087B60
#define NW4R__SND__SOUND_HANDLE__SET_VOLUME 0x80267230
#define PLAY_SOUND_WITH_FUNCTION_B4 0x80194EA0
#define DETACH_SOUND 0x8027A010
#define SOUND_RELATED_CLASS 0x8042A1A8
#define STOP_BGM_MUSIC_REV1 0x807DB1C0
#define STOP_BGM_MUSIC_REV2 0x807DB1D0
#define GET_PLAYER_OR_YOSHI 0x8005FB90
#define SET_ANIME_PLAY_STANDARD_TYPE 0x80052290
#define MAKE_MARIO_ENTER_DEMO_MODE_REV1 0x807C7CE0
#define MAKE_MARIO_ENTER_DEMO_MODE_REV2 0x807C7CF0
#define UNKNOWN_STAGE_TIMER_STRUCT_PTR_PTR 0x80429D90

#define NULL 0

#define true 1
#define false 0

typedef unsigned char bool;

typedef struct{
	void *data;
}nw4r__snd__SoundHandle_Struct;

typedef struct{
    unsigned char unk0[0x34];
    unsigned int length;
    //0x38
    unsigned char unk1[4];
    //全部で0x3Cバイト
}DVDFileInfo;

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
	unsigned char *filePtr;
	unsigned int length;
}simpleFileStruct;

typedef struct{
	void *patch4CodeEnd;
	void *patch5CodeEnd;
	void *patch15CodeEnd;
	void *patch16CodeEnd;
	void *patch20CodeEnd;
	nw4r__lyt__TextBox_Struct *T_level_hint;
    unsigned int *timerPtr;
	bool hijackBrstm;
	bool isGameTimerRunning;
	unsigned char gameSpoofMusicId;
	unsigned char myMusicId;
	unsigned char *courseArcFile;
	unsigned int curArea;
	simpleFileStruct animTilesBinInTilesetArc[4];
	unsigned int getMusicIdCalledCount;
	mugendaiMeikyu mugenGame;
	simpleFileStruct animTilesBin;
	bool killerHoudaiSearch;
	bool isBossClearBgmPlayed;
	int bossClearStageExitTimer;
	int lastPlayCountdownSeTime;
}myMemStruct;

float initializeFloat(unsigned int);
float abs(float);
float intToFloat(int);
unsigned int floatToInt(float);
void *my_malloc(unsigned int length);
void my_free(void *ptr);
void *my_realloc(void *ptr, unsigned int size);
void *my_malloc_via_egg(unsigned int length);
void *my_free_via_egg(void *ptr);
unsigned short *utf8ToUtf16(char *_src);
void *my_realloc_via_egg(void *ptr, unsigned int size);
void *my_malloc_via_allocator(unsigned int length);
Actor *CreateActor(unsigned short classID, int settings, VEC3 *pos, void* rot, char layer);
Actor *FindActorByType(unsigned short classID, Actor *startFrom);
void setStageTimerRaw(int time);
unsigned int getStageTimerRaw(void);
unsigned int random(unsigned int max);
void nw4r__snd__SoundHandle__SetVolume(nw4r__snd__SoundHandle_Struct *self, float value, int count);
void PlaySoundWithFunctionB4(void *spc, nw4r__snd__SoundHandle_Struct *handle, int id, int unk);
void DetachSound(nw4r__snd__SoundHandle_Struct *ptr);
void StopBGMMusic(void);
void bossClear(void);
void u32ToBytes(unsigned char *mem, unsigned int val);
void u16ToBytes(unsigned char *mem, unsigned short val);
unsigned int bytesToU32(unsigned char *mem);
unsigned short bytesToU16(unsigned char *mem);
unsigned int makeBranchInstructionByAddrDelta(int addrDelta);
void injectBranchPatch(void *targetAddr, void *codeStart, void *codeEnd, bool doIcInvalidate);
void makeInArchiveCourseFileName(char *dest, unsigned int destSize, int area, int layer);
unsigned char *getARCChildFilePointer(unsigned char* arcFile, const char *targetFile, unsigned int *targetFileSize);
unsigned char *getCourseBinBlock(unsigned char *courseBin, unsigned int blockIndex, unsigned int *blockSize);
void getCurAreaTilesetsPath(myMemStruct *myMem, char *tilesetsPath, unsigned int tilesetPathLength);
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
const char *getString17(void);
const char *getString18(void);
const char *getString19(void);
const char *getString20(void);
const char *getString21(void);
const char *getString22(void);
const char *getString23(void);
const char *getString24(void);
const char *getString25(void);
const char *getString26(void);
const char *getString27(void);
const unsigned short *getU16String0(void);
const unsigned short *getU16String1(void);
const unsigned short *getU16String2(void);
unsigned char *getPipeFixNodeCalcBin(void);
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
void *get_patch10_get_layout_asm(void);
void *get_patch10_get_layout_asm_end(void);
void *get_patch9_arc_open_hook_asm_end(void);
void *get_patch11_bugmario_actorcreate_hook_asm(void);
void *get_patch11_bugmario_actorcreate_hook_asm_end(void);
void *get_patch12_sprite_208_block_actorcreate_hook_asm(void);
void *get_patch12_sprite_208_block_actorcreate_hook_asm_end(void);
void *get_patch13_newer_do_tiles_asm(void);
void *get_patch13_newer_do_tiles_asm_end(void);
void *get_patch14_newer_destroy_tiles_asm(void);
void *get_patch14_newer_destroy_tiles_asm_end(void);
void *get_patch15_get_houdai_slide_search_killer_flag_asm(void);
void *get_patch15_get_houdai_slide_search_killer_flag_asm_end(void);
void *get_patch16_houdai_slide_generate_killer_hook_asm(void);
void *get_patch16_houdai_slide_generate_killer_hook_asm_end(void);
void *get_patch17_get_cur_area_asm(void);
void *get_patch17_get_cur_area_asm_end(void);
void *get_patch18_compare_time_100_hook_asm(void);
void *get_patch18_compare_time_100_hook_asm_end(void);
void *get_daChengeBlock_c__doStuff_asm(void);
void *get_NEW_GetTileFromTileTable(void);
void *get_Special_end(void);
void *get_patch20_zurumode_itemstock99_asm(void);
void *get_patch20_zurumode_itemstock99_asm_end(void);

#endif//_COMMON_H_