ENTRY(__main)
SECTIONS
{
        .text 0x80004000 : {
                *(.text.__main);
                *(.text*);
        }
}