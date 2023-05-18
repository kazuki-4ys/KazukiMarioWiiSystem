#include "da_change_block_c.h"

unsigned short *BgGmBase__getPointerToTile(BgGmBase_Struct *self, int x, int y, int layer, int *pBlockNum, bool unused){
    unsigned short*(*BgGmBase__getPointerToTile_ptr)(BgGmBase_Struct*, int, int, int, int*, bool) = (void*)BG_GM_BASE__GET_POINTER_TO_TILE;
    return BgGmBase__getPointerToTile_ptr(self, x, y, layer, pBlockNum, unused);
}

void BgGmBase__placeTile(BgGmBase_Struct *self, unsigned short x, unsigned short y, int layer, int tile){
    void (*BgGmBase__placeTile_ptr)(BgGmBase_Struct*, unsigned short, unsigned short, int, int) = (void*)BG_GM_BASE__PLACE_TILE;
    BgGmBase__placeTile_ptr(self, x, y, layer, tile);
}

void daChengeBlock_c__doStuff(daChengeBlock_c_Struct *self, daChengeBlock_c__Action action, bool wasCalledOnCreation){
    unsigned short Tiles[6];
    Tiles[0] = 124;
    Tiles[1] = 2;
    Tiles[2] = 12;
    Tiles[3] = 123;
    Tiles[4] = 15;
    Tiles[5] = 0;
    BgGmBase_Struct *dBgGm_c__instance = *((BgGmBase_Struct**)((void*)D_BG_GM_C__INSTANCE));
    unsigned short perTilePatternFlag = 1, perRowPatternFlag = 1;

	unsigned short worldX = (unsigned short)(floatToInt(((dActor_c_Struct*)((void*)self))->pos.x - initializeFloat(0x3F000000)) & 0xFFF0);
	unsigned short baseWorldX = worldX;
	unsigned short worldY = (unsigned short)(floatToInt(abs(((dActor_c_Struct*)((void*)self))->pos.y) - initializeFloat(0x3F000000)) & 0xFFF0);

	if (self->pattern == CheckerB) {
		perTilePatternFlag = 0;
		perRowPatternFlag = 0;
	}
    unsigned short tile;
    if (action != Destroy) {
		if (self->blockType & 8) {
			// Specify a tile number
			tile = 0x8000 | ((self->blockType & 3) << 8) | ((((fBase_c_Struct*)((void*)self))->settings & 0xFF00000) >> 20);
		} else {
			// fall through
			tile = Tiles[self->blockType];
		}
	} else {
		tile = 0;
	}
    for (unsigned short y = 0; y < self->height; y++) {
		for (unsigned short x = 0; x < self->width; x++) {
			if (perTilePatternFlag) {
                unsigned short *pExistingTile = BgGmBase__getPointerToTile(dBgGm_c__instance, worldX, worldY, ((dStageActor_c_Struct*)((void*)self))->currentLayerID, NULL, false);
                unsigned short existingTile = pExistingTile ? *pExistingTile : 0;
                BgGmBase__placeTile(dBgGm_c__instance, worldX, worldY, ((dStageActor_c_Struct*)((void*)self))->currentLayerID, tile);
                if (!wasCalledOnCreation) {
					Vec effectPos;
					if (action == Destroy) {
                        if (self->blockType != 2) {
							effectPos.x = (intToFloat(worldX)) + initializeFloat(0x41000000);
							effectPos.y = (intToFloat(-worldY)) - initializeFloat(0x41000000);
							effectPos.z = ((dActor_c_Struct*)((void*)self))->pos.z;

							unsigned short shardType;
							switch (existingTile) {
                                case 0x30: shardType = 0; break;
								case 0x31: shardType = 3; break;
								case 0x32: shardType = 4; break;
								case 0x33: shardType = 2; break;
								case 0x34: shardType = 1; break;
								case 0x37: shardType = 5; break;
								default: shardType = 0xFFFF;
                            }
                            if (!(((fBase_c_Struct*)((void*)self))->settings & 0x40000)) {
								if (shardType == 0xFFFF) {
									SpawnEffect(getString27(), 0, &effectPos, 0, 0);
								} else {
									unsigned int sets = (shardType << 8) | 3;
									effectPos.y -= initializeFloat(0x41000000);
									dEffectBreakMgr_c__spawnTile(*((void**)((void*)D_EFFECT_BREAK_MGR_C__INSTANCE)), &effectPos, sets, 0);
								}
							}
                            if (!(((fBase_c_Struct*)((void*)self))->settings & 0x80000)) {
                                Vec2 soundPos;
								ConvertStagePositionToScreenPosition(&soundPos, &effectPos);
								SoundPlayingClass__PlaySoundAtPosition(*((void**)((void*)SOUND_PLAYING_CLASS__INSTANCE2)), 628, &soundPos, 0);
                            }
                        }
                    }else{
                        effectPos.x = (intToFloat(worldX)) + initializeFloat(0x41000000);
						effectPos.y = (intToFloat(-worldY)) - initializeFloat(0x41000000);
						effectPos.z = ((dActor_c_Struct*)((void*)self))->pos.z;

						if (!(((fBase_c_Struct*)((void*)self))->settings & 0x40000)) {
							if (self->blockType != 2) {
								SpawnEffect(getString27(), 0, &effectPos, 0, 0);
							}
                        }
                    }
                }
            }
            if (self->pattern != Fill) {
				perTilePatternFlag ^= 1;
			}

			worldX += 16;
        }
        if (self->pattern != Fill) {
			perRowPatternFlag ^= 1;
			perTilePatternFlag = perRowPatternFlag;
		}

		worldX = baseWorldX;
		worldY += 16;
    }

}