#pragma once
#ifndef MULTI_BOOT_INFO_H
#define MULTI_BOOT_INFO_H
#include "../Kernel/CarbonDefine.h"
typedef struct __multiboot_base_tag__ {
    uint32_t type;
    uint32_t size;
} MultibootBaseTag;
typedef struct __multiboot_info__ {
    uint32_t size;
    uint32_t reserved;
    MultibootBaseTag tags[0];
} MultibootInfo;
#endif // MULTI_BOOT_INFO_H