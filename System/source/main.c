#include "common.h"

void u32ToBytes(unsigned char *mem, unsigned int val){
    *mem = (val >> 24);
    *(mem + 1) = ((val >> 16) & 0xFF);
    *(mem + 2) = ((val >> 8) & 0xFF);
    *(mem + 3) = (val & 0xFF);
}

unsigned int bytesToU32(unsigned char *mem){
    return (*mem << 24) | (*(mem + 1) << 16) | (*(mem + 2) << 8) | *(mem + 3);
}

unsigned int makeBranchInstructionByAddrDelta(int addrDelta){
    unsigned int instruction = 0;
    if(addrDelta < 0){
        instruction = addrDelta + 0x4000000;
    }else{
        instruction = addrDelta;
    }
    instruction |= 0x48000000;
    return instruction;
}

void injectBranchPatch(void *targetAddr, void *codeStart, void *codeEnd, bool doIcInvalidate){
    //inject code like C2 code type
    u32ToBytes((unsigned char*)codeEnd - 4, makeBranchInstructionByAddrDelta((unsigned int)targetAddr + 4 - ((unsigned int)codeEnd - 4)));
    if(doIcInvalidate)ICInvalidateRange((void*)(((unsigned int)codeEnd - 4) & (~0x1F)), 0x20);
    u32ToBytes(targetAddr, makeBranchInstructionByAddrDelta(codeStart - targetAddr));
    if(doIcInvalidate)ICInvalidateRange((void*)((unsigned int)targetAddr & (~0x1F)), 0x20);
}

void __main(void){
    void (*OSReport)(const char*, ...) = (void*)0x8015F540;
    OSReport(getString6());
    injectBranchPatch((void*)0x801C4CCC, get_patch1_run_1fr_asm(), get_patch1_run_1fr_asm_end(), true);
    injectBranchPatch((void*)0x80060438, get_patch2_coin_killer_asm(), get_patch2_coin_killer_asm_end(), true);
    injectBranchPatch((void*)0x800e3948, get_patch3_save_timer_ptr_asm(), get_patch3_save_timer_ptr_asm_end(), true);
    injectBranchPatch((void*)0x8008e5e4, get_patch6_get_music_id_asm(), get_patch6_get_music_id_asm_end(), true);
    injectBranchPatch((void*)0x8026917c, get_patch7_brstm_hijacker_asm(), get_patch7_brstm_hijacker_asm_end(), true);
    injectBranchPatch((void*)0x802691c0, get_patch8_auto_brsar_patch_asm(), get_patch8_auto_brsar_patch_asm_end(), true);
}