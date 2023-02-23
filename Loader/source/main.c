#define ALREADY_LAUNCHED_FLAG 0x800001B8
#define EGG_HEAP_ALLOC 0x802B8AD0
#define ARCHIVE_HEAP 0x8042A16C
#define DVD_CONVERT_PATH_TO_ENTRY_NUM 0x801CA490
#define DVD_FAST_OPEN 0x801CA7A0
#define DVD_READ_PRIO 0x801CA930
#define DVD_CLOSE 0x801CA810
#define TEST_FLAG 0x800001B4

typedef struct{
    unsigned char unk0[0x34];
    unsigned int length;
    //0x38
    unsigned char unk1[4];
    //全部で0x3Cバイト
} DVDFileInfo;

const char *getString0(void);

void *my_malloc(unsigned int length){
    void*(*AllocFromGameHeap1)(unsigned int) = (void*)0x801626D0;
    unsigned int buf = (unsigned int)AllocFromGameHeap1(length + 0x20);
    if((buf & 0x1F) == 0)return (void*)buf;
    return (void*)((buf + 0x20) & (~0x1F));
}

void __main(void){
    void (*systemBinEntry)(void);
    int (*DVDConvertPathToEntryNum)(const char*) = (void*)DVD_CONVERT_PATH_TO_ENTRY_NUM;
    int (*DVDFastOpen)(int, DVDFileInfo*) = (void*)DVD_FAST_OPEN;
    int (*DVDReadPrio)(DVDFileInfo*, void*, unsigned int, unsigned int, unsigned int) = (void*)DVD_READ_PRIO;
    void (*DVDClose)(DVDFileInfo*) = (void*)DVD_CLOSE;
	unsigned char *alreadyLaunchedFlag = (void*)ALREADY_LAUNCHED_FLAG;
	if(*alreadyLaunchedFlag)return;
	*alreadyLaunchedFlag = 1;
	DVDFileInfo fi;
	int result = DVDFastOpen(DVDConvertPathToEntryNum(getString0()), &fi);
    if(!result)return;
    unsigned int *testFlag = (void*)TEST_FLAG;
    void *systemBin = my_malloc(fi.length);
    *testFlag = (unsigned int)systemBin;
    DVDReadPrio(&fi, systemBin, fi.length, 0, 2);
    DVDClose(&fi);
    systemBinEntry = systemBin;
    systemBinEntry();
}