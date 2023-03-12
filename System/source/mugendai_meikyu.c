#include "mugendai_meikyu.h"

#define MAZE_KABE_1_TYPE 32
#define MAZE_KABE_2_TYPE 33

#define NORM_MODE_TYPE 207
#define INFI_MODE_TYPE 208
#define F_TYPE 113
#define NUM_START_X 12
#define NUM_START_Y 104
#define ITEMBOX_START_X 12
#define ITEMBOX_START_Y 80
#define ITEMBOX_COUNT 5

#define BGDAT_OBJECT_SIZE 0xA
#define BGDAT_OBJECT_TYPE_OFFSET 1
#define BGDAT_OBJECT_X_OFFSET 2
#define BGDAT_OBJECT_Y_OFFSET 4

#define COURSE_ENTRANCE_SIZE 0x14
#define COURSE_ENTRANCE_X_OFFSET 0
#define COURSE_ENTRANCE_Y_OFFSET 2
#define COURSE_ENTRANCE_ID_OFFSET 8
#define COURSE_ENTRANCE_DEST_AREA_OFFSET 9

#define COURSE_SPRITE_SIZE 0x10
#define COURSE_SPRITE_ID_OFFSET 0
#define COURSE_SPRITE_X_OFFSET 2
#define COURSE_SPRITE_Y_OFFSET 4
#define COURSE_SPRITE_SETTINGS_OFFSET 6

#define DOOR_SPRITE_ID 259
#define STARCOIN_SPRITE_ID 32

unsigned int samePosTekiType(mugendaiMeikyu *game, mazePos *mp){
    for(unsigned int i = 0; i < MUGENDAI_MEIKYU_TEKI_COUNT;i++){
        if(isSameMazePos(&(game->teki[i].pos), mp))return game->teki[i].type;
    }
    return INVALID_TEKI;
}

void setDestAreaToCourseEntrance(unsigned char *ent, unsigned char area){
    if(!ent)return;
    *(ent + COURSE_ENTRANCE_DEST_AREA_OFFSET) = area;
}

void setPosToCourseEntrance(unsigned char *ent, unsigned int x, unsigned int y){
    if(!ent)return;
    u16ToBytes(ent + COURSE_ENTRANCE_X_OFFSET, (unsigned short)x);
    u16ToBytes(ent + COURSE_ENTRANCE_Y_OFFSET, (unsigned short)y);
}

unsigned char *findEntranceByIdFromCourseBin(unsigned char id, unsigned char *courseBin, unsigned int courseBinSize){
    unsigned int block6Size;
    unsigned int curEntIndex = 0;
    unsigned char *block6 = getCourseBinBlock(courseBin, 6, &block6Size);
    unsigned int entCount = block6Size / COURSE_ENTRANCE_SIZE;
    while(curEntIndex < entCount){
        unsigned char *curEnt = block6 + curEntIndex * COURSE_ENTRANCE_SIZE;
        if(*(curEnt + COURSE_ENTRANCE_ID_OFFSET) == id)return curEnt;
        curEntIndex++;
    }
    return NULL;
}

unsigned char *findSpriteByIdFromCourseBin(unsigned short id, unsigned char *courseBin, unsigned int courseBinSize){
    unsigned int block7Size;
    unsigned int curSprIndex = 0;
    unsigned char *block7 = getCourseBinBlock(courseBin, 7, &block7Size);
    unsigned int sprCount = (block7Size - 4) / COURSE_SPRITE_SIZE;
    while(curSprIndex < sprCount){
        unsigned char *curSpr = curSprIndex * COURSE_SPRITE_SIZE + block7;
        if(bytesToU16(curSpr + COURSE_SPRITE_ID_OFFSET) == id)return curSpr;
        curSprIndex++;
    }
    return NULL;
}

unsigned char *findSpriteByIdAndSettingsFromCourseBin(unsigned short id, unsigned int settingsIndex, unsigned char setting, unsigned char *courseBin, unsigned int courseBinSize){
    unsigned int block7Size;
    unsigned int curSprIndex = 0;
    unsigned char *block7 = getCourseBinBlock(courseBin, 7, &block7Size);
    unsigned int sprCount = (block7Size - 4) / COURSE_SPRITE_SIZE;
    while(curSprIndex < sprCount){
        unsigned char *curSpr = curSprIndex * COURSE_SPRITE_SIZE + block7;
        if(bytesToU16(curSpr + COURSE_SPRITE_ID_OFFSET) == id && *(curSpr + COURSE_SPRITE_SETTINGS_OFFSET + settingsIndex) == setting)return curSpr;
        curSprIndex++;
    }
    return NULL;
}

