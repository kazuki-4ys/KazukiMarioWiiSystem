#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"

#define BIG_HANA_FIREBALL 0x809B3350

typedef float Mtx[3][4];

typedef struct{
	float x;
	float y;
	float z;
}__attribute__ ((packed)) Vec;

typedef struct{
	float x;
	float y;
}__attribute__ ((packed)) Vec2;

typedef struct{
	short x;
	short y;
	short z;
}__attribute__ ((packed)) s16Vec;

typedef struct LinkListEntry{
	struct LinkListEntry *first;
	struct LinkListEntry *last;
	void *owned_obj;
}__attribute__ ((packed)) LinkListEntry;

typedef struct{
    LinkListEntry s;
	unsigned short order;
	unsigned short _;
}__attribute__ ((packed)) OrderedLinkListEntry;

typedef struct TreeNode{
	struct TreeNode *parent;
	struct TreeNode *child;
	struct TreeNode *prev;
	struct TreeNode *next;
	void *owned_obj;
}__attribute__ ((packed)) TreeNode;

typedef struct{
    unsigned int id;
    unsigned int settings;
    unsigned short name;
	unsigned char _A;
	unsigned char _B;
    unsigned char _C;
	unsigned char _D;
	unsigned char base_type;
	unsigned char _F;
	TreeNode link_connect;
	OrderedLinkListEntry link_execute;
	OrderedLinkListEntry link_draw;
	LinkListEntry link_IDlookup;
	unsigned int _50;
	unsigned int _54;
	unsigned int _58;
	unsigned int heap;
    void *vtable;
}__attribute__ ((packed)) fBase_c_Struct;

typedef struct{
    fBase_c_Struct s;
    unsigned int _64;
    const char *explanation_string;
	const char *name_string;
}__attribute__ ((packed)) dBase_c_Struct;

typedef struct{
    dBase_c_Struct s;
    LinkListEntry link_actor;
	Mtx matrix;
	Vec pos;
	Vec last_pos;
	Vec pos_delta;
	Vec pos_delta2;
	Vec scale;
	Vec speed;
	Vec max_speed;
	s16Vec rot;
	s16Vec _106;
	unsigned int _10C;
	unsigned int _110;
	float y_speed_inc;
	unsigned int _118;
	float x_speed_inc;
	unsigned int _120;
	bool visible;
}__attribute__ ((packed)) dActor_c_Struct;

typedef struct{
	float xDistToCenter;
	float yDistToCenter;
	float xDistToEdge;
	float yDistToEdge;
	unsigned char category1;
	unsigned char category2;
	unsigned char pad0[2];
	unsigned int bitfield1;
	unsigned int bitfield2;
	unsigned short unkShort1C;
	unsigned char pad1[2];
	void* callback;
}__attribute__ ((packed)) ActivePhysics_Info;//size must be 0x24

struct dStageActor_c_Struct;

typedef struct ActivePhysics_Struct{
	void *vtable;
	struct dStageActor_c_Struct *owner;
	unsigned int _8;
	unsigned int _C;
	struct ActivePhysics_Struct *listPrev, *listNext;
	unsigned int _18;
	ActivePhysics_Info info;
	float trpValue0, trpValue1, trpValue2, trpValue3;
	float firstFloatArray[8];//at 0x50
	float secondFloatArray[8];//at 0x70
	Vec2 positionOfLastCollision;//at 0x90
	unsigned short result1;
	unsigned short result2;
	unsigned short result3;
	unsigned char collisionCheckType;
	unsigned char chainlinkMode;
	unsigned char layer;
	unsigned char someFlagByte;
	unsigned char isLinkedIntoList;
	unsigned char pad0;
}__attribute__ ((packed)) ActivePhysics_Struct;//size must be 0xA4

typedef struct Physics_Struct{
	dActor_c_Struct *owner;
	struct Physics_Struct *next, *prev;
	unsigned int _C, _10, _14, _18, _1C, _20, _24, _28, _2C, _30, _34;
	void *somePlayer;
	unsigned int _3C;
	void *otherCallback1, *otherCallback2, *otherCallback3;
	void *callback1, *callback2, *callback3;
	float lastX, lastY;
	//Unknown unkArray[4];//at 0x60
	unsigned char unk[0x20];//at 0x60
	//at 0x80
	float x, y;
	float _88, _8C;
	float diameter;
	Vec lastActorPosition;
	float _A0, _A4, last_A0, last_A4, _B0, _B4;
	unsigned int _B8;
	short *ptrToRotationShort;
	short currentRotation;
	short rotDiff;
	short rotDiffAlt;
	unsigned char pad0[2];
	unsigned int isRound;
	unsigned int _CC;
	// Flag 4 is icy
	unsigned int flagsMaybe;
	unsigned int _D4, _D8;
	unsigned char isAddedToList, _DD, layer;
	unsigned char pad1;
	unsigned int id;
}__attribute__ ((packed)) Physics_Struct;//size must be 0xE4

