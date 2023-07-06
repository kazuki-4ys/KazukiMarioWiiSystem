#include <ppc-asm.h>

.global getString0
.global getString1
.global getString2
.global getString3
.global getString4
.global getString5
.global getString6
.global getString7
.global getString8
.global getString9
.global getString10
.global getString11
.global getString12
.global getString13
.global getString14
.global getString15
.global getString16
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

getString6:
    mflr r12
    bl blTrickCommonEnd
    .string "[Kazuki Mario Wii]Hello World From System.bin!!\n\0\0\0"

getString7:
    mflr r12
    bl blTrickCommonEnd
    .string "course%d.bin\0\0\0"

getString8:
    mflr r12
    bl blTrickCommonEnd
    .string "course%d_bgdatL%d.bin\0\0"

getString9:
    mflr r12
    bl blTrickCommonEnd
    .string "[Kazuki Mario Wii]Warning!! Fail to allocate memory!!\n\0"

getString10:
    mflr r12
    bl blTrickCommonEnd
    .string "[Kazuki Mario Wii]A maze generated!!\n\0\0"

getString11:
    mflr r12
    bl blTrickCommonEnd
    .string "[Kazuki Mario Wii]game->isInfinityMode = %d\n\0\0\0"

getString12:
    mflr r12
    bl blTrickCommonEnd
    .string "[Kazuki Mario Wii]game->curFloor = %d\n\0"

getString17:
    mflr r12
    bl blTrickCommonEnd
    .string "/KazukiRes/AnimTiles.bin\0\0\0"

getString18:
    mflr r12
    bl blTrickCommonEnd
    .string "[Kazuki Mario Wii]anim load fail\n\0\0"

getString19:
    mflr r12
    bl blTrickCommonEnd
    .string "[Kazuki Mario Wii]anim info incorrect\n\0"

getString20:
    mflr r12
    bl blTrickCommonEnd
    .string "BG_tex/%s\0\0"

getString21:
    mflr r12
    bl blTrickCommonEnd
    .string "/Stage/Texture/%s.arc\0\0"

getString22:
    mflr r12
    bl blTrickCommonEnd
    .string "AnimTiles.bin\0\0"

getString23:
    mflr r12
    bl blTrickCommonEnd
    .string "T_coin_00\0\0"

getString24:
    mflr r12
    bl blTrickCommonEnd
    .string "T_level_hint\0\0\0"

getString25:
    mflr r12
    bl blTrickCommonEnd
    .long 0xE3838EE3
    .long 0x83BCE383
    .long 0x9EE383AB
    .long 0xE383A2E3
    .long 0x83BCE383
    .long 0x89256446
    .long 0x00000000
    #ノーマルモード%dF (UTF-8)

getString26:
    mflr r12
    bl blTrickCommonEnd
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

getString27:
    mflr r12
    bl blTrickCommonEnd
    .string "Wm_en_burst_ss\0"

getU16String0:
    mflr r12
    bl blTrickCommonEnd
    .long 0x30B330A4#コイ
    .long 0x30F33092#ンを
    .long 0x3068308B#とる
    .long 0x306AFF01#な！
    .long 0x00000000

getU16String1:
    mflr r12
    bl blTrickCommonEnd
    .long 0x3066304D
    .long 0x30923059
    .long 0x30793066
    .long 0x305F304A
    .long 0x305BFF01
    .long 0x00000000

getU16String2:
    mflr r12
    bl blTrickCommonEnd
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

getPipeFixNodeCalcBin:
    mflr r12
    bl blTrickCommonEnd
    .incbin "PipeFix_NodeCalc.bin" #絶対パスじゃないとエラー吐くかも

getString0:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/BGM_SUICHU.32.brstm\0\0"

getString1:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/STRM_BGM_CHIJOU.brstm\0\0\0\0"

getString13:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/athletic_lr.n.32.brstm\0\0\0"

getString14:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/STRM_BGM_CHIKA.brstm\0"

getString2:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/BGM_SUICHU_fast.32.brstm\0"

getString3:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/STRM_BGM_CHIJOU_FAST.brstm\0\0\0"

getString4:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/%02x.brstm\0\0\0"

getString5:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/%02x_fast.brstm\0\0"

getString15:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/athletic_fast_lr.n.32.brstm\0\0"

getString16:
    mflr r12
    bl blTrickCommonEnd
    .string "/Sound/stream/STRM_BGM_CHIKA_FAST.brstm\0\0\0\0"