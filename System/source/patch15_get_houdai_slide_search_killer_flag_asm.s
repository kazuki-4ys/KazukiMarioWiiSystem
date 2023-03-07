#include <ppc-asm.h>

.macro defaultInstruction
    li r6, 20
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

.global get_patch15_get_houdai_slide_search_killer_flag_asm
.global get_patch15_get_houdai_slide_search_killer_flag_asm_end

get_patch15_get_houdai_slide_search_killer_flag_asm_end:
    mflr r12
    b get_patch15_get_houdai_slide_search_killer_flag_asm_end_b
get_patch15_get_houdai_slide_search_killer_flag_asm:
    mflr r12
bl get_patch15_get_houdai_slide_search_killer_flag_asm_bl
patch15_get_houdai_slide_search_killer_flag_asm:
    pushStack
    mr r3, r31
    bl patch15_get_houdai_slide_search_killer_flag
    popStack
    defaultInstruction
get_patch15_get_houdai_slide_search_killer_flag_asm_end_b:
bl get_patch15_get_houdai_slide_search_killer_flag_asm_end_bl
patch15_get_houdai_slide_search_killer_flag_asm_end:
get_patch15_get_houdai_slide_search_killer_flag_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch15_get_houdai_slide_search_killer_flag_asm_end_bl:
    mflr r3
    mtlr r12
    blr