void setPosToCourseSprite(unsigned char *spr, unsigned int x, unsigned int y){
    if(!spr)return;
    u16ToBytes(spr + COURSE_SPRITE_X_OFFSET, (unsigned short)x);
    u16ToBytes(spr + COURSE_SPRITE_Y_OFFSET, (unsigned short)y);
}

void setIdToCourseSprite(unsigned char *spr, unsigned short id){
    if(!spr)return;
    u16ToBytes(spr + COURSE_SPRITE_ID_OFFSET, id);
}

void setSettingsToCourseSprite(unsigned char *spr, unsigned int settingsIndex, unsigned char setting){
    if(!spr)return;
    *(spr + COURSE_SPRITE_SETTINGS_OFFSET + settingsIndex) = setting;
}

void setZoneIdToCourseSprite(unsigned char *spr, unsigned char zoneId){
    setSettingsToCourseSprite(spr, 6, zoneId);
}

bool isSameMazePos(mazePos *a, mazePos *b){
    if(a->x == b->x && a->y == b->y)return true;
    return false;
}

void reportGameSettings(mugendaiMeikyu *game){
    mazePos tmpPos;
    void (*OSReport)(const char*, ...) = (void*)OSREPORT;
    char string[MAZE_SIZE_X + 2];
    string[MAZE_SIZE_X] = '\n';
    string[MAZE_SIZE_X + 1] = '\0';
    for(unsigned int y = 0;y < MAZE_SIZE_Y;y++){
        for(unsigned int x = 0;x < MAZE_SIZE_X;x++){
            tmpPos.x = x;
            tmpPos.y = y;
            if(game->rawMazeData[y][x]){
                string[x] = '#';
            }else{
                if(isSameMazePos(&tmpPos, &(game->start))){
                    string[x] = 'S';
                }else if(isSameMazePos(&tmpPos, &(game->goal))){
                    string[x] = 'G';
                }else if(isSameMazePos(&tmpPos, &(game->starCoin))){
                    string[x] = 'C';
                }else{
                    string[x] = ' ';
                }
            }
        }
        OSReport(string);
    }
    OSReport(getString11(), game->isInfinityMode);
    OSReport(getString12(), game->curFloor);
}

void anahoriInit(bool rawMazeData[][MAZE_SIZE_X]){
    for(unsigned int y = 0;y < MAZE_SIZE_Y;y++){
        for(unsigned int x = 0;x < MAZE_SIZE_X;x++){
            if(x == 0 || x == (MAZE_SIZE_X - 1) || y == 0 || y == (MAZE_SIZE_Y - 1)){
                rawMazeData[y][x] = false;
            }else{
                rawMazeData[y][x] = true;
            }
        }
    }
}

void anahoriLast(bool rawMazeData[][MAZE_SIZE_X]){
    for(unsigned int y = 0;y < MAZE_SIZE_Y;y++){
        for(unsigned int x = 0;x < MAZE_SIZE_X;x++){
            if(x == 0 || x == (MAZE_SIZE_X - 1) || y == 0 || y == (MAZE_SIZE_Y - 1)){
                rawMazeData[y][x] = true;
            }
        }
    }
}

