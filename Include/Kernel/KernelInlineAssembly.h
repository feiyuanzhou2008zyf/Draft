#pragma once
#ifndef KERNEL_INLINE_ASSEMBLY_H
#define KERNEL_INLINE_ASSEMBLY_H
#include "CarbonDefine.h"
#define Bit(n, nb) (((n) & (1 << (nb))) != 0)
#define SetBit(n, nb) ((n) |= (1 << (nb)))
#define ClearBit(n, nb) ((n) &= ~(1 << (nb)))
uint8_t inb(uint32_t port);
uint16_t inw(uint32_t port);
uint32_t intdw(uint32_t port);
void outb(uint32_t port, uint8_t data);
void outw(uint32_t port, uint16_t data);
void outdw(uint32_t port, uint32_t data);
void cli();
void sti();
void hlt();
void sti_hlt();
uint32_t get_eflags();
void set_eflags(uint32_t eflages);
void set_ss(uint16_t data);
void set_ds(uint16_t data);
void set_es(uint16_t data);
void set_fs(uint16_t data);
void set_gs(uint16_t data);
uint16_t get_cs();
uint16_t get_ds();
uint16_t get_ss();
uint16_t get_es();
uint16_t get_fs();
uint16_t get_gs();
#endif // KERNEL_INLINE_ASSEMBLY_H