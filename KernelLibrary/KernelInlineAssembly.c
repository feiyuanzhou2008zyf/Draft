#include "Kernel/KernelInlineAssembly.h"
uint8_t inb(uint32_t port) {
    uint8_t tmp;
    asm volatile ("movl %0,%%edx"::"m"(port));
    asm volatile ("movl $0,%eax");
    asm volatile ("inb %dx,%al");
    asm volatile ("movb %%al,%0":"=m"(tmp));
    return tmp;
}
uint16_t inw(uint32_t port) {
    uint16_t tmp;
    asm volatile ("movl %0,%%edx"::"m"(port));
    asm volatile ("movl $0,%eax");
    asm volatile ("inw %dx,%ax");
    asm volatile ("movw %%ax,%0":"=m"(tmp));
    return tmp;
}
uint32_t intdw(uint32_t port) {
    uint32_t tmp;
    asm volatile ("movl %0,%%edx"::"m"(port));
    asm volatile ("movl $0,%eax");
    asm volatile ("inl %dx,%eax");
    asm volatile ("movl %%eax,%0":"=m"(tmp));
    return tmp;
}
void outb(uint32_t port, uint8_t data) {
    asm volatile ("movl %0,%%edx"::"m"(port));
    asm volatile ("movl $0,%eax");
    asm volatile ("movb %0,%%al":"=m"(data));
    asm volatile ("outb %al,%dx");
}
void outw(uint32_t port, uint16_t data) {
    asm volatile ("movl %0,%%edx"::"m"(port));
    asm volatile ("movl $0,%eax");
    asm volatile ("movw %0,%%ax":"=m"(data));
    asm volatile ("outw %ax,%dx");
}
void outdw(uint32_t port, uint32_t data) {
    asm volatile ("movl %0,%%edx"::"m"(port));
    asm volatile ("movl $0,%eax");
    asm volatile ("movl %0,%%eax":"=m"(data));
    asm volatile ("outl %eax,%dx");
}
void cli() { asm volatile ("cli"); }
void sti() { asm volatile ("sti"); }
void nop() { asm volatile ("nop"); }
void hlt() { asm volatile ("hlt"); }
void sti_hlt() {
    asm volatile ("sti");
    asm volatile ("hlt");
}
uint32_t get_eflags() {
    uint32_t tmp;
    asm volatile ("pushfl");
    asm volatile ("popl %eax");
    asm volatile ("movl %%eax,%0":"=m"(tmp));
    return tmp;
}
void set_eflags(uint32_t eflages) {
    asm volatile ("movl %0,%%eax":"=m"(eflages));
    asm volatile ("pushl %eax");
    asm volatile ("popfl");
}
void set_ss(uint16_t data) {
    asm volatile ("movw %0,%%ax"::"m"(data));
    asm volatile ("movw %ax,%ss");
}
void set_ds(uint16_t data) {
    asm volatile ("movw %0,%%ax"::"m"(data));
    asm volatile ("movw %ax,%ds");
}
void set_es(uint16_t data) {
    asm volatile ("movw %0,%%ax"::"m"(data));
    asm volatile ("movw %ax,%es");
}
void set_fs(uint16_t data) {
    asm volatile ("movw %0,%%ax"::"m"(data));
    asm volatile ("movw %ax,%fs");
}
void set_gs(uint16_t data) {
    asm volatile ("movw %0,%%ax"::"m"(data));
    asm volatile ("movw %ax,%gs");
}
uint16_t get_cs() {
    uint16_t tmp;
    asm volatile ("movw %cs,%ax");
    asm volatile ("movw %%ax,%0":"=m"(tmp));
    return tmp;
}
uint16_t get_ds() {
    uint16_t tmp;
    asm volatile ("movw %ds,%ax");
    asm volatile ("movw %%ax,%0":"=m"(tmp));
    return tmp;
}
uint16_t get_ss() {
    uint16_t tmp;
    asm volatile ("movw %ss,%ax");
    asm volatile ("movw %%ax,%0":"=m"(tmp));
    return tmp;
}
uint16_t get_es() {
    uint16_t tmp;
    asm volatile ("movw %es,%ax");
    asm volatile ("movw %%ax,%0":"=m"(tmp));
    return tmp;
}
uint16_t get_fs() {
    uint16_t tmp;
    asm volatile ("movw %fs,%ax");
    asm volatile ("movw %%ax,%0":"=m"(tmp));
    return tmp;
}
uint16_t get_gs() {
    uint16_t tmp;
    asm volatile ("movw %gs,%ax");
    asm volatile ("movw %%ax,%0":"=m"(tmp));
    return tmp;
}