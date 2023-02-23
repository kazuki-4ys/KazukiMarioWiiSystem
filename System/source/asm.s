#include <ppc-asm.h>

.global getString6
.global ICInvalidateRange

getString6:
    mflr r12
    bl string_0
    .string "Hello World From System.bin!!\0\0"
    string_0:
    mflr r3
    mtlr r12
    blr
	.globl ICInvalidateRange
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