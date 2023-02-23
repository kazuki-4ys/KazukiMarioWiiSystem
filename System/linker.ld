ENTRY(__main)
SECTIONS
{
        .text 0x808DD440 : {
                *(.text.__main);
                *(.text*);
        }
        EggHeapAlloc = 0x80229734;
        EggHeapFree = 0x80229AA4;
        OSReport = 0x801A24F0;
}