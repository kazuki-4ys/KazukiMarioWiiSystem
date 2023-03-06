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

.global get_patch14_newer_destroy_tiles_asm
.global get_patch14_newer_destroy_tiles_asm_end

get_patch14_newer_destroy_tiles_asm_end:
    mflr r12
    b get_patch14_newer_destroy_tiles_asm_end_b
get_patch14_newer_destroy_tiles_asm:
    mflr r12
bl get_patch14_newer_destroy_tiles_asm_bl
patch14_newer_destroy_tiles_asm:
    pushStack
    bl patch14_newer_destroy_tiles
    popStack
    defaultInstruction
get_patch14_newer_destroy_tiles_asm_end_b:
bl get_patch14_newer_destroy_tiles_asm_end_bl
patch14_newer_destroy_tiles_asm_end:
get_patch14_newer_destroy_tiles_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch14_newer_destroy_tiles_asm_end_bl:
    mflr r3
    mtlr r12
    blr