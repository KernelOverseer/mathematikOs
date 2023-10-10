#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>

void *memset(void *dest, uint8_t c, uint32_t size);
void *bzero(void *dest, uint32_t size);

#endif