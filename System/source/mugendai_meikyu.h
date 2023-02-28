#ifndef _MUGENDAI_MEIKYU_H_
#define _MUGENDAI_MEIKYU_H_

#include "common.h"

#define BOSS_FLOOR 5

#define MAZE_START_X_POS 20
#define MAZE_START_Y_POS 16

#define MAZE_BLOCK_X_SIZE 4
#define MAZE_BLOCK_Y_SIZE 4

#define GOOMBA_SPRITE_ID 20
#define KOOPA_TROOPA_SPRITE_ID 57
#define TEMPLATE_SPRITE_ID 40

#define MAZE_KABE_1_TYPE 32
#define MAZE_KABE_2_TYPE 33

#define NORM_MODE_TYPE 207
#define INFI_MODE_TYPE 208
#define F_TYPE 113
#define NUM_START_X 12
#define NUM_START_Y 104

#define BGDAT_OBJECT_SIZE 0xA
#define BGDAT_OBJECT_TYPE_OFFSET 1
#define BGDAT_OBJECT_X_OFFSET 2
#define BGDAT_OBJECT_Y_OFFSET 4

bool isSameMazePos(mazePos *a, mazePos *b);
unsigned int samePosTekiType(mugendaiMeikyu *game, mazePos *mp);
unsigned char *findObjectByPosFromBgdat(unsigned int x, unsigned int y, unsigned char *bgdat, unsigned int bgdatSize);
unsigned char *findObjectByTypeFromBgdat(unsigned char type, unsigned char *bgdat, unsigned int bgdatSize);
void applyMazeToBgdatL1(mugendaiMeikyu *game, unsigned char *bgdatL1, unsigned int bgdatL1Size);
void createMugendaiMeikyuGame(myMemStruct *myMem);
void destroyMugendaiMeikyuGame(myMemStruct *myMem);
void doMugendaiMeikyuGame(myMemStruct *myMem, unsigned int curArea);

#endif//_MUGENDAI_MEIKYU_H_