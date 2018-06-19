#include "GlobalDescriptor/DescriptorUtil.h"
static GDTItem GDT[GDT_COUNT];
SegmentDescriptor MakeDescriptor(int limit, int baseaddr, SegmentType segment_type, SystemRPL rpl) {
    SegmentDescriptor sd;
    sd.present = 1;
    sd.baseaddr_0_23 = baseaddr;
    sd.baseaddr_24_31 = baseaddr >> 24;
    int limit_4k = limit / 4096;
    sd.seglmt_0_15 = limit_4k;
    sd.seglmt_16_19 = limit_4k >> 16;
    sd.segtype4 = segment_type;
    sd.AVL = 0;
    sd.zero = 0;
    sd.g = UNIT_4K;
    sd.d = BIT_32;
    sd.s = CODE_DATA;
    sd.rpl = rpl;
    return sd;
}
void SetGDTItem(int index, GDTItem item) { memcpy(&GDT[index], &item, sizeof(GDTItem)); }
Bool InitGDT(){
    memset(GDT, 0, sizeof(GDT));
    const uint32_t memory_total_size = 32 * 1024 * 1024;
    GDTItem item1 = MakeDescriptor(memory_total_size, 0, CODE_RW, KERNEL);
    SetGDTItem(KERNEL_CODE_SEGMENT >> 3, item1);
    GDTItem item2 = MakeDescriptor(memory_total_size, 0, DATA_RW, KERNEL);
    SetGDTItem(KERNEL_DATA_SEGMENT >> 3, item2);
    static GDTDescriptor gdtr;
    gdtr.size = sizeof(GDT);
    gdtr.addr = GDT;
    asm volatile ("lgdt %0"::"m"(gdtr));
    asm volatile ("push %0;"
                  "pushl %1;"
                  "retf"::"r"(KERNEL_CODE_SEGMENT), "r"(&&NEXT_STAT));
    NEXT_STAT:
    asm volatile ("mov %0,%%ds;"
                  "mov %0,%%ss;"
                  "mov %0,%%es;"
                  "mov %0,%%fs;"
                  "mov %0,%%gs;"::"r"(KERNEL_DATA_SEGMENT));
    return TRUE;
}