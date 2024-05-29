#ifndef SYSCALLFUNCTIONS_H
#define SYSCALLFUNCTIONS_H
#include <stdint.h>

uint64_t sys_ead(uint64_t * toBuffer, uint64_t toBufferDim);
uint64_t sys_write(uint64_t x, uint64_t y, uint8_t * string);

#endif 