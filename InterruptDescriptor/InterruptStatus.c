#include "Interrupt/InterruptStatus.h"
#define INTERRUPT_EFLAGS 0x00000200
InterruptStatus InterruptGetStatus() {
    unsigned int eflags = get_eflags();
    return (INTERRUPT_EFLAGS & eflags) ? INTERRUPT_ON : INTERRUPT_OFF;
}
InterruptStatus InterruptSetStatus(InterruptStatus status) {
    return status & INTERRUPT_ON ? InterruptEnable() : InterruptDisable();
}
InterruptStatus InterruptEnable() {
    InterruptStatus OldStatus;
    if (InterruptGetStatus() == INTERRUPT_ON) {
        OldStatus = INTERRUPT_ON;
        return OldStatus;
    }
    else {
        OldStatus = INTERRUPT_OFF;
        sti();
        return OldStatus;
    }
}
InterruptStatus InterruptDisable() {
    InterruptStatus OldStatus;
    if (InterruptGetStatus() == INTERRUPT_ON) {
        OldStatus = INTERRUPT_ON;
        cli();
        return OldStatus;
    }
    else {
        OldStatus = INTERRUPT_OFF;
        return OldStatus;
    }
}