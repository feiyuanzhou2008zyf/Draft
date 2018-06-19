#include "Interrupt/InterruptService.h"
typedef struct __handler_info__ {
    int index;
    intr_hander handler;
    GateType type;
} HandlerInfo;
static IDTItem IDT[INTERRUPT_GATE_COUNT];
void SetIDTItem(int index, IDTItem item) { memcpy(&IDT[index], &item, sizeof(IDTItem)); }
IDTItem MakeIDTItem(intr_hander callback, GateType gatetype) {
    uint32_t func = (uint32_t)callback;
    IDTItem item;
    item.segment_selector = KERNEL_CODE_SEGMENT;
    item.offset_0_15 = (uint16_t)func;
    item.offset_16_31 = (uint16_t)(func >> 16);
    item.present = 1;
    item.rpl = KERNEL;
    item.zero = 0;
    item.type = gatetype;
    return item;
}
static HandlerInfo handler_map[] = {
        {0,  divide_error, TRAP},
        {1,  single_step_exception, TRAP},
        {2,  nmi, TRAP},
        {3,  breakpoint_exception, TRAP},
        {4,  overflow, TRAP},
        {5,  bounds_check,},
        {6,  inval_opcode, TRAP},
        {7,  copr_not_available,},
        {8,  double_fault, TRAP},
        {9,  copr_seg_overrun, TRAP},
        {10, inval_tss, TRAP},
        {11, segment_not_present, TRAP},
        {12, stack_exception, TRAP},
        {13, general_protection, TRAP},
        {14, page_fault, TRAP},
        {16, copr_error, TRAP},
        {32, hwint00, INT},
        {33, hwint01, INT},
        {34, hwint02, INT},
        {35, hwint03, INT},
        {36, hwint04, INT},
        {37, hwint05, INT},
        {38, hwint06, INT},
        {39, hwint07, INT},
        {40, hwint08, INT},
        {41, hwint09, INT},
        {42, hwint10, INT},
        {43, hwint11, INT},
        {44, hwint12, INT},
        {45, hwint13, INT},
        {46, hwint14, INT},
        {47, hwint15, INT},
        {-1,0,0}
};
Bool InitIDT() {
    for (int i = 0; handler_map[i].index != -1; i++) {
        IDTItem item = MakeIDTItem(handler_map[i].handler,handler_map[i].type);
        SetIDTItem(handler_map[i].index,item);
    }
    InitPIC();
    static IDTDescriptor idtr;
    idtr.addr = IDT;
    idtr.size = sizeof(IDT);
    asm volatile ("lidt %0"::"m"(idtr));
    return TRUE;
}
void ShowIDTTable(int begin, int end) {
    uint64_t idt_operand = (uint64_t)0;
    asm volatile ("sidt %0":"=m"(idt_operand));
    KernelPrint("\nIDT_address:0x%08X  IDT_size:0x%08X\n", (uint32_t)(idt_operand >> 16), (uint32_t)(idt_operand & 0xFFFF));
    KernelPrint("index\t address selector-offset\t P DPL S TYPE param\n");
    uint32_t tmppp = (uint32_t)(idt_operand >> 16);
    Gate *tmp = (Gate *) tmppp;
    uint16_t len = (uint16_t) (((idt_operand + 1) & 0xFFFF) / 8);
    uint32_t endtmp, begintmp;
    endtmp = end;
    begintmp = begin;
    if (begin < 0) { begintmp = 0; }
    if (end > len) { endtmp = len; }
    int i;
    for (i = begintmp; i <= endtmp; i++) {
        Gate *index = tmp;
        index = index + i;
        uint16_t tmpattr = index->attr & 0xFFFF;
        KernelPrint("%d.\t0x%08X  0x%04X-0x%08X\t %01X  %01X  %01X   %01X   %d\n", i, (uint32_t)index, index->selector, ((uint32_t)(index->offset2) << 16) | index->offset1, (tmpattr >> 15) & 0x1, (tmpattr >> 13) & 0x3, (tmpattr >> 12) & 0x1, (tmpattr >> 8) & 0xF, (tmpattr) & 0b00011111);
    }
}