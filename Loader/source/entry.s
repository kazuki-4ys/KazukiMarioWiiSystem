#include <ppc-asm.h>

.macro defaultInstruction
    li r0, 97
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

.global __entry
.global __end
.global getString0

.section .text.__entry
__entry:
    pushStack
    bl __main
    b __end

getString0:
    mflr r12
    bl string_0
    .string "/KazukiRes/System.bin\0\0"
    string_0:
    mflr r3
    mtlr r12
    blr

.section .text.__end
#このシンボル__endは必ず最後に配置し、コードハンドラによるbranch命令でゲームのコードに戻れるようにする
__end:
    popStack
    #最後に元の命令を配置(場合によっては最後にならないことも)
    defaultInstruction