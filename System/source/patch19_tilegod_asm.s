#include <ppc-asm.h>

.set TileTable, 0x802EF7D8
.global get_daChengeBlock_c__doStuff_asm
.global get_NEW_GetTileFromTileTable
.global get_Special_end
get_daChengeBlock_c__doStuff_asm:
    mflr r12
bl get_Special_end_bl
daChengeBlock_c__doStuff_asm:
	b daChengeBlock_c__doStuff

get_Special_end:
mflr r12
b ExitFromTileGodHack_0
get_NEW_GetTileFromTileTable:
mflr r12
bl get_Special_end_bl
NEW_GetTileFromTileTable:
	andi. r0, r3, 0x8000
	beq UseRegular
	
	li r4, 0x7FFF
	and r3, r3, r4
	blr
	
UseRegular:
	lis r4, TileTable@h
	ori r4, r4, TileTable@l
	
	clrlslwi r0, r3, 16, 1
	lhzx r3, r4, r0
	blr


.global TileGodHack
TileGodHack:
	lwz r4, 4(r3)          # Load settings
	extrwi. r0, r4, 1, 16  # Get and check the "use regular tile" flag
	extrwi r4, r4, 3, 17   # Get the tile number OR tileset number
	bne Special
	
	bl TileGodTiles
	slwi r4, r4, 1
	lhzx r25, r3, r4
	
	b ExitFromTileGodHack_0
	
Special:
	lwz r3, 4(r3)          # Load settings
	srwi r3, r3, 20        # Get tile number
	andi. r3, r3, 0xFF     # Cut off top nybble
	slwi r4, r4, 8         # Shift tileset number
	or r3, r3, r4         # Add tileset number
	ori r25, r3, 0x8000    # Add "get regular tile" flag
	
ExitFromTileGodHack_0:
    bl get_Special_end_bl
	get_Special_end_bl:
    mflr r3
    mtlr r12
    blr

TileGodTiles:
    mflr r12
    bl TileGodTiles_0
	.short 0x7C, 0x02, 0x0C, 0x7B, 0x0F, 0x00
    TileGodTiles_0:
    mflr r3
    mtlr r12
    blr