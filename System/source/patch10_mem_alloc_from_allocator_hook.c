#include "common.h"

void patch10_mem_alloc_from_allocator_hook(void* allocator){
    myMemStruct *myMem = *((myMemStruct**)((void*)MY_MEM_PTR_PTR));
    if(!myMem)return;
    myMem->allocator = allocator;
}