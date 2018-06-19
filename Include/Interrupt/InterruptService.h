#pragma once
#ifndef INTERRUPT_SERVICE_H
#define INTERRUPT_SERVICE_H
#include "../Kernel/CarbonDefine.h"
#include "InterruptController.h"
#include "../GlobalDescriptor/DescriptorUtil.h"
#include "../Kernel/CarbonKernelPrintUtil.h"
#include "../Kernel/KernelInlineAssembly.h"
#include "../RuntimeLibrary/StringLibrary.h"
#define INTERRUPT_GATE_COUNT 255
typedef void(*intr_hander)();
typedef GDTDescriptor IDTDescriptor;
typedef enum __gate_type__ {
    INT = 0b01110,
    FAULT = 0b01110,
    TRAP = 0b01111
} GateType;
typedef struct __idt_item__ {
    uint16_t offset_0_15;
    uint16_t segment_selector;
    uint8_t zero;
    GateType type: 5;
    SystemRPL rpl: 2;
    Bool present: 1;
    uint16_t offset_16_31;
} IDTItem;
IDTItem MakeIDTItem(intr_hander callback, GateType gatetype);
void SetIDTItem(int index, IDTItem item);
Bool InitIDT();
void ShowIDTTable(int begin, int end);
void divide_error();
void single_step_exception();
void nmi();
void breakpoint_exception();
void overflow();
void bounds_check();
void inval_opcode();
void copr_not_available();
void double_fault();
void copr_seg_overrun();
void inval_tss();
void segment_not_present();
void stack_exception();
void general_protection();
void page_fault();
void copr_error();
void hwint00();
void hwint01();
void hwint02();
void hwint03();
void hwint04();
void hwint05();
void hwint06();
void hwint07();
void hwint08();
void hwint09();
void hwint10();
void hwint11();
void hwint12();
void hwint13();
void hwint14();
void hwint15();
void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags);
void spurious_irq(int irq);
void keyboard_handler(int irq);
void interrupt_handler();
#endif // INTERRUPT_SERVICE_H