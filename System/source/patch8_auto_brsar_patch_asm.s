#include <ppc-asm.h>

.global get_patch8_auto_brsar_patch_asm
.global get_patch8_auto_brsar_patch_asm_end

get_patch8_auto_brsar_patch_asm_end:
    mflr r12
    b get_patch8_auto_brsar_patch_asm_end_b
get_patch8_auto_brsar_patch_asm:
    mflr r12
bl get_patch8_auto_brsar_patch_asm_bl
patch8_auto_brsar_patch_asm:
    lis       r31, 0x7FFF
    ori       r31, r31, 0xFFFF
    stw       r31, 0x74(r29)
get_patch8_auto_brsar_patch_asm_end_b:
bl get_patch8_auto_brsar_patch_asm_end_bl
patch8_auto_brsar_patch_asm_end:
get_patch8_auto_brsar_patch_asm_bl:
    mflr r3
    mtlr r12
    blr
get_patch8_auto_brsar_patch_asm_end_bl:
    mflr r3
    mtlr r12
    blr
