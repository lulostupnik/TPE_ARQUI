#include <keyboard.h>
#include <stdint.h>

extern uint8_t getKey();

#include <video.h>

/*
 * Buffer --> es "circular". Si se llena, pisa lo que primero se puso.
 */
static uint8_t buffer[BUFFER_SIZE];
static uint64_t buffer_index = 0;
static uint64_t buffer_dim = 0;


/*
 * @TODO:
 * implementar teclas especiales como shift, control, caps lock
 * por ahora en el buffer solo se guardan los PRESSED
 */
static uint8_t shiftPressed = 0;

void keyboardHandler(){
    uint8_t key = getKey();
//    if(key&&0b01111111 != 'a'){
//        return;
//    }

    if(key > 0x79){
          return;
    }              // solo me interesa el pressed


    buffer[buffer_index % BUFFER_SIZE] =   getKey();
    buffer_index = (buffer_index+1) %BUFFER_SIZE;
    if(buffer_dim < BUFFER_SIZE){
        buffer_dim++;
    }
    drawRectangle(buffer[buffer_index-1],buffer[buffer_index-1],buffer[buffer_index-1],buffer_index*10,buffer_index*10, buffer[buffer_index-1], buffer[buffer_index-1]);
}


//static uint8_t specialKeys[] = {'shift', 'caps'};
//[aP, aR, shiftP, aP, shiftR, aR]
// if buff[] = shiftP
//while(buff[] != shiftReleased)
//      command = ;;....

