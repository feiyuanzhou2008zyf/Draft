#pragma once
#ifndef INTERRUPT_STATUS_H
#define INTERRUPT_STATUS_H
#include "../Kernel/CarbonDefine.h"
#include "../Kernel/KernelInlineAssembly.h"
typedef enum __interrupt_status__ {
    INTERRUPT_OFF,
    INTERRUPT_ON
} InterruptStatus;
InterruptStatus InterruptGetStatus();
InterruptStatus InterruptSetStatus(InterruptStatus status);
InterruptStatus InterruptEnable();
InterruptStatus InterruptDisable();
#endif // INTERRUPT_STATUS_H