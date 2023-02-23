ENTRY(__main)
SECTIONS
{
        .text 0x808DD440 : {
                *(.text.__main);
                *(.text*);
        }
}