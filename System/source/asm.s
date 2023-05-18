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
.global getString21
.global getString22
.global getString23
.global getString24
.global getString25
.global getString26
.global getString27
.global getU16String0
.global getU16String1
.global getU16String2
.global getPipeFixNodeCalcBin
.global ICInvalidateRange
.global initializeFloat
.global abs
.global intToFloat
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

getString21:
    mflr r12
    bl string_21
    .string "/Stage/Texture/%s.arc\0\0"
    string_21:
    mflr r3
    mtlr r12
    blr

getString22:
    mflr r12
    bl string_22
    .string "AnimTiles.bin\0\0"
    string_22:
    mflr r3
    mtlr r12
    blr

getString23:
    mflr r12
    bl string_23
    .string "T_coin_00\0\0"
    string_23:
    mflr r3
    mtlr r12
    blr

getString24:
    mflr r12
    bl string_24
    .string "T_level_hint\0\0\0"
    string_24:
    mflr r3
    mtlr r12
    blr

getString25:
    mflr r12
    bl string_25
    .long 0xE3838EE3
    .long 0x83BCE383
    .long 0x9EE383AB
    .long 0xE383A2E3
    .long 0x83BCE383
    .long 0x89256446
    .long 0x00000000
    #ノーマルモード%dF (UTF-8)
    string_25:
    mflr r3
    mtlr r12
    blr

getString26:
    mflr r12
    bl string_26
    .long 0xE382A4E3
    .long 0x83B3E383
    .long 0x95E382A3
    .long 0xE3838BE3
    .long 0x8386E382
    .long 0xA3E383BC
    .long 0xE383A2E3
    .long 0x83BCE383
    .long 0x89256446
    .long 0x00000000
    #インフィニティーモード%dF (UTF-8)
    string_26:
    mflr r3
    mtlr r12
    blr

getString27:
    mflr r12
    bl string_27
    .string "Wm_en_burst_ss\0"
    string_27:
    mflr r3
    mtlr r12
    blr

getU16String0:
    mflr r12
    bl u16string_0
    .long 0x30B330A4#コイ
    .long 0x30F33092#ンを
    .long 0x3068308B#とる
    .long 0x306AFF01#な！
    .long 0x00000000
    u16string_0:
    mflr r3
    mtlr r12
    blr

getU16String1:
    mflr r12
    bl u16string_1
    .long 0x3066304D
    .long 0x30923059
    .long 0x30793066
    .long 0x305F304A
    .long 0x305BFF01
    .long 0x00000000
    u16string_1:
    mflr r3
    mtlr r12
    blr

getU16String2:
    mflr r12
    bl u16string_2
    .long 0x30E830C3
    .long 0x30B730FC
    .long 0x304B3089
    .long 0x304A308A
    .long 0x308B3068
    .long 0x000A30BF
    .long 0x30A430DE
    .long 0x30FC3055
    .long 0x30693046
    .long 0xFF010000
    u16string_2:
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