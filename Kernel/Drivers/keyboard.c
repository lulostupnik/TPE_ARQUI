#include <keyboard.h>
#include <stdint.h>

extern uint8_t getKey();


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

static int specialKeyPressed(uint16_t code){
    if(!isSpecialKey(code)){
        return -1;
    }
    return specialKeyPressedMap[specialKeyPressedMapIdx(code)];
}


static int capsLockPressed(){
    return specialKeyPressed(CAPS_LOCK);
}
static int shiftPressed(){
    return (specialKeyPressed(LEFT_SHIFT) || specialKeyPressed(RIGHT_SHIFT)) ? 1:0;
    /*
    if(specialKeyPressed(LEFT_SHIFT || specialKeyPressed(RIGHT_SHIFT))){
        return 1;
    }
    return 0;*/
}
static int shiftCapsLockPressed(){
    return (shiftPressed()^capsLockPressed()); //xor
}

static uint8_t releasedKeyToPressedMask(uint8_t key){
    return key&0x7F;
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
 * ver que ande todo bien. testear. pensar mas casos de special keys
 * Por ahora solo GUARDO LOS PRESSED
 */


/*
 *@TODO implementar NUM_LOCK
 * se puede implementar algo que me devuelva si se tocaron las teclas de control.....
*  un buffer con pressed y released o una funcion que me diga si se presiono una tecla especial (uso el mapa). Por ahora musa
 */


void keyboardHandler(){
    uint8_t key = getKey();


    uint8_t key_is_pressed = isPressed(key) ? 1:0;

    if( !key_is_pressed){
        key = releasedKeyToPressedMask(key); //la tabla es para PRESSED !
    }

    uint16_t code = pressedKeyShiftMap[key][shiftCapsLockPressed()];

    if(isSpecialKey(code)){
        if(code != CAPS_LOCK && code != NUM_LOCK && code != SCROLL_LOCK){
            specialKeyPressedMap[specialKeyPressedMapIdx(code)] = key_is_pressed;
        }else if(key_is_pressed) {
            specialKeyPressedMap[specialKeyPressedMapIdx(code)] = 1 - specialKeyPressedMap[specialKeyPressedMapIdx(code)];
        }
       // return; por ahora guardamos las special keys en el buffer
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
}
