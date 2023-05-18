#include "game.h"

#ifndef _DA_CHANGE_BLOCK_H_
#define _DA_CHANGE_BLOCK_H_

#define BG_GM_BASE__GET_POINTER_TO_TILE 0x80077520
#define BG_GM_BASE__PLACE_TILE 0x80077860
#define D_FLAG_MGR_C__INSTANCE 0x80429D98
#define D_STAGE_ACTOR_C__CREATING_FLAG_MASK 0x80429A40
#define D_BG_GM_C__INSTANCE 0x80429AF0
#define D_EFFECT_BREAK_MGR_C__INSTANCE 0x80429C08

typedef enum { Destroy, Create }daChengeBlock_c__Action;
typedef enum { Fill, CheckerA, CheckerB }daChengeBlock_c__Pattern;


typedef struct{
    dStageActor_c_Struct s;
    unsigned int _394;
	unsigned long long initialFlags;

	int width, height;
	daChengeBlock_c__Action action;
	int blockType;
    int isPermanent;
    daChengeBlock_c__Pattern pattern;
	unsigned short hasTriggered;
    unsigned char pad0[2];
	unsigned int _3BC;

}__attribute__ ((packed)) daChengeBlock_c_Struct;

unsigned short *BgGmBase__getPointerToTile(BgGmBase_Struct *self, int x, int y, int layer, int *pBlockNum, bool unused);
void BgGmBase__placeTile(BgGmBase_Struct *self, unsigned short x, unsigned short y, int layer, int tile);

#endif//_DA_CHANGE_BLOCK_H_