void anahoriDig(bool rawMazeData[][MAZE_SIZE_X], unsigned int x, unsigned int y, unsigned int *digFinish)
{
    unsigned int digDir = random(4);//掘れる方向決定
    //実際に掘る
    switch(digDir){
        case 0:
            if(rawMazeData[y][x + 1] == false || rawMazeData[y][x + 2] == false){
                *digFinish = 0;
                *(digFinish + 1) = 0;
                return;
            }
            rawMazeData[y][x + 1] = false;
            rawMazeData[y][x + 2] = false;
            *digFinish = x + 2;
            *(digFinish + 1) = y;
            return;
        case 1:
            if(rawMazeData[y][x - 1] == false || rawMazeData[y][x - 2] == false){
                *digFinish = 0;
                *(digFinish + 1) = 0;
                return;
            }
            rawMazeData[y][x - 1] = false;
            rawMazeData[y][x - 2] = false;
            *digFinish = x - 2;
            *(digFinish + 1) = y;
            return;
        case 2:
            if(rawMazeData[y + 1][x] == false || rawMazeData[y + 2][x] == false){
                *digFinish = 0;
                *(digFinish + 1) = 0;
                return;
            }
            rawMazeData[y + 1][x] = false;
            rawMazeData[y + 2][x] = false;
            *digFinish = x;
            *(digFinish + 1) = y + 2;
            return;
        default:
            if(rawMazeData[y - 1][x] == false || rawMazeData[y - 2][x] == false){
                *digFinish = 0;
                *(digFinish + 1) = 0;
                return;
            }
            rawMazeData[y - 1][x] = false;
            rawMazeData[y - 2][x] = false;
            *digFinish = x;
            *(digFinish + 1) = y - 2;
    }
}

bool anahoriCanDig(bool rawMazeData[][MAZE_SIZE_X], unsigned int x, unsigned int y){
    if(rawMazeData[y][x])return false;
    if(rawMazeData[y + 1][x] && rawMazeData[y + 2][x])return true;
    if(rawMazeData[y - 1][x] && rawMazeData[y - 2][x])return true;
    if(rawMazeData[y][x + 1] && rawMazeData[y][x + 2])return true;
    if(rawMazeData[y][x - 1] && rawMazeData[y][x - 2])return true;
    return false;
}

void anahori(bool rawMazeData[][MAZE_SIZE_X]){
    anahoriInit(rawMazeData);
    rawMazeData[1][1] = false;
    unsigned int canDig[2 * MAZE_SIZE_X * MAZE_SIZE_Y];
    unsigned int canDigCount = 0;
    unsigned int x = 1;
    unsigned int y = 1;
    while (true)
    {
        while (true)
        {
            unsigned int digFinish[2];
            anahoriDig(rawMazeData, x, y, digFinish);
            if(digFinish[0] == 0 && digFinish[1] == 0)break;
            x = digFinish[0];
            y = digFinish[1];
        }
        //まだ掘れる場所が存在するか判断
        canDigCount = 0;
        for(int yc = 0; yc < MAZE_SIZE_Y; yc++){
            for(int xc = 0; xc < MAZE_SIZE_X; xc++){
                if(xc % 2 == 0 || yc % 2 == 0)continue;
                if(anahoriCanDig(rawMazeData, xc, yc)){
                    canDig[canDigCount * 2] = xc;
                    canDig[canDigCount * 2 + 1] = yc;
                    canDigCount++;
                }
            }
        }
        if(canDigCount == 0)break;
        unsigned int canDigTargetIndex = random(canDigCount);
        x = canDig[canDigTargetIndex * 2];
        y = canDig[canDigTargetIndex * 2 + 1];
    }
    anahoriLast(rawMazeData);
}

void itemBox(mugendaiMeikyu *game){
    game->item1Type = random(ITEMBOX_COUNT);
    game->item2Type = random(ITEMBOX_COUNT);
    while(game->item1Type == game->item2Type)game->item2Type = random(ITEMBOX_COUNT);
    game->item1.x = random(MAZE_SIZE_X - 2) + 1;
    game->item1.y = random(MAZE_SIZE_Y - 2) + 1;
    while(game->rawMazeData[game->item1.y][game->item1.x] == true || game->rawMazeData[game->item1.y + 1][game->item1.x] == false){
        game->item1.x = random(MAZE_SIZE_X - 2) + 1;
        game->item1.y = random(MAZE_SIZE_Y - 2) + 1;
    }
    game->item2.x = random(MAZE_SIZE_X - 2) + 1;
    game->item2.y = random(MAZE_SIZE_Y - 2) + 1;
    while(game->rawMazeData[game->item2.y][game->item2.x] == true || isSameMazePos(&(game->item1), &(game->item2)) || game->rawMazeData[game->item2.y + 1][game->item2.x] == false){
        game->item2.x = random(MAZE_SIZE_X - 2) + 1;
        game->item2.y = random(MAZE_SIZE_Y - 2) + 1;
    }
}

