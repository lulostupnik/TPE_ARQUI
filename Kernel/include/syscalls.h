#ifndef _SYSCALLS_H
#define _SYSCALLS_H
#include <stdint.h>
#include <stddef.h> // lo necesitamos para size_t

// @TODO: Estamos poniendo los mismos prototipos que linux

//@COMMENT: Puse los prototipos de las funciones que hice yo, no me mates Mati -Fede


uint64_t sysRead(uint64_t * toBuffer, uint64_t toBufferDim);
uint64_t sysWrite(uint64_t x, uint64_t y, uint8_t * string);

#endif