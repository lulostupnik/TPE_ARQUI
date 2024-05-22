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



extern uint16_t pressedKeyShiftMap[][2];

/*
 * @TODO:
 * implementar teclas especiales como shift, control, caps lock
 * por ahora en el buffer solo se guardan los PRESSED
 */



static uint8_t isReleased(uint8_t key){
    return (key & 0x80);
}
static uint8_t isPressed(uint8_t key){
    return !isReleased(key);
}

#define specialKeyPressedMapIdx(code) (code - FIRST_SPECIAL_KEY)
static uint16_t specialKeyPressedMap[SPECIAL_KEYS_CANT] = {0};

static int isSpecialKey(uint16_t code){
    return (code >= FIRST_SPECIAL_KEY) && (code <= LAST_SPECIAL_KEY);
}
static int capsLockPressed(){
    return specialKeyPressedMap[specialKeyPressedMapIdx(CAPS_LOCK)];

}
static int shiftPressed(){
    if(specialKeyPressedMap[specialKeyPressedMapIdx(RIGHT_SHIFT)] == 1 || specialKeyPressedMap[specialKeyPressedMapIdx(LEFT_SHIFT)] == 1){
        return 1;
    }
    return 0;
}
static int shiftCapsLockPressed(){
    return !(shiftPressed()&capsLockPressed()); //nand
}

static uint8_t releasedKeyToPressedMask(uint8_t key){
    return key&0xEF;
}

 void readKeyboardBuffer(uint8_t * toBuffer, uint64_t toBufferDim, uint64_t * count){
    int i=0;
    int charstobeRead=buffer_dim-buffer_index;
    while(i<charstobeRead && i<toBufferDim){
        toBuffer[i++]=buffer[(buffer_index++)% BUFFER_SIZE];
    }
    *count=i;
 }
/*
 * @TODO
 * ver que ande todo bien. testear.
 * borrar el draw en el keyboard handler
 * poner todo mass lindo es un kilombo
 */
void keyboardHandler(){
    uint8_t key = getKey();
   // key = LEFT_SHIFT;
   uint8_t key_is_pressed = isPressed(key);
   if(!key_is_pressed){
       key = releasedKeyToPressedMask(key); //la tabla es para PRESSED !
   }
   uint16_t code = pressedKeyShiftMap[key][shiftCapsLockPressed()];
   if(isSpecialKey(code)){
       specialKeyPressedMap[specialKeyPressedMapIdx(code)] = key_is_pressed;
       return;
   }

   if(!key_is_pressed){
        return;
   }
    //Solo pongo en el buffer codigos ascii que no son 'special keys'

    buffer[buffer_index % BUFFER_SIZE] = code;
    buffer_index = (buffer_index+1) %BUFFER_SIZE;
    if(buffer_dim < BUFFER_SIZE){
        buffer_dim++;
    }

    //TESTEO
    //putRectangle(255,255,255,0,0, buffer[buffer_index-1], buffer[buffer_index-1]);
    drawLetter(buffer_index*8, 0, (char)code);


}



//static uint8_t specialKeys[] = {'shift', 'caps'};
//[aP, aR, shiftP, aP, shiftR, aR]
// if buff[] = shiftP
//while(buff[] != shiftReleased)
//      command = ;;....