void startGoalDecideType0(mugendaiMeikyu *game){
    unsigned int searchCount = 0;
    game->start.y = random(3) + 1;
    game->start.x = random(MAZE_SIZE_X - 2) + 1;
    while(game->rawMazeData[game->start.y][game->start.x] == true || game->rawMazeData[game->start.y + 1][game->start.x] == false){
        game->start.y = random(3) + 1;
        game->start.x = random(MAZE_SIZE_X - 2) + 1;
        searchCount++;
        if(searchCount >= 30){
            game->start.x = 1;
            game->start.y = 1;
            break;
        }
    }
    searchCount = 0;
    game->goal.y = (MAZE_SIZE_Y - 1) - (random(3) + 1);
    game->goal.x = random(MAZE_SIZE_X - 2) + 1;
    while(game->rawMazeData[game->goal.y][game->goal.x] == true || game->rawMazeData[game->goal.y + 1][game->goal.x] == false){
        game->goal.y = (MAZE_SIZE_Y - 1) - (random(3) + 1);
        game->goal.x = random(MAZE_SIZE_X - 2) + 1;
        searchCount++;
        if(searchCount >= 30){
            game->goal.x = MAZE_SIZE_X - 2;
            game->goal.y = MAZE_SIZE_Y - 2;
            break;
        }
    }
}

void startGoalDecideType1(mugendaiMeikyu *game){
    unsigned int searchCount = 0;
    game->start.y = (MAZE_SIZE_Y - 1) - (random(3) + 1);
    game->start.x = random(MAZE_SIZE_X - 2) + 1;
    while(game->rawMazeData[game->start.y][game->start.x] == true || game->rawMazeData[game->start.y + 1][game->start.x] == false){
        game->start.y = (MAZE_SIZE_Y - 1) - (random(3) + 1);
        game->start.x = random(MAZE_SIZE_X - 2) + 1;
        searchCount++;
        if(searchCount >= 30){
            game->start.x = MAZE_SIZE_X - 2;
            game->start.y = MAZE_SIZE_Y - 2;
            break;
        }
    }
    searchCount = 0;
    game->goal.y = random(3) + 1;
    game->goal.x = random(MAZE_SIZE_X - 2) + 1;
    while(game->rawMazeData[game->goal.y][game->goal.x] == true || game->rawMazeData[game->goal.y + 1][game->goal.x] == false){
        game->goal.y = random(3) + 1;
        game->goal.x = random(MAZE_SIZE_X - 2) + 1;
        searchCount++;
        if(searchCount >= 30){
            game->goal.x = 1;
            game->goal.y = 1;
            break;
        }
    }
}

void startGoalDecideType2(mugendaiMeikyu *game){
    unsigned int searchCount = 0;
    game->start.y = random(MAZE_SIZE_Y - 2) + 1;
    game->start.x = random(3) + 1;
    while(game->rawMazeData[game->start.y][game->start.x] == true || game->rawMazeData[game->start.y + 1][game->start.x] == false){
        game->start.y = random(MAZE_SIZE_Y - 2) + 1;
        game->start.x = random(3) + 1;
        searchCount++;
        if(searchCount >= 30){
            game->start.x = 1;
            game->start.y = MAZE_SIZE_Y - 2;
            break;
        }
    }
    searchCount = 0;
    game->goal.y = random(MAZE_SIZE_Y - 2) + 1;
    game->goal.x = (MAZE_SIZE_X - 1) - (random(3) + 1);
    while(game->rawMazeData[game->goal.y][game->goal.x] == true || game->rawMazeData[game->goal.y + 1][game->goal.x] == false){
        game->goal.y = random(MAZE_SIZE_Y - 2) + 1;
        game->goal.x = (MAZE_SIZE_X - 1) - (random(3) + 1);
        searchCount++;
        if(searchCount >= 30){
            game->goal.x = MAZE_SIZE_X - 2;
            game->goal.y = 1;
            break;
        }
    }
}

