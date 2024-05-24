#include <stdint.h>
#include <video.h>

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} Registers;

/*
typedef struct {
    uint64_t rsi, rdi, rdx, rcx, rbx, rax;
} Registers;
*/

void sysCallHandler(Registers * regs) {
    switch(regs->rax){
        case 0: sysRead(regs->rbx, regs->rcx, regs->rdx); break;
        case 1: sysWrite(regs->rbx, regs->rcx, regs->rdx); break;
    }
}

void sysWrite(uint64_t x, uint64_t y, uint8_t * string){ // @TODO: le paso la longitud del string?
    drawString(x,y,string);
}

void sysRead(uint64_t * toBuffer, uint64_t toBufferDim, uint64_t * count){
    readKeyboardBuffer(toBuffer,toBufferDim,count);
}

//ACA HAY QUE IMPLEMENTAR TODAS LAS INT 80h

// write --> escribe directo en la pantalla?

// read --> lee del buffer de teclado

// registros del procesador

// emitir un sonido --> beep

// alguna que sirva como timer --> nano sleep? (para el jueguito de la serpiente)

// hora en general

/*

void sys_write(Registers * regs);

static void (*syscall_handlers[2])(Registers * regs) = {
    sys_write,
    sys_read
};

void sys_write(Registers * regs) {

    drawString(regs->rbx, regs->rcx,(char *) regs->rdx, regs->r);
}

 */
