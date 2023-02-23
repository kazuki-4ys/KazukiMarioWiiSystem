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

.global get_patch7_brstm_hijacker_asm
.global get_patch7_brstm_hijacker_asm_end
.global getString0
.global getString1
.global getString2
.global getString3
.global getString4
.global getString5

get_patch7_brstm_hijacker_asm_end:
    mflr r12
    b get_patch7_brstm_hijacker_asm_end_b
get_patch7_brstm_hijacker_asm:
    mflr r12
bl get_patch7_brstm_hijacker_asm_bl
patch7_brstm_hijacker_asm:
    pushStack
    bl patch7_brstm_hijacker
    stw r3, -4 (sp)
    popStack
    lwz r3, -0x84 (sp)
get_patch7_brstm_hijacker_asm_end_b:
bl get_patch7_brstm_hijacker_asm_end_bl
patch7_brstm_hijacker_asm_end:
get_patch7_brstm_hijacker_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch7_brstm_hijacker_asm_end_bl:
    mflr r3
    mtlr r12
    blr

getString0:
    mflr r12
    bl string_0
    .string "/Sound/stream/BGM_SUICHU.32.brstm\0\0"
    string_0:
    mflr r3
    mtlr r12
    blr

getString1:
    mflr r12
    bl string_1
    .string "/Sound/stream/STRM_BGM_CHIJOU.brstm\0\0\0\0"
    string_1:
    mflr r3
    mtlr r12
    blr

getString2:
    mflr r12
    bl string_2
    .string "/Sound/stream/BGM_SUICHU_fast.32.brstm\0"
    string_2:
    mflr r3
    mtlr r12
    blr

getString3:
    mflr r12
    bl string_3
    .string "/Sound/stream/STRM_BGM_CHIJOU_FAST.brstm\0\0\0"
    string_3:
    mflr r3
    mtlr r12
    blr

getString4:
    mflr r12
    bl string_4
    .string "/Sound/stream/%02x.brstm\0\0\0"
    string_4:
    mflr r3
    mtlr r12
    blr

getString5:
    mflr r12
    bl string_5
    .string "/Sound/stream/%02x_fast.brstm\0\0"
    string_5:
    mflr r3
    mtlr r12
    blr