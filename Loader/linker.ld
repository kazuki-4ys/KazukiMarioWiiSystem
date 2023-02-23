ENTRY(__entry)
SECTIONS
{
        .text 0x80001800 : {
                *(.text.__entry);
                *(.text*);
                *(.text.__end);
        }
}