typedef struct collisionMgr_c_Struct{
	void *vtable;
	struct dStageActor_c_Struct *owner;
	void *pBelowInfo, *pAboveInfo, *pAdjacentInfo;
	Vec *pPos, *pLastPos, *pSpeed;
	Vec specialSpeedOffset;
	float xDeltaMaybe, yDeltaMaybe;
	float _34, _38;
	unsigned int _3C, _40, _44, _48;
	float initialXAsSetByJumpDai;
	/*dClass2DC_c*/void *pClass2DC;
	unsigned int _54;
	Physics_Struct *sCollBelow;
	Physics_Struct *sCollAbove;
	Physics_Struct *sCollAdjacentLast, *sCollAdjacent[2];
	struct collisionMgr_c_Struct *_6C, *_70, *_74;
	struct collisionMgr_c_Struct *_78[2];
	Physics_Struct *_80[2];
	unsigned int outputMaybe;
	unsigned int _8C;
	unsigned int someStoredBehaviourFlags, someStoredProps;
	char whichPlayerOfParent____;
	char whichController____;
	unsigned short _9A, _9C;
	unsigned char pad0[2];
	unsigned int tileBelowProps;
	unsigned char tileBelowSubType, lastTileBelowSubType;
	unsigned char pad1[2];
	unsigned int tileAboveProps;
	unsigned char tileAboveSubType, lastTileAboveSubType;
	unsigned char pad2[2];
	unsigned int adjacentTileProps[2];
	unsigned char adjacentTileSubType[2];
	unsigned char _BA, _BB;
	unsigned char _BC; // &8 makes able to enter mini pipes?
	unsigned char currentSlopeType;
	short currentSlopeAngle;
	unsigned char currentFlippedSlopeType;
	unsigned char pad3;
	short currentFlippedSlopeAngle;
	unsigned int _C4;
	unsigned short currentAdjacentSlopeAngle;
	unsigned char pad4[2];
	unsigned int currentFenceType; // 0=null 1=ladder 2=fence
	Physics_Struct *_D0;
	float _D4;
	float _D8;
	float _DC;
	unsigned char touchedSpikeFlag;
	char maxTouchedSpikeType;
	unsigned char currentSlopeDirection, _E3, onGround_maybe, chainlinkMode;
	unsigned char pad5[2];
	unsigned char *pLayerID;
	unsigned char layer;
	bool enteredPipeIsMini;
	unsigned char pad6[2];
}__attribute__ ((packed)) collisionMgr_c_Struct;//size must be 0xF0

typedef struct{
    dActor_c_Struct s;
    unsigned char _125;
	unsigned char pad0[2];
	unsigned int _128, _12C, directionForCarry, _134, _138, _13C;
	float _140;
	unsigned int _144;
	ActivePhysics_Struct aPhysics;//at 0x148
	collisionMgr_c_Struct collMgr;//at 0x1EC
	unsigned char classAt2DC[0x34];//at 0x2DC
	float _310, _314;
	float spriteSomeRectX, spriteSomeRectY;
	float _320, _324, _328, _32C, _330, _334, _338, _33C, _340, _344;
	unsigned char direction;
	unsigned char currentZoneID;
	unsigned char _34A, _34B;
	unsigned char *spriteByteStorage;//at 0x34C
	unsigned short *spriteShortStorage;//at 0x350
	unsigned short spriteFlagNum;//at 0x354
	unsigned char pad1[2];//at 0x356
	unsigned long long spriteFlagMask;//at 0x358
	unsigned int _360;
	unsigned short spriteSomeFlag;
	unsigned char _366, _367;
	unsigned int _368;
	unsigned char eatenState;	// 0=normal,2=eaten,4=spit out
	unsigned char _36D;
	unsigned char pad2[2];
	Vec scaleBeforeBeingEaten;//at 0x370
	unsigned int _37C, lookAtMode, _384, _388;
	unsigned char stageActorType;
	unsigned char which_player;		// _38D
	unsigned char disableFlagMask, currentLayerID;
	unsigned char deleteForever;
	unsigned char appearsOnBackFence, _392, _padding;
}__attribute__ ((packed)) dStageActor_c_Struct;//size must be 0x394

typedef struct{
    dStageActor_c_Struct s;
    //MultiStateMgr acState;
	unsigned char acState[0x414 - 0x394];
}__attribute__ ((packed)) dActorMultiState_c_Struct;