void startGoalDecideType3(mugendaiMeikyu *game){
    unsigned int searchCount = 0;
    game->start.y = random(MAZE_SIZE_Y - 2) + 1;
    game->start.x = (MAZE_SIZE_X - 1) - (random(3) + 1);
    while(game->rawMazeData[game->start.y][game->start.x] == true || game->rawMazeData[game->start.y + 1][game->start.x] == false){
        game->start.y = random(MAZE_SIZE_Y - 2) + 1;
        game->start.x = (MAZE_SIZE_X - 1) - (random(3) + 1);
        searchCount++;
        if(searchCount >= 30){
            game->start.x = MAZE_SIZE_X - 2;
            game->start.y = 1;
            break;
        }
    }
    searchCount = 0;
    game->goal.y = random(MAZE_SIZE_Y - 2) + 1;
    game->goal.x = random(3) + 1;
    while(game->rawMazeData[game->goal.y][game->goal.x] == true || game->rawMazeData[game->goal.y + 1][game->goal.x] == false){
        game->goal.y = random(MAZE_SIZE_Y - 2) + 1;
        game->goal.x = random(3) + 1;
        searchCount++;
        if(searchCount >= 30){
            game->goal.x = 1;
            game->goal.y = MAZE_SIZE_Y - 2;
            break;
        }
    }
}
void startGoalDecide(mugendaiMeikyu *game){
    unsigned int r = random(4);
    switch(r){
        case 0:
            startGoalDecideType0(game);
            return;
        case 1:
            startGoalDecideType1(game);
            return;
        case 2:
            startGoalDecideType2(game);
            return;
        default:
            startGoalDecideType3(game);
            return;
    }
}

void starCoin(mugendaiMeikyu *game){
    game->starCoin.x = 0;
    game->starCoin.y = 0;
    if(game->isInfinityMode)return;
    if(game->curFloor > 3)return;
    game->starCoin.x = random(MAZE_SIZE_X);
    game->starCoin.y = random(MAZE_SIZE_Y);
    while(game->rawMazeData[game->starCoin.y][game->starCoin.x] == true){
        game->starCoin.x = random(MAZE_SIZE_X);
        game->starCoin.y = random(MAZE_SIZE_Y);
    }
}

bool checkIsEnemySamePos(mugendaiMeikyu *game, unsigned int curIndex){
    if(isSameMazePos(&(game->teki[curIndex].pos), &(game->start)))return true;
    if(isSameMazePos(&(game->teki[curIndex].pos), &(game->goal)))return true;
    for(unsigned int i = 0;i < curIndex;i++){
        if(isSameMazePos(&(game->teki[curIndex].pos), &(game->teki[i].pos)))return true;
    }
    return false;
}

void enemy(mugendaiMeikyu *game){
    unsigned int tekiCount = NORM_MODE_MUGENDAI_MEIKYU_TEKI_COUNT;
    if(game->isInfinityMode){
        tekiCount += (game->curFloor - 1);
        if(tekiCount > MUGENDAI_MEIKYU_TEKI_COUNT)tekiCount = MUGENDAI_MEIKYU_TEKI_COUNT;
    }
    for(unsigned int i = 0;i < MUGENDAI_MEIKYU_TEKI_COUNT;i++)game->teki[i].type = INVALID_TEKI;
    for(unsigned int i = 0;i < tekiCount;i++){
        unsigned int searchCount = 0;
        do{
            game->teki[i].pos.x = random(MAZE_SIZE_X);
            game->teki[i].pos.y = random(MAZE_SIZE_Y);
            searchCount++;
            if(searchCount > 30){
                break;
            }
        }while(checkIsEnemySamePos(game, i) || game->rawMazeData[game->teki[i].pos.y][game->teki[i].pos.x]);
        if(game->rawMazeData[game->teki[i].pos.y + 1][game->teki[i].pos.x] == true && game->rawMazeData[game->teki[i].pos.y][game->teki[i].pos.x] == false){
            game->teki[i].type = random(MUGENDAI_MEIKYU_TEKI_TYPE_COUNT);
        }else{
            game->teki[i].type = random(MUGENDAI_MEIKYU_TEKI_TYPE_COUNT_TYU) + 0x80;
        }
        if(isSameMazePos(&(game->teki[i].pos), &(game->start)) || isSameMazePos(&(game->teki[i].pos), &(game->goal))){
            game->teki[i].type = INVALID_TEKI;
        }
    }
}

