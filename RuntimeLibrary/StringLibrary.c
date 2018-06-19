#include "RuntimeLibrary/StringLibrary.h"
static void *memcpy_prototype(void *dest, const void *src, size_t n);
void *memcpy(void *dest, const void *src, size_t count) {
    if (dest > src && dest - src < count) {
        KernelPrint("Avoiding potentially unsafe overlapping memcpy()!\n");
        return memmove(dest, src, count);
    }
    return memcpy_prototype(dest, src, count);
}

void *memset(void *src, int chunk, size_t count) {
    int i;
    char *ss = src;
    for (i = 0; i < count; i++)
        ss[i] = chunk;
    return src;
}
void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *d = dest;
    const uint8_t *s = src;
    if (d <= s || d - s >= n)
        return memcpy_prototype(dest, src, n);
    while (n-- > 0)
        d[n] = s[n];
    return dest;
}
char *strcpy(char *dest, const char *src) {
    char *addr = dest;
    assert((dest != NULL) && (src != NULL));
    while (*src) {
        *dest = *src;
        dest++;src++;
    }
    *dest = '\0';
    return addr;
}
char *strcat(char *dest, const char *src) {
    assert(dest != NULL && src != NULL);
    char *ptr = dest;
    while (*ptr++)
        --ptr;
    while ((*ptr++ = *src++) != 0);
    return dest;
}
int strcmp(const char *str1, const char *str2) {
    assert((str1 != NULL) && (str2 != NULL));
    while (*str1 && *str2 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
int strlen(const char *src) {
    if (src == NULL)
        return NULL;
    return ('\0' != *src) ? (1 + strlen(++src)) : 0;
}
static void *memcpy_prototype(void *dest, const void *src, size_t n) {
    int d0, d1, d2;
    asm volatile (
    "rep;movsl\n\t"
    "movl %4, %%ecx\n\t"
    "rep;movsb\n\t"
    : "=&c"(d0), "=&D"(d1), "=&S"(d2)
    : "0"(n >> 2), "g"(n & 3), "1"(dest), "2"(src)
    : "memory");
    return dest;
}