typedef struct{
	void *vtable;
	const char *mName;
	int mID;
}__attribute__ ((packed)) dStateBase_c_Struct;

typedef struct{
	float xSpeed, ySpeed, maxYSpeed, yAccel;
	dStateBase_c_Struct *state;
	unsigned int _14, _18;
	unsigned char _1C, _1D, isDead;
	unsigned char pad0;
}__attribute__ ((packed)) EntityDeathInfo;//size must be 0x20

typedef struct{
	unsigned int some_count;
	unsigned int ice_timer1;
	unsigned int ice_timer2;
	unsigned int _mstate;				//0=not,1=frozen,3=die_coin
	unsigned int _10;
	unsigned int _nstate;				//1=countdown,2=meltedNormal
	unsigned int spawns_coin;			//1=delete,3=coin
	unsigned int _1C_timerLenType;
	unsigned int _20_defaultTimerLenType;
	unsigned int _24;
	unsigned int _28;
	unsigned int perm_freeze;
	unsigned int _30;
	unsigned int actorIds[12];
	void* owner;//at 0x64
}__attribute__ ((packed)) freezeMgr_c_Struct;//size must be 0x68

typedef struct dEn_c_Struct{
    dActorMultiState_c_Struct s;
    EntityDeathInfo deathInfo;//at 0x0x414
	unsigned int _434;
	unsigned short _438;
	unsigned char pad0[2];
	unsigned int _43C;
	Vec velocity1, velocity2;
	unsigned char _458, _459, _45A, _45B, _45C, _45D, _45E;
	unsigned char pad1;
	unsigned int _460;
	Vec initialScale;
	float _470;
	unsigned int _474, _478;
	struct dEn_c_Struct *_47C;
	unsigned int _480;
	//FIXME verify that size fits
	//unsigned char classAt484[0x4EC - 0x484];
	freezeMgr_c_Struct frzMgr;
	unsigned int _4EC;
	float _4F0, _4F4, _4F8;
	unsigned int flags_4FC;
	unsigned short counter_500, counter_502;
	unsigned short counter_504[4];
	unsigned short counter_50C;
	unsigned char pad2[2];
	unsigned int _510, _514, _518;
	void *_51C;
	struct dEn_c_Struct *_520;
}__attribute__ ((packed)) dEn_c_Struct;//size must be 0x524

typedef struct{
	unsigned short x, y;
	int layer, countdown, tile;
}__attribute__ ((packed)) BgGmBase__something_s;

typedef struct{
	float leftX, rightX;
	float _8, _C, _10, y, _18, _1C, _20, _24, _28, _2C;
	float zoneY, zoneHeight, zoneX, zoneWidth;
	unsigned short flags; // documented in idb struct, kind of
	unsigned char pad0[2];
}__attribute__ ((packed)) BgGmBase__limitLineEntry_s;

typedef struct{
	float x1, x2, y1, y2;
	unsigned char unkValue6, zoomLevel, firstFlag;
	unsigned char pad0;
}__attribute__ ((packed)) BgGmBase__manualZoomEntry_s;

typedef struct{
	float _0, _4;
	unsigned char _8;
	unsigned char pad0[3];
}__attribute__ ((packed)) BgGmBase__beets_s;

typedef struct{
	dBase_c_Struct s;
	unsigned int behaviours; //type?

	int somethingCount;
	BgGmBase__something_s somethings[256];

	// Limit lines grouped by:
	// 64 zones; 8 groups IDed by mysterious setting; 16 lines per group
	BgGmBase__limitLineEntry_s limitLines[64][8][16];

	BgGmBase__manualZoomEntry_s manualZooms[64];
	unsigned int _8F478, _8F47C;

	BgGmBase__beets_s beets1[100];
	BgGmBase__beets_s beets2[100];

}__attribute__ ((packed)) BgGmBase_Struct;

void SoundPlayingClass__PlaySoundAtPosition(void *self, int id, Vec2 *pos, unsigned int flags);
void ConvertStagePositionToScreenPosition(Vec2 *screen, Vec *stage);
void SpawnEffect(const char* str, int a, Vec *b, s16Vec *c, Vec *d);
bool dEffectBreakMgr_c__spawnTile(void *self, Vec *position, unsigned int settings, char param);

#define SOUND_PLAYING_CLASS__PLAY_SOUND_AT_POSITION 0x80198A40
#define SOUND_PLAYING_CLASS__INSTANCE2 0x80429A80
#define CONVERT_STAGE_POSITION_TO_SCREEN_POSITION 0x8006A4B0
#define SPAWN_EFFECT 0x8016C6A0
#define D_EFFECT_BREAK_MGR_C__SPAWN_TILE 0x800925F0

#endif//_GAME_H_