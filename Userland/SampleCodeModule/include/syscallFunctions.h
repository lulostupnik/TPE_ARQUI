#ifndef SYSCALLFUNCTIONS_H
#define SYSCALLFUNCTIONS_H
#include <stdint.h>


int64_t sys_read(uint64_t fd, char * buffer, uint64_t amount);
int64_t sys_write(uint64_t fd, const char * buffer, uint64_t amount);


#endif 