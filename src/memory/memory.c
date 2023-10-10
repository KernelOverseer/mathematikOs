#include "memory/memory.h"

void *memset(void *mem, uint8_t c,  uint32_t size)
{
    uint32_t i = 0;
    uint8_t *memory = (uint8_t *)mem;
    
    while (i < size)
    {
        memory[i] = c;
        i++;
    }
    return mem;
}

void *bzero(void *mem, uint32_t size)
{
    return memset(mem, 0, size);
}