void decideGameSettings(mugendaiMeikyu *game){
    void (*OSReport)(const char*, ...) = (void*)OSREPORT;
    anahori(game->rawMazeData);
    startGoalDecide(game);
    itemBox(game);
    starCoin(game);
    enemy(game);
    OSReport(getString10());
    reportGameSettings(game);
    return;
}

unsigned char *getNumberObject(unsigned int num, unsigned int place, unsigned char *bgdat, unsigned int bgdatSize){
    return findObjectByPosFromBgdat(NUM_START_X + num, NUM_START_Y + place, bgdat, bgdatSize);
}

unsigned char *getItembox(unsigned int type, unsigned int floor, unsigned char *bgdat, unsigned int bgdatSize){
    return findObjectByPosFromBgdat(ITEMBOX_START_X + type, ITEMBOX_START_Y + floor - 1, bgdat, bgdatSize);
}

unsigned char *findObjectByPosFromBgdat(unsigned int x, unsigned int y, unsigned char *bgdat, unsigned int bgdatSize){
    unsigned int objectCount = (bgdatSize - 2) / BGDAT_OBJECT_SIZE;
    unsigned int curObjectIndex = 0;
    while(curObjectIndex < objectCount){
        unsigned char *curObject = bgdat + curObjectIndex * BGDAT_OBJECT_SIZE;
        unsigned int curObjectX = bytesToU16(curObject + BGDAT_OBJECT_X_OFFSET);
        unsigned int curObjectY = bytesToU16(curObject + BGDAT_OBJECT_Y_OFFSET);
        if(x == curObjectX && y == curObjectY)return curObject;
        curObjectIndex++;
    }
    return NULL;
}

unsigned char *findObjectByTypeFromBgdat(unsigned char type, unsigned char *bgdat, unsigned int bgdatSize){
    unsigned int objectCount = (bgdatSize - 2) / BGDAT_OBJECT_SIZE;
    unsigned int curObjectIndex = 0;
    while(curObjectIndex < objectCount){
        unsigned char *curObject = bgdat + curObjectIndex * BGDAT_OBJECT_SIZE;
        if(*(curObject + BGDAT_OBJECT_TYPE_OFFSET) == type)return curObject;
        curObjectIndex++;
    }
    return NULL;
}

void applyMazeToBgdatL1(mugendaiMeikyu *game, unsigned char *bgdatL1, unsigned int bgdatL1Size){
    for(int y = 1;y < MAZE_SIZE_Y - 1;y++){
        unsigned int targetObjectY = y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS;
        for(int x = 1;x < MAZE_SIZE_X - 1;x++){
            unsigned int targetObjectX = x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS;
            unsigned char *targetObject = findObjectByPosFromBgdat(targetObjectX, targetObjectY, bgdatL1, bgdatL1Size);
            if(!targetObject)return;
            if(game->rawMazeData[y][x]){
                *(targetObject + BGDAT_OBJECT_TYPE_OFFSET) = MAZE_KABE_1_TYPE;
            }else{
                *(targetObject + BGDAT_OBJECT_TYPE_OFFSET) = MAZE_KABE_2_TYPE;
            }
        }
    }
    if(game->isInfinityMode || game->curFloor > (BOSS_FLOOR - 1))return;
    unsigned char *itembox1 = getItembox(game->item1Type, game->curFloor, bgdatL1, bgdatL1Size);
    if(itembox1){
        u16ToBytes(itembox1 + BGDAT_OBJECT_X_OFFSET, game->item1.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS + 1);
        u16ToBytes(itembox1 + BGDAT_OBJECT_Y_OFFSET, game->item1.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS + 1);
    }
    unsigned char *itembox2 = getItembox(game->item2Type, game->curFloor, bgdatL1, bgdatL1Size);
    if(itembox2){
        u16ToBytes(itembox2 + BGDAT_OBJECT_X_OFFSET, game->item2.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS + 1);
        u16ToBytes(itembox2 + BGDAT_OBJECT_Y_OFFSET, game->item2.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS + 1);
    }
}

