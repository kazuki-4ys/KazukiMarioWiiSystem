#include <ppc-asm.h>

.global ICInvalidateRange
.global initializeFloat
.global abs
.global intToFloat
.global floatToInt
.global blTrickCommonEnd

ICInvalidateRange:
	cmplwi r4, 0   # zero or negative size?
	blelr
	clrlwi. r5, r3, 27  # check for lower bits set in address
	beq 1f
	addi r4, r4, 0x20 
1:
	addi r4, r4, 0x1f
	srwi r4, r4, 5
	mtctr r4
2:
	icbi r0, r3
	addi r3, r3, 0x20
	bdnz 2b
	sync
	isync
	blr

initializeFloat:
    stw r3, -4 (sp)
    lfs f1, -4 (sp)
    blr

abs:
    stfs f1, -4 (sp)
    lwz r12, -4 (sp)
    lis r11, 0x7FFF
    ori r11, r11, 0xFFFF
    and r12, r12, r11
    stw r12, -4 (sp)
    lfs f1, -4 (sp)
    blr

intToFloat:
    lis r4, 0x4330
    stw r4, -0x8 (sp)
    lis r4, 0x8000
    stw r4, -0x4 (sp)
    lfd f2, -0x8 (sp) # load magic double into f2
    xoris r3, r3, 0x8000 # flip sign bit
    stw r3, -0x4 (sp) # store lower half (upper half already stored)
    lfd f1, -0x8 (sp)
    fsub f1, f1, f2 # complete conversion
    frsp f1, f1
    blr

floatToInt:
    mr r12, sp
    subi r12, r12, 4
    li r11, 0
    fctiw f1, f1
    stfiwx f1, r11, r12
    lwz r3, -4 (sp)
    blr

blTrickCommonEnd:
    mflr r3
    mtlr r12
    blr