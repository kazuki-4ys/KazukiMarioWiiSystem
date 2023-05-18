#include <ppc-asm.h>

.macro defaultInstruction
    stw r0, 0x8B4 (r30)
.endm

.global get_patch20_zurumode_itemstock99_asm
.global get_patch20_zurumode_itemstock99_asm_end

get_patch20_zurumode_itemstock99_asm_end:
    mflr r12
    b get_patch20_zurumode_itemstock99_asm_end_b
get_patch20_zurumode_itemstock99_asm:
    mflr r12
bl get_patch20_zurumode_itemstock99_asm_bl
patch20_zurumode_itemstock99_asm:
    li r0, 99
    defaultInstruction
get_patch20_zurumode_itemstock99_asm_end_b:
bl get_patch20_zurumode_itemstock99_asm_end_bl
patch20_zurumode_itemstock99_asm_end:
get_patch20_zurumode_itemstock99_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch20_zurumode_itemstock99_asm_end_bl:
    mflr r3
    mtlr r12
    blr
