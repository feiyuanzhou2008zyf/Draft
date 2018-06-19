#pragma once
#ifndef DESCRIPTOR_UTIL_H
#define DESCRIPTOR_UTIL_H
#include "../Kernel/CarbonDefine.h"
#include "../Kernel/CarbonKernelPrintUtil.h"
#include "../Kernel/KernelInlineAssembly.h"
#include "../RuntimeLibrary/StringLibrary.h"
#define DA_32 0x4000
#define DA_16 0x0000
#define DA_LIMIT_4K 0x8000
#define DA_LIMIT_byte 0x0000
#define DA_DPL0 0x00
#define DA_DPL1 0x20
#define DA_DPL2 0x40
#define DA_DPL3 0x60
#define DA_DR 0x90
#define DA_DRW 0x92
#define DA_DRWA 0x93
#define DA_C 0x98
#define DA_CR 0x9A
#define DA_CCO 0x9C
#define DA_CCOR 0x9E
#define DA_LDT 0x82
#define DA_TaskGate 0x85
#define DA_386TSS 0x89
#define DA_386CGate 0x8C
#define DA_386IGate 0x8E
#define DA_386TGate 0x8F
#define SA_RPL0 0
#define SA_RPL1 1
#define SA_RPL2 2
#define SA_RPL3 3
#define SA_TIG 0
#define SA_TIL 4
#define GDT_COUNT 1024
#define GLOBAL_KERNEL_SEGMENT(n) (uint16_t)(((n) << 3) + 0b000)
#define GLOBAL_USER_SEGMENT(n) (uint16_t)(((n) << 3) + 0b011)
#define LOCAL_KERNEL_SEGMENT(n) (uint16_t)(((n) << 3) + 0b100)
#define LOCAL_USER_SEGMENT(n) (uint16_t)(((n) << 3) + 0b111)
#define KERNEL_CODE_SEGMENT GLOBAL_KERNEL_SEGMENT(1)
#define KERNEL_DATA_SEGMENT GLOBAL_KERNEL_SEGMENT(2)
typedef enum __segment_type__ {
    DATA_R = 0b0000,
    DATA_RW = 0b0010,
    CODE_R = 0b1000,
    CODE_RW = 0b1010
} SegmentType;
typedef enum __S__ {
    SYSTEM = 0,
    CODE_DATA = 1
} S;
typedef enum __D__ {
    BIT_32 = 1,
    BIT_16 = 0
} D;
typedef enum __G__ {
    UNIT_1BYTE = 0,
    UNIT_4K = 1
} G;
typedef struct __descriptor__ {
    uint32_t seglmt_0_15: 16;
    uint32_t baseaddr_0_23: 24;
    SegmentType segtype4: 4;
    S s: 1;
    SystemRPL rpl: 2;
    Bool present: 1;
    uint32_t seglmt_16_19: 4;
    uint32_t AVL: 1;
    uint32_t zero: 1;
    D d: 1;
    G g: 1;
    uint32_t baseaddr_24_31: 8;
} SegmentDescriptor;
typedef struct __gate__ {
    uint16_t offset1;
    uint16_t selector;
    uint16_t attr;
    uint16_t offset2;
} Gate;
typedef struct __gdt_descriptor__ {
    uint16_t size;
    void *addr;
} GDTDescriptor;
typedef SegmentDescriptor GDTItem;
SegmentDescriptor MakeDescriptor(int limit, int baseaddr, SegmentType segment_type, SystemRPL rpl);
void SetGDTItem(int index, GDTItem item);
Bool InitGDT();
#endif // DESCRIPTOR_UTIL_H