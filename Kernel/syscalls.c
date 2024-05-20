#include <stdint.h>
#include <video.h>

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} Registers;

void sysCallHandler(Registers * regs) {
    switch(regs->rax){
        case 0: ;
        case 1: sysWrite(regs->rbx,regs->rcx, regs->rdx);;
        case 2: ;
    }
}

void sysWrite(uint64_t x, uint64_t y, char * string){ // @TODO: le paso la longitud del string?
    drawString(x,y,string);
}

void sysRead(){

}

//ACA HAY QUE IMPLEMENTAR TODAS LAS INT 80h

// write --> escribe directo en la pantalla?

// read --> lee del buffer de teclado

// registros del procesador

// emitir un sonido --> beep

// alguna que sirva como timer --> nano sleep? (para el jueguito de la serpiente)

// hora en general

