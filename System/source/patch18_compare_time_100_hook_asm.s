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

.global get_patch18_compare_time_100_hook_asm
.global get_patch18_compare_time_100_hook_asm_end

get_patch18_compare_time_100_hook_asm_end:
    mflr r12
    b get_patch18_compare_time_100_hook_asm_end_b
get_patch18_compare_time_100_hook_asm:
    mflr r12
bl get_patch18_compare_time_100_hook_asm_bl
patch18_compare_time_100_hook_asm:
    mr r11, r0
    pushStack
    bl patch18_compare_time_100_hook
    stw r3, -4 (sp)
    popStack
    mr r0, r11
    lwz r12, -0x84 (sp)
    cmpwi r12, 0
    beq not_01_03
    li r12, 1
    cmpwi r12, 0
    b s_01_03
    not_01_03:
    cmpwi r0, 100
    s_01_03:

get_patch18_compare_time_100_hook_asm_end_b:
bl get_patch18_compare_time_100_hook_asm_end_bl
patch18_compare_time_100_hook_asm_end:
get_patch18_compare_time_100_hook_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch18_compare_time_100_hook_asm_end_bl:
    mflr r3
    mtlr r12
    blr
