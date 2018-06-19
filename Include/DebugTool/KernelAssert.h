#pragma once
#ifndef KERNEL_ASSERT_H
#define KERNEL_ASSERT_H
#include "../Kernel/CarbonDefine.h"
#include "../Kernel/CarbonKernelPrintUtil.h"
#ifndef NDEBUG
#define assert(expr) (void)((expr) || ((Assert(#expr,__FILE__,__LINE__),0)))
#define runtime_assert(expr, msg) ({ if (!(expr)) KernelPrint("Assertion failed: %s\n", msg); })
#else
#define assert(expr) ((void)0)
#define runtime_assert(expr, msg) ((void)0)
#endif // NDEBUG
#define static_assert(x) (switch (x) { case 0: case (x): ; })
void Assert(void *exp, void *file, uint32_t line);
#endif // KERNEL_ASSERT_H