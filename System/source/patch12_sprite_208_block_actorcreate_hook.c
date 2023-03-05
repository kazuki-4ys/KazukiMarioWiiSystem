#include "common.h"
#include "actors.h"

Actor* patch12_sprite_208_block_actorcreate_hook(unsigned short classID, int settings, VEC3 *pos, void* rot, char layer, Actor *itemBlock){
	float yAdjust = initializeFloat(0x41800000);//16.0f
	if(settings & 0x40000)yAdjust = initializeFloat(0xC1800000);//-16.0f
	unsigned short extendedItemBlockClassID = (unsigned short)(itemBlock->field_0x80 >> 16);
	unsigned short extendedItemBlockSettings = (unsigned short)(itemBlock->field_0x80 & 0xFFFF);
	if(extendedItemBlockClassID == 0)return CreateActor(classID, settings, pos, rot, layer);
	pos->y += yAdjust;
	return CreateActor(extendedItemBlockClassID, extendedItemBlockSettings, pos, rot, layer);
}