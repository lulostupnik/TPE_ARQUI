#ifndef _SYSCALLS_H
#define _SYSCALLS_H
#include <stdint.h>
#include <stddef.h> // lo necesitamos para size_t

// @TODO: Estamos poniendo los mismos prototipos que linux


ssize_t sys_read(unsigned int fd, char __user *buf, size_t count);

ssize_t sys_write(int fd, const void *buf, size_t count);


#endif