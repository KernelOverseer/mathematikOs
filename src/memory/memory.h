#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>

void *memset(void *mem, uint8_t c,  uint32_t size);
void *bzero(void *mem, uint32_t size);

#endif