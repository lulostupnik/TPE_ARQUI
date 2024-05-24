#ifndef SYSCALLFUNCTIONS_H
#define SYSCALLFUNCTIONS_H
#include <stdint.h>

void sysRead(uint64_t * toBuffer, uint64_t toBufferDim, uint64_t * count);
void sysWrite(uint64_t x, uint64_t y, uint8_t * string);

#endif 