#include <libc.h>
#include <stdint.h>
#include <syscallFunctions.h>

//Special characters son mayores a 256 en el kernel.
//devuelve solo los chars/special APRETADOS !
uint64_t getFirstKeyStroke(){
    uint64_t c;
    uint64_t count = 0;
    sysRead(&c,1,&count);
    return c;
}


