#pragma once
#ifndef ELF_UTIL_H
#define ELF_UTIL_H
#include "../Kernel/CarbonDefine.h"
#include "../RuntimeLibrary/StringLibrary.h"
#define ELF32_ST_TYPE(i) ((i) & 0xf)
typedef struct __elf_section_header__ {
    uint32_t name;
    uint32_t types;
    uint32_t flags;
    uint32_t addr;
    uint32_t offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t addr_align;
    uint32_t entry_size;
} ElfSectionHeader;
typedef struct __elf_symbol__ {
    uint32_t name;
    uint32_t value;
    uint32_t size;
    uint8_t info;
    uint8_t other;
    uint16_t shndx;
} ElfSymbol;
typedef struct __elf__ {
    ElfSymbol *symtab;
    uint32_t symtabsz;
    const char *strtab;
    uint32_t strtabsz;
} Elf;
Elf ElfFromMultiboot();
const char *ElfLookupSymbol(uint32_t address, Elf *elf);
#endif // ELF_UTIL_H