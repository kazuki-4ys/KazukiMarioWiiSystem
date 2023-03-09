#include "common.h"

void *my_malloc(unsigned int length){
    void (*OSReport)(const char*, ...) = (void*)OSREPORT;
    void*(*AllocFromGameHeap1)(unsigned int) = (void*)ALLOC_FROM_GAME_HEAP;
    void *buf = AllocFromGameHeap1(length);
    if(!buf){
        OSReport(getString9());
        return NULL;
    }
    return buf;
}

void my_free(void *ptr){
    void (*FreeFromGameHeap1)(void*) = (void*)FREE_FROM_GAME_HEAP;
    FreeFromGameHeap1(ptr);
}

void *my_malloc_via_allocator(unsigned int length){
    void (*OSReport)(const char*, ...) = (void*)OSREPORT;
    void*(*MEMAllocFromAllocator)(void*, unsigned int) = (void*)MEM_ALLOC_FROM_ALLOCATOR;
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return NULL;
    void *dest = MEMAllocFromAllocator(myMem->allocator, length);
    if(!dest){
        OSReport(getString9());
        return NULL;
    }
    return dest;
}

Actor *CreateActor(unsigned short classID, int settings, VEC3 *pos, void* rot, char layer){
    Actor* (*create_actor_ptr)(unsigned short classID, int settings, VEC3 *pos, void* rot, char layer) = (void*)CREATE_ACTOR;
    return create_actor_ptr(classID, settings, pos, rot, layer);
}

void setStageTimerRaw(int time){
    unknownStageTimerStruct *ustsp = *((unknownStageTimerStruct**)((void*)UNKNOWN_STAGE_TIMER_STRUCT_PTR_PTR));
    if(!ustsp)return;
    ustsp->stageTimer = time;
}

unsigned int random(unsigned int max){
    unsigned int(*GenerateRandomNumber)(int) = (void*)GENERATE_RANDOM_NUMBER;
    return GenerateRandomNumber(max);
}

void u32ToBytes(unsigned char *mem, unsigned int val){
    *mem = (val >> 24);
    *(mem + 1) = ((val >> 16) & 0xFF);
    *(mem + 2) = ((val >> 8) & 0xFF);
    *(mem + 3) = (val & 0xFF);
}

void u16ToBytes(unsigned char *mem, unsigned short val){
    *mem = (val >> 8);
    *(mem + 1) = (val & 0xFF);
}

unsigned short bytesToU16(unsigned char *mem){
    return (*mem << 8) | *(mem + 1);
}

unsigned int bytesToU32(unsigned char *mem){
    return (*mem << 24) | (*(mem + 1) << 16) | (*(mem + 2) << 8) | *(mem + 3);
}

/*void *my_memset(void *buf, int ch, unsigned int n){
    unsigned char *bufChar = (unsigned char*)buf;
    for(int i = 0;i < n;i++)*(buf + i) = (unsigned char)ch;
    return buf;
}*/

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

void makeInArchiveCourseFileName(char *dest, unsigned int destSize, int area, int layer){
    int (*sprintf)(char * buf, const char * format, ...) = (void*)SPRINTF;
    //my_memset(dest, 0, destSize);
    if(layer < 0){
        sprintf(dest, getString7(), area);
    }else{
        sprintf(dest, getString8(), area, layer);
    }
}

unsigned char *getARCChildFilePointer(unsigned char* arcFile, const char *targetFile, unsigned int *targetFileSize){
    int (*strcmp)(const char*, const char*) = (void*)STRCMP;
    if(bytesToU32(arcFile) != 0x55AA382D)return NULL;//ARCファイルじゃない
    unsigned char *firstNode = bytesToU32(arcFile + 0x4) + arcFile;
    unsigned int nodeCount = bytesToU32(firstNode + 0x8);
    unsigned char *stringPool = nodeCount * 0xC + firstNode;
    unsigned char *curNode = firstNode;
    unsigned int curNodeIndex = 0;
    while(curNodeIndex < nodeCount){
        if(!strcmp((bytesToU32(curNode) & 0xFFFFFF) + stringPool, targetFile)){
            if(targetFileSize)*targetFileSize = bytesToU32(curNode + 8);
            //return bytesToU32(curNode + 4) + filesMass;
            return bytesToU32(curNode + 4) + arcFile;
        }
        curNodeIndex++;
        curNode += 0xC;
    }
    return NULL;//targetFileが見つからなかった
}

unsigned char *getCourseBinBlock(unsigned char *courseBin, unsigned int blockIndex, unsigned int *blockSize){
    return bytesToU32(courseBin + 4 * blockIndex * 2) + courseBin;
    *blockSize = bytesToU32(courseBin + 4 * (blockIndex * 2 + 1));
}

void newerPipeFix(void){
    //from newerSMBW
    //https://github.com/Newer-Team/NewerSMBW/blob/cw/Kamek/bugfixes.yaml
    unsigned char *pipeFixNodeCalcBin = getPipeFixNodeCalcBin();
    unsigned int getPipeFixNodeCalcBinSize = 0x40;
    for(unsigned int i = 0;i < getPipeFixNodeCalcBinSize;i++)*(((unsigned char*)((void*)0x800508F8)) + i) = *(pipeFixNodeCalcBin + i);
    u32ToBytes((void*)0x80050A5C, 0x88030013);
    u32ToBytes((void*)0x80050A60, 0x2C000000);
    u32ToBytes((void*)0x80050A68, 0x2C000001);
    u32ToBytes((void*)0x80050A70, 0x2C000002);
    u32ToBytes((void*)0x80050A78, 0x2C000003);
    u32ToBytes((void*)0x80050A88, 0x389F065C);
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
    injectBranchPatch((void*)0x8019F510, get_patch9_arc_open_hook_asm(), get_patch9_arc_open_hook_asm_end(), true);
    injectBranchPatch((void*)0x801D5350, get_patch10_mem_alloc_from_allocator_hook_asm(), get_patch10_mem_alloc_from_allocator_hook_asm_end(), true);
    injectBranchPatch((void*)0x80068f54, get_patch11_bugmario_actorcreate_hook_asm(), get_patch11_bugmario_actorcreate_hook_asm_end(), true);
    injectBranchPatch((void*)0x80022AAC, get_patch12_sprite_208_block_actorcreate_hook_asm(), get_patch12_sprite_208_block_actorcreate_hook_asm_end(), true);
    injectBranchPatch((void*)0x80087698, get_patch13_newer_do_tiles_asm(), get_patch13_newer_do_tiles_asm_end(), true);
    injectBranchPatch((void*)0x80087508, get_patch14_newer_destroy_tiles_asm(), get_patch14_newer_destroy_tiles_asm_end(), true);
    injectBranchPatch((void*)0x8008e5c0, get_patch17_get_cur_area_asm(), get_patch17_get_cur_area_asm_end(), true);
    u32ToBytes((void*)0x80087544, 0x38801000);//AnimTileFrameHeapPatch
    newerPipeFix();
}