#include "lyt.h"

nw4r__lyt__TextBox_Struct *EmbedLayoutBase_c__findTextBoxByName(void *self, const char *name){
    nw4r__lyt__TextBox_Struct* (*EmbedLayoutBase_c__findTextBoxByName_ptr)(void*, const char*) = (void*)EMBEDLAYOUT_BASE_C__FIND_TEXT_BOX_BY_NAME;
    return EmbedLayoutBase_c__findTextBoxByName_ptr(self, name);
}

void nw4r__lyt__TextBox__SetString(nw4r__lyt__TextBox_Struct *self, const unsigned short *str, unsigned short destOffset){
    void *nw4r__lyt__TextBox__SetString_ptr_from_vtable = (void*)bytesToU32(((unsigned char*)self->s.vtable) + (31 * 4));
    void (*nw4r__lyt__TextBox__SetString_ptr)(nw4r__lyt__TextBox_Struct*, const unsigned short*, unsigned short) = nw4r__lyt__TextBox__SetString_ptr_from_vtable;
    nw4r__lyt__TextBox__SetString_ptr(self, str, destOffset);
}