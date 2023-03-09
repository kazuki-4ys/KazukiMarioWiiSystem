#include <ppc-asm.h>

.macro defaultInstruction
    stwu sp, -0x10 (sp)
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

.global get_patch17_get_cur_area_asm
.global get_patch17_get_cur_area_asm_end

get_patch17_get_cur_area_asm_end:
    mflr r12
    b get_patch17_get_cur_area_asm_end_b
get_patch17_get_cur_area_asm:
    mflr r12
bl get_patch17_get_cur_area_asm_bl
patch17_get_cur_area_asm:
    pushStack
    bl patch17_get_cur_area
    popStack
    defaultInstruction
get_patch17_get_cur_area_asm_end_b:
bl get_patch17_get_cur_area_asm_end_bl
patch17_get_cur_area_asm_end:
get_patch17_get_cur_area_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch17_get_cur_area_asm_end_bl:
    mflr r3
    mtlr r12
    blr
