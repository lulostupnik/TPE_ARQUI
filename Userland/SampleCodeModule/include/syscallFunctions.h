#ifndef SYSCALLFUNCTIONS_H
#define SYSCALLFUNCTIONS_H
#include <stdint.h>

void syscallRead(uint8_t * toBuffer, uint64_t toBufferDim, uint64_t * count);
void syscallWrite(uint64_t x, uint64_t y, char * string);

#endif 