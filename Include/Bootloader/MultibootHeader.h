#pragma once
#ifndef MULTI_BOOT_HEADER_H
#define MULTI_BOOT_HEADER_H
#include "../Kernel/CarbonDefine.h"
typedef struct __multiboot_header_tag__ {
    uint16_t type;
    uint16_t flags;
    uint16_t size;
} MultibootHeaderTag;
typedef struct __multiboot_header__ {
    uint32_t magic;
    uint32_t architecture;
    uint32_t header_length;
    uint32_t checksum;
    MultibootHeaderTag tag;
} MultibootHeader;
#endif // MULTI_BOOT_HEADER_H