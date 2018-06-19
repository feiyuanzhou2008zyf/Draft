#include "Elf/ELFUtil.h"
#include "Bootloader/MultibootElfSection.h"
Elf ElfFromMultiboot() {
    int i;
    Elf elf;
    MultibootTagElfSymbols *tagPtr = FindMultibootTag(TAG_ELF_SECTIONS);
    ElfSectionHeader *sh = tagPtr->sectionHeader;
    uint32_t shstrtab = sh[tagPtr->shndx].addr;
    for (i = 0; i < tagPtr->num; i++) {
        const char *name = (const char *)(shstrtab + sh[i].name);
        if (strcmp(name, ".strtab") == 0) {
            elf.strtab = (const char *)sh[i].addr;
            elf.strtabsz = sh[i].size;
        }
        if (strcmp(name, ".symtab") == 0) {
            elf.symtab = (ElfSymbol *)sh[i].addr;
            elf.symtabsz = sh[i].size;
        }
    }
    return elf;
}
const char *ElfLookupSymbol(uint32_t addr, Elf *elf) {
    int i;
    for (i = 0; i < (elf->symtabsz / sizeof(ElfSymbol)); i++) {
        if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2) { continue; }
        if ((addr >= elf->symtab[i].value) && (addr < (elf->symtab[i].value + elf->symtab[i].size))) {
            return (const char *)((uint32_t)elf->strtab + elf->symtab[i].name);
        }
    }
    return NULL;
}