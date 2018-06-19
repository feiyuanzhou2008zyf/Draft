#pragma once
#ifndef INTERRUPT_CONTROLLER_H
#define INTERRUPT_CONTROLLER_H
#include "../Kernel/KernelInlineAssembly.h"
#define PIC_M_CTRL 0x20
#define PIC_M_DATA 0x21
#define PIC_S_CTRL 0xa0
#define PIC_S_DATA 0xa1
void InitPIC();
#endif // INTERRUPT_CONTROLLER_H