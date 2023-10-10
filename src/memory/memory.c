#include "memory/memory.h"

void *memset(void *dest, uint8_t c, uint32_t size)
{
    uint8_t *mem = dest;
    while (size--)
        *mem++ = c;
    return dest;
}

void *bzero(void *dest, uint32_t size)
{
    return memset(dest, 0, size);
}