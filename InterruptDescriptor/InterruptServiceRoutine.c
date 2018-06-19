#include "Interrupt/InterruptService.h"
#include "DebugTool/DebugUtil.h"
#define exception1(x) ({ asm volatile ("movl %ebp,%esp"); \
	asm volatile ("popl %ebp"); \
	asm volatile (x); \
	asm volatile ("call exception_handler"); \
	asm volatile ("addl $8,%esp"); \
	asm volatile ("hlt"); \
})
#define exception2(x,y) ({ asm volatile ("movl %ebp,%esp"); \
    asm volatile ("popl %ebp"); \
    asm volatile (x); \
    asm volatile (y); \
    asm volatile ("call exception_handler"); \
    asm volatile ("addl $8,%esp"); \
    asm volatile ("hlt"); \
})
#define hardware_interrupt(x) ({ asm volatile ("movl %ebp,%esp"); \
    asm volatile ("popl %ebp"); \
    asm volatile (x); \
    asm volatile ("call spurious_irq"); \
    asm volatile ("addl $4,%esp"); \
    asm volatile ("iret"); \
})
void spurious_irq(int irq) { KernelPrint("spurious_irq: %X\n", irq); }
void interrupt_handler() {
    asm volatile ("movl %ebp,%esp");
    asm volatile ("popl %ebp");
    keyboard_handler(1);
    outb(0x20, 0x61);
    asm volatile ("movl %ebp,%esp");
    asm volatile ("iret");
}
void keyboard_handler(int irq) {
    uint8_t scan_code = inb(0x60);
    KernelPrint("0x%X ", scan_code);
}
void divide_error() { exception2("pushl $0xFFFFFFFF", "pushl $0"); }
void single_step_exception() { exception2("pushl $0xFFFFFFFF", "pushl $1"); }
void nmi() { exception2("pushl $0xFFFFFFFF", "pushl $2"); }
void breakpoint_exception() { exception2("pushl $0xFFFFFFFF", "pushl $3"); }
void overflow() { exception2("pushl $0xFFFFFFFF", "pushl $4"); }
void bounds_check() { exception2("pushl $0xFFFFFFFF", "pushl $5"); }
void inval_opcode() { exception2("pushl $0xFFFFFFFF", "pushl $6"); }
void copr_not_available() { exception2("pushl $0xFFFFFFFF", "pushl $7"); }
void double_fault() { exception1("pushl $8"); }
void copr_seg_overrun() { exception2("pushl $0xFFFFFFFF", "pushl $9"); }
void inval_tss() { exception1("pushl $10"); }
void segment_not_present() { exception1("pushl $11"); }
void stack_exception() { exception1("pushl $12"); }
void general_protection() { exception1("pushl $13"); }
void page_fault() { exception1("pushl $14"); }
void copr_error() { exception2("pushl $0xFFFFFFFF", "pushl $16"); }
void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags) {
    char* err_msg[] = {
            "#DE Divide Error",
            "#DB RESERVED",
            "#NMI NMI Interrupt",
            "#BP Breakpoint",
            "#OF Overflow",
            "#BR BOUND Range Exceeded",
            "#UD Invalid Opcode (Undefined Opcode)",
            "#NM Device Not Available (No Math Coprocessor)",
            "#DF Double Fault",
            "#CSO Coprocessor Segment Overrun (reserved)",
            "#TS Invalid TSS",
            "#NP Segment Not Present",
            "#SS Stack-Segment Fault",
            "#GP General Protection",
            "#PF Page Fault",
            "#Reserved (Intel reserved. Do not use.)",
            "#MF x87 FPU Floating-Point Error (Math Fault)",
            "#AC Alignment Check",
            "#MC Machine Check",
            "#XF SIMD Floating-Point Exception"
    };
    KernelPrint("Exception! --> %s\nEFLAGS: 0x%X,CS: 0x%X,EIP: 0x%X\n", err_msg[vec_no], eflags, cs, eip);
    if (err_code != 0xFFFFFFFF) { KernelPrint("Error code: 0x%X\n", err_code); }
    PrintStackTrace();
    while (1);
}
void hwint00() {
    asm volatile ("movl %ebp,%esp");
    asm volatile ("popl %ebp");
    asm volatile ("movb $0x20,%al");
    asm volatile ("outb %al,$0xa0");
    asm volatile ("outb %al,$0x20");
    asm volatile ("iret");
}
void hwint01() { hardware_interrupt("pushl $1"); }
void hwint02() { hardware_interrupt("pushl $2"); }
void hwint03() { hardware_interrupt("pushl $3"); }
void hwint04() { hardware_interrupt("pushl $4"); }
void hwint05() { hardware_interrupt("pushl $5"); }
void hwint06() { hardware_interrupt("pushl $6"); }
void hwint07() { hardware_interrupt("pushl $7"); }
void hwint08() { hardware_interrupt("pushl $8"); }
void hwint09() { hardware_interrupt("pushl $9"); }
void hwint10() { hardware_interrupt("pushl $10"); }
void hwint11() { hardware_interrupt("pushl $11"); }
void hwint12() { hardware_interrupt("pushl $12"); }
void hwint13() { hardware_interrupt("pushl $13"); }
void hwint14() { hardware_interrupt("pushl $14"); }
void hwint15() { hardware_interrupt("pushl $15"); }