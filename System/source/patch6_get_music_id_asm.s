#include <ppc-asm.h>

.macro defaultInstruction
    blr
.endm

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

.global get_patch6_get_music_id_asm
.global get_patch6_get_music_id_asm_end

get_patch6_get_music_id_asm_end:
    mflr r12
    b get_patch6_get_music_id_asm_end_b
get_patch6_get_music_id_asm:
    mflr r12
bl get_patch6_get_music_id_asm_bl
patch6_get_music_id_asm:
    pushStack
    bl patch6_get_music_id
    stw r3, -4 (sp)
    popStack
    #最後に元の命令を配置(場合によっては最後にならないことも)
    lwz r3, -0x84 (sp)
    defaultInstruction
get_patch6_get_music_id_asm_end_b:
bl get_patch6_get_music_id_asm_end_bl
patch6_get_music_id_asm_end:
get_patch6_get_music_id_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch6_get_music_id_asm_end_bl:
    mflr r3
    mtlr r12
    blr