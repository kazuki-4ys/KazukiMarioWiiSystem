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

.global get_patch4_dokan_coin_spawner_asm
.global get_patch4_dokan_coin_spawner_asm_end

get_patch4_dokan_coin_spawner_asm_end:
    mflr r12
    b get_patch4_dokan_coin_spawner_asm_end_b
get_patch4_dokan_coin_spawner_asm:
    mflr r12
bl get_patch4_dokan_coin_spawner_asm_bl
patch4_dokan_coin_spawner_asm:
    pushStack
    bl patch4_dokan_coin_spawner
    stw r3, -4 (sp)
    popStack
    lwz r3, -0x84 (sp)
get_patch4_dokan_coin_spawner_asm_end_b:
bl get_patch4_dokan_coin_spawner_asm_end_bl
patch4_dokan_coin_spawner_asm_end:
get_patch4_dokan_coin_spawner_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch4_dokan_coin_spawner_asm_end_bl:
    mflr r3
    mtlr r12
    blr