#include "game.h"

void SoundPlayingClass__PlaySoundAtPosition(void *self, int id, Vec2 *pos, unsigned int flags){
    void (*SoundPlayingClass__PlaySoundAtPosition_ptr)(void*, int, Vec2*, unsigned int) = (void*)SOUND_PLAYING_CLASS__PLAY_SOUND_AT_POSITION;
    SoundPlayingClass__PlaySoundAtPosition_ptr(self, id, pos, flags);
}

void ConvertStagePositionToScreenPosition(Vec2 *screen, Vec *stage){
    void (*ConvertStagePositionToScreenPosition_ptr)(Vec2*, Vec*) = (void*)CONVERT_STAGE_POSITION_TO_SCREEN_POSITION;
    ConvertStagePositionToScreenPosition_ptr(screen, stage);
}

void SpawnEffect(const char* str, int a, Vec *b, s16Vec *c, Vec *d){
    void (*SpawnEffect_ptr)(const char*, int, Vec*, s16Vec*, Vec*) = (void*)SPAWN_EFFECT;
    SpawnEffect_ptr(str, a, b, c, d);
}

bool dEffectBreakMgr_c__spawnTile(void *self, Vec *position, unsigned int settings, char param){
    bool (*dEffectBreakMgr_c__spawnTile_ptr)() = (void*)D_EFFECT_BREAK_MGR_C__SPAWN_TILE;
    return dEffectBreakMgr_c__spawnTile_ptr(self, position, settings, param);
}