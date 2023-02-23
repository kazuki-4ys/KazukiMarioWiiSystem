#include <ppc-asm.h>

.macro pushStack
    stwu sp, -0x80 (sp)#124 + パディング
    mflr r0
    stw r0, 0x84 (sp)
    stmw r3, 8 (sp)
.endm

.macro popStack
    lmw r3, 8 (sp)
    lwz r0, 0x84 (sp)
    mtlr r0
    addi sp, sp, 0x80
.endm

.global get_patch5_coin_lakitu_spawner_asm
.global get_patch5_coin_lakitu_spawner_asm_end

get_patch5_coin_lakitu_spawner_asm_end:
    mflr r12
    b get_patch5_coin_lakitu_spawner_asm_end_b
get_patch5_coin_lakitu_spawner_asm:
    mflr r12
bl get_patch5_coin_lakitu_spawner_asm_bl
patch5_coin_lakitu_spawner_asm:
    pushStack
    bl patch5_coin_lakitu_spawner
    li r4, 83
    cmpwi r3, 1
    bne not_replace_rakitu_to_coin_lakitu
    li r4, 84
    not_replace_rakitu_to_coin_lakitu:
    stw r4, -4 (sp)
    popStack
    lwz r3, -0x84 (sp)
get_patch5_coin_lakitu_spawner_asm_end_b:
bl get_patch5_coin_lakitu_spawner_asm_end_bl
patch5_coin_lakitu_spawner_asm_end:
get_patch5_coin_lakitu_spawner_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch5_coin_lakitu_spawner_asm_end_bl:
    mflr r3
    mtlr r12
    blr