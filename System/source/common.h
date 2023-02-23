#ifndef _COMMON_H_
#define _COMMON_H_

#define MY_MEM_PTR_PTR 0x800001B0
#define CUR_LEVEL_WORLD 0x803159bE
#define CUR_LEVEL_STAGE 0x803159bF

#define EVENT_TABLE 0x80429D98
#define CREATE_ACTOR 0x80064610
#define DVD_CONVERT_PATH_TO_ENTRY_NUM 0x801CA490
#define SPRINTF 0x802E15EC
#define STRCMP 0x802E18C4

#define true 1
#define false 0

typedef unsigned char bool;

typedef struct{
	float x;
	float y;
	float z;
}VEC3;

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

typedef struct{
	void *patch4CodeEnd;
	void *patch5CodeEnd;
    unsigned int *timerPtr;
	bool hijackBrstm;
	unsigned char myMusicId;
}myMemStruct;

void u32ToBytes(unsigned char *mem, unsigned int val);

unsigned int bytesToU32(unsigned char *mem);

unsigned int makeBranchInstructionByAddrDelta(int addrDelta);

void injectBranchPatch(void *targetAddr, void *codeStart, void *codeEnd, bool doIcInvalidate);

const char *getString6(void);
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

#endif//_COMMON_H_