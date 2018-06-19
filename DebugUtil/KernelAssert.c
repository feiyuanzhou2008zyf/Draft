#include "DebugTool/KernelAssert.h"
void Assert(void *exp, void *file, uint32_t line) {
    KernelPrint("Assertion failed: %s, File: %s,Line: %d\n", exp, file, line);
    while (1);
}