void applyMazeToBgdatL2(mugendaiMeikyu *game, unsigned char *bgdatL2, unsigned int bgdatL2Size){
    unsigned char displayModeType = NORM_MODE_TYPE;
    unsigned char displayNumObjXPos[3];
    if(game->isInfinityMode)displayModeType = INFI_MODE_TYPE;
    unsigned char *displayModeObject = findObjectByTypeFromBgdat(displayModeType, bgdatL2, bgdatL2Size);
    if(displayModeObject){
        u16ToBytes(displayModeObject + BGDAT_OBJECT_X_OFFSET, game->start.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS);
        u16ToBytes(displayModeObject + BGDAT_OBJECT_Y_OFFSET, game->start.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS);
    }
    displayNumObjXPos[2] = (game->curFloor % 10);
    displayNumObjXPos[1] = (game->curFloor / 10) % 10;
    displayNumObjXPos[0] = (game->curFloor / 100) % 10;
    for(int i = 0;i < 3;i++){
        unsigned char *obj = getNumberObject(displayNumObjXPos[i], i, bgdatL2, bgdatL2Size);
        if(!obj)continue;
        u16ToBytes(obj + BGDAT_OBJECT_X_OFFSET, game->start.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS + i);
        u16ToBytes(obj + BGDAT_OBJECT_Y_OFFSET, game->start.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS + 2);
    }
    unsigned char *fObj = findObjectByTypeFromBgdat(F_TYPE, bgdatL2, bgdatL2Size);
    if(fObj){
        u16ToBytes(fObj + BGDAT_OBJECT_X_OFFSET, game->start.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS + 3);
        u16ToBytes(fObj + BGDAT_OBJECT_Y_OFFSET, game->start.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS + 2);
    }
}

void applyMazeToCourseBin(mugendaiMeikyu *game, unsigned char *courseBin, unsigned int courseBinSize){
    unsigned char *startEnt = findEntranceByIdFromCourseBin(0, courseBin, courseBinSize);
    setPosToCourseEntrance(startEnt, (game->start.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS + 1) * 16, (game->start.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS + 3) * 16);
    unsigned char *goalEnt = findEntranceByIdFromCourseBin(1, courseBin, courseBinSize);
    setPosToCourseEntrance(goalEnt, (game->goal.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS + 1) * 16, (game->goal.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS + 3) * 16);
    if(game->isInfinityMode == false && game->curFloor + 1 == BOSS_FLOOR){
        setDestAreaToCourseEntrance(goalEnt, 4);
    }
    unsigned char *door = findSpriteByIdFromCourseBin(DOOR_SPRITE_ID, courseBin, courseBinSize);
    setPosToCourseSprite(door, (game->goal.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS + 1) * 16, (game->goal.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS + 1) * 16);
    unsigned char *starCoin = findSpriteByIdFromCourseBin(STARCOIN_SPRITE_ID, courseBin, courseBinSize);
    if(!game->isInfinityMode && game->curFloor < 4){
        setPosToCourseSprite(starCoin, (game->starCoin.x * MAZE_BLOCK_X_SIZE + MAZE_START_X_POS + 1) * 16, (game->starCoin.y * MAZE_BLOCK_Y_SIZE + MAZE_START_Y_POS + 1) * 16);
        setSettingsToCourseSprite(starCoin, 4, game->curFloor - 1);
        //setZoneIdToCourseSprite(starCoin, 1);
    }
}

void createMugendaiMeikyuGame(myMemStruct *myMem){//コースデータバックアップ
    unsigned char *arcFilePtr = myMem->courseArcFile;
    if(myMem->mugenGame.course2Bin)return;
    void *(*memcpy)(void*, void*, unsigned int) = (void*)MEMCPY;
    unsigned int fileSize;
    unsigned char *fileData;
    char inArcCourseFileName[128];

    makeInArchiveCourseFileName(inArcCourseFileName, 128, 2, -1);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    myMem->mugenGame.course2Bin = my_malloc_via_egg(fileSize);
    memcpy(myMem->mugenGame.course2Bin, fileData, fileSize);
    myMem->mugenGame.course2BinSize = fileSize;

    makeInArchiveCourseFileName(inArcCourseFileName, 128, 2, 1);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    myMem->mugenGame.course2BgdatL1Bin = my_malloc_via_egg(fileSize);
    memcpy(myMem->mugenGame.course2BgdatL1Bin, fileData, fileSize);
    myMem->mugenGame.course2BgdatL1BinSize = fileSize;

    makeInArchiveCourseFileName(inArcCourseFileName, 128, 2, 2);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    myMem->mugenGame.course2BgdatL2Bin = my_malloc_via_egg(fileSize);
    memcpy(myMem->mugenGame.course2BgdatL2Bin, fileData, fileSize);
    myMem->mugenGame.course2BgdatL2BinSize = fileSize;

    makeInArchiveCourseFileName(inArcCourseFileName, 128, 3, -1);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    myMem->mugenGame.course3Bin = my_malloc_via_egg(fileSize);
    memcpy(myMem->mugenGame.course3Bin, fileData, fileSize);
    myMem->mugenGame.course3BinSize = fileSize;

    makeInArchiveCourseFileName(inArcCourseFileName, 128, 3, 1);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    myMem->mugenGame.course3BgdatL1Bin = my_malloc_via_egg(fileSize);
    memcpy(myMem->mugenGame.course3BgdatL1Bin, fileData, fileSize);
    myMem->mugenGame.course3BgdatL1BinSize = fileSize;

    makeInArchiveCourseFileName(inArcCourseFileName, 128, 3, 2);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    myMem->mugenGame.course3BgdatL2Bin = my_malloc_via_egg(fileSize);
    memcpy(myMem->mugenGame.course3BgdatL2Bin, fileData, fileSize);
    myMem->mugenGame.course3BgdatL2BinSize = fileSize;
}

void restoreCourseBackupData(myMemStruct *myMem, unsigned int curArea){//バックアップしたコースデータをリストア
    void *(*memcpy)(void*, void*, unsigned int) = (void*)MEMCPY;
    unsigned char *arcFilePtr = myMem->courseArcFile;
    unsigned int fileSize;
    unsigned char *fileData;
    char inArcCourseFileName[128];
    if(curArea == 2){
        makeInArchiveCourseFileName(inArcCourseFileName, 128, 2, -1);
        fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
        memcpy(fileData, myMem->mugenGame.course2Bin, fileSize);
        makeInArchiveCourseFileName(inArcCourseFileName, 128, 2, 1);
        fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
        memcpy(fileData, myMem->mugenGame.course2BgdatL1Bin, fileSize);
        makeInArchiveCourseFileName(inArcCourseFileName, 128, 2, 2);
        fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
        memcpy(fileData, myMem->mugenGame.course2BgdatL2Bin, fileSize);
    }else{
        makeInArchiveCourseFileName(inArcCourseFileName, 128, 3, -1);
        fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
        memcpy(fileData, myMem->mugenGame.course3Bin, fileSize);
        makeInArchiveCourseFileName(inArcCourseFileName, 128, 3, 1);
        fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
        memcpy(fileData, myMem->mugenGame.course3BgdatL1Bin, fileSize);
        makeInArchiveCourseFileName(inArcCourseFileName, 128, 3, 2);
        fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
        memcpy(fileData, myMem->mugenGame.course3BgdatL2Bin, fileSize);
    }
}

void destroyMugendaiMeikyuGame(myMemStruct *myMem){//フラグ破棄など
    myMem->mugenGame.curFloor = 0;
    myMem->mugenGame.isInfinityMode = false;
}

void doMugendaiMeikyuGame(myMemStruct *myMem, unsigned int curArea){
	if(myMem->mugenGame.curFloor == 0){
		if(curArea == 3)myMem->mugenGame.isInfinityMode = true;
	}
	myMem->mugenGame.curFloor++;
    restoreCourseBackupData(myMem, curArea);
    decideGameSettings(&(myMem->mugenGame));

    unsigned char *arcFilePtr = myMem->courseArcFile;
    unsigned int fileSize;
    unsigned char *fileData;
    char inArcCourseFileName[128];
    makeInArchiveCourseFileName(inArcCourseFileName, 128, curArea, 1);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    applyMazeToBgdatL1(&(myMem->mugenGame), fileData, fileSize);
    makeInArchiveCourseFileName(inArcCourseFileName, 128, curArea, 2);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    applyMazeToBgdatL2(&(myMem->mugenGame), fileData, fileSize);
    makeInArchiveCourseFileName(inArcCourseFileName, 128, curArea, -1);
    fileData = getARCChildFilePointer(arcFilePtr, inArcCourseFileName, &fileSize);
    applyMazeToCourseBin(&(myMem->mugenGame), fileData, fileSize);
    
	return;
}