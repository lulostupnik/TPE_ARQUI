#include <libc.h>
#include <stdint.h>
#include <syscallFunctions.h>

//Special characters son mayores a 256 en el kernel.
//devuelve solo los chars/special APRETADOS !
uint64_t getFirstKeyStroke(){

    uint64_t c;

    while( sysRead(&c, 1) == 0 );


    sysWrite(0,0,"hola");

    return c;
}






