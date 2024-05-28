#include <stdint.h>
#include <video.h>
#include <syscalls.h>

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} Registers;

/*
typedef struct {
    uint64_t rsi, rdi, rdx, rcx, rbx, rax;
} Registers;
*/

/*
 * @Todo agregar sys_write
 */
uint64_t sysCallHandler(Registers * regs) {
    switch(regs->rax){
        case 0: return sysRead(regs->rdi, regs->rsi); break;
        case 1: return 1; break;
    }
}

//uint64_t sysWrite(uint64_t x, uint64_t y, uint8_t * string){ // @TODO: le paso la longitud del string?
//    drawLetter(x,y,string[0],1);
//    return 0; // @TODO: cambiar!!!!
//}

uint64_t sysRead(uint64_t * toBuffer, uint64_t toBufferDim){
    uint64_t i = 0;
    while(i < toBufferDim && bufferHasNext()){
        toBuffer[i] = getCurrent();
        i++;
    }

    return i;
   // readKeyboardBuffer(toBuffer,toBufferDim,count);

}


//Modo texto:
int64_t sys_write(uint64_t fd, const char * buffer, int64_t amount){
    return 1;
}
int64_t sys_set_font_size(uint64_t size){
    return 1;
}  // este ya hace el resize si entra AL menos 1 caracter !

//Modo video:
int64_t sys_draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, Color color){
    return 1;
}
int64_t sys_draw_letter(uint64_t x, uint64_t y, char letter, Color color){
    return 1;
}
int64_t sys_draw_pixel(uint64_t x, uint64_t y, Color color){
    return 1;
}

//Ambos modos:
int64_t sys_get_screen_information(ScreenInformation * screen_information){
    return 1;
}
int64_t sys_set_mode(uint64_t mode){
    return 1;
}



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
