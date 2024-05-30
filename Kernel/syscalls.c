#include <stdint.h>
#include <video.h>
#include <keyboard.h>
#include <syscalls.h>

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} Registers;

/*
typedef struct {
    uint64_t rsi, rdi, rdx, rcx, rbx, rax;
} Registers;
*/

// Orden en el cual mandar los registros:

/*
 * @Todo agregar sys_write
 */
int64_t sysCallHandler(Registers * regs) {
    // printFont('X');
    switch(regs->rax){
        case 0: return sys_read(regs->rdi, (char *) regs->rsi, regs->rdx); break;
        case 1: return sys_write(regs->rdi, (char *) regs->rsi, regs->rdx); break;
        // case 2: return sys_get_register_snapshot((RegisterSet *) regs->rdi); break;
        // case 3: return sys_beep(regs->rdi, regs->rsi); break;
        case 4: return sys_set_font_size(regs->rdi); break;
        case 5: return sys_clear_screen(); break;
        case 6: return sys_put_pixel(regs->rdi, regs->rsi, (Color *) regs->rdx); break; //@todo: ¿está bien orden de registros?
        case 7: return sys_put_rectangle(regs->rdi, regs->rsi, regs->rdx, regs->rcx, (Color *) regs->r8); break;
        case 9: return sys_set_mode(regs->rdi); break;
        default: return NOT_VALID_SYS_ID;  //     printFont('X');

    }
}

//uint64_t sysWrite(uint64_t x, uint64_t y, uint8_t * string){ // @TODO: le paso la longitud del string?
//    drawLetter(x,y,string[0],1);
//    return 0; // @TODO: cambiar!!!!
//}

int64_t sys_read(uint64_t fd, char * buffer, uint64_t amount){
    uint64_t i = 0;
    while(i < amount && bufferHasNext()){
        buffer[i] = (char) getCurrent(); // @TODO getCurrent me da un uint64_t, pero lo que quiero es un char --> ¿el casteo está bien?
        i++;
    }
    return i;
   // readKeyboardBuffer(toBuffer,toBufferDim,count);
}


//Modo texto:
int64_t sys_write(uint64_t fd, const char * buffer, uint64_t amount){
    return vdriver_text_write(fd, buffer, amount);
}

int64_t sys_set_font_size(uint64_t size){
    return vdriver_text_set_font_size(size);
}  // este ya hace el resize si entra AL menos 1 caracter !

int64_t sys_put_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, Color * color){
    return vdriver_video_draw_rectangle(x, y, width, height, *color);
}

int64_t sys_draw_letter(uint64_t x, uint64_t y, char letter, Color color){
    return 1;
}

int64_t sys_put_pixel(uint64_t x, uint64_t y, Color * color){
    return vdriver_video_draw_pixel(x, y, *color);
}

//Ambos modos:
int64_t sys_get_screen_information(ScreenInformation * screen_information){
    return 1;
}

int64_t sys_set_mode(uint64_t mode){
    return vdriver_set_mode(mode, (Color) {0,0,0});
}

int64_t sys_get_register_snapshot(RegisterSet * registers){
    return -1;
}


int64_t sys_clear_screen(){
    return vdriver_clear_screen((Color) {0,0,0});
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
