#include <ppc-asm.h>

.global getString6
.global getString7
.global getString8
.global getString9
.global getString10
.global getString11
.global getString12
.global getString17
.global getString18
.global getString19
.global getString20
.global getPipeFixNodeCalcBin
.global ICInvalidateRange
.global initializeFloat
.global abs
.global floatToInt

getString6:
    mflr r12
    bl string_0
    .string "[Kazuki Mario Wii]Hello World From System.bin!!\n\0\0\0"
    string_0:
    mflr r3
    mtlr r12
    blr
	.globl ICInvalidateRange

getString7:
    mflr r12
    bl string_7
    .string "course%d.bin\0\0\0"
    string_7:
    mflr r3
    mtlr r12
    blr

getString8:
    mflr r12
    bl string_8
    .string "course%d_bgdatL%d.bin\0\0"
    string_8:
    mflr r3
    mtlr r12
    blr

getString9:
    mflr r12
    bl string_9
    .string "[Kazuki Mario Wii]Warning!! Fail to allocate memory!!\n\0"
    string_9:
    mflr r3
    mtlr r12
    blr

getString10:
    mflr r12
    bl string_10
    .string "[Kazuki Mario Wii]A maze generated!!\n\0\0"
    string_10:
    mflr r3
    mtlr r12
    blr

getString11:
    mflr r12
    bl string_11
    .string "[Kazuki Mario Wii]game->isInfinityMode = %d\n\0\0\0"
    string_11:
    mflr r3
    mtlr r12
    blr

getString12:
    mflr r12
    bl string_12
    .string "[Kazuki Mario Wii]game->curFloor = %d\n\0"
    string_12:
    mflr r3
    mtlr r12
    blr

getString17:
    mflr r12
    bl string_17
    .string "/KazukiRes/AnimTiles.bin\0\0\0"
    string_17:
    mflr r3
    mtlr r12
    blr

getString18:
    mflr r12
    bl string_18
    .string "[Kazuki Mario Wii]anim load fail\n\0\0"
    string_18:
    mflr r3
    mtlr r12
    blr

getString19:
    mflr r12
    bl string_19
    .string "[Kazuki Mario Wii]anim info incorrect\n\0"
    string_19:
    mflr r3
    mtlr r12
    blr

getString20:
    mflr r12
    bl string_20
    .string "BG_tex/%s\0\0"
    string_20:
    mflr r3
    mtlr r12
    blr

getPipeFixNodeCalcBin:
    mflr r12
    bl PipeFixNodeCalcBin
    .incbin "PipeFix_NodeCalc.bin" #絶対パスじゃないとエラー吐くかも
    PipeFixNodeCalcBin:
    mflr r3
    mtlr r12
    blr

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

floatToInt:
    mr r12, sp
    subi r12, r12, 4
    li r11, 0
    fctiw f1, f1
    stfiwx f1, r11, r12
    lwz r3, -4 (sp)
    blr