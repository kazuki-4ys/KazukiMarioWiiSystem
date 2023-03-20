//from newerSMBW
//https://github.com/Newer-Team/NewerSMBW/blob/cw/Kamek/include/game.h

#ifndef _LYT_H_
#define _LYT_H_

#define EMBEDLAYOUT_BASE_C__FIND_TEXT_BOX_BY_NAME 0x80007320

typedef struct{
 	unsigned char r;			/*!< Red color component. */
 	unsigned char g;			/*!< Green color component. */
 	unsigned char b;			/*!< Blue alpha component. */
	unsigned char a;			/*!< Alpha component. If a function does not use the alpha value, it is safely ignored. */
}GXColor;

typedef struct{
    void *vtable;
    unsigned char data[0xB0];
    float _B4;
    unsigned char alpha;
    unsigned char effectiveAlpha;
    unsigned char origin;
    unsigned char flag;
    char name[0x11];
	char userdata[9];
    unsigned char paneIsOwnedBySomeoneElse;
	unsigned char _D7;
}nw4r__lyt__Pane_Struct;

typedef struct{
    nw4r__lyt__Pane_Struct s;
    unsigned short *stringBuf;
    GXColor colour1, colour2;
    void *font;
    float fontSizeX, fontSizeY;
	float lineSpace, charSpace;
    void *tagProc;
    unsigned short bufferLength;
    unsigned short stringLength;
    unsigned char alignment;
    unsigned char flags;
}nw4r__lyt__TextBox_Struct;

nw4r__lyt__TextBox_Struct *EmbedLayoutBase_c__findTextBoxByName(void *self, const char *name);
void nw4r__lyt__TextBox__SetString(nw4r__lyt__TextBox_Struct *self, const unsigned short *str, unsigned short destOffset);

#endif//_LYT_H_