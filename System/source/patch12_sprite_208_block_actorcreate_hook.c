#include "common.h"
#include "actors.h"

Actor* patch12_sprite_208_block_actorcreate_hook(unsigned short classID, int settings, VEC3 *pos, void* rot, char layer, Actor *itemBlock){
	float yAdjust = initializeFloat(0x41800000);//16.0f
	if(settings & 0x40000)yAdjust = initializeFloat(0xC1800000);//-16.0f
	unsigned short extendedItemBlockClassID = (unsigned short)(itemBlock->field_0x80 >> 16);
	unsigned short extendedItemBlockSettings = (unsigned short)(itemBlock->field_0x80 & 0xFFFF);
	if(extendedItemBlockClassID == 0)return CreateActor(classID, settings, pos, rot, layer);
	Actor *act;
	switch(extendedItemBlockClassID){
		case CHUKAN_POINT:
			pos->y += initializeFloat(0x41800000);
			return CreateActor(extendedItemBlockClassID, extendedItemBlockSettings, pos, rot, layer);
		case EN_KILLER_HOUDAI_SLIDE:
			pos->y += initializeFloat(0x41800000);
			act = CreateActor(extendedItemBlockClassID, (extendedItemBlockSettings & 0x7FFF), pos, rot, layer);
			if(extendedItemBlockSettings & 0x8000)act->field_0x80 = 1;
			return act;
		default:
			pos->y += yAdjust;
			return CreateActor(extendedItemBlockClassID, extendedItemBlockSettings, pos, rot, layer);
	}
	return CreateActor(extendedItemBlockClassID, extendedItemBlockSettings, pos, rot, layer);
}