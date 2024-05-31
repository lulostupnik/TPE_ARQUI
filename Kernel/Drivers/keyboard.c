#include <keyboard.h>
#include <stdint.h>

extern uint8_t getKey();


/*
 * Buffer --> es "circular". Si se llena, pisa lo que primero se puso.
 */

static uint16_t buffer[BUFFER_SIZE];
//static uint64_t buffer_index = 0;
static uint64_t buffer_dim = 0;
static uint64_t buffer_current = 0;
static uint8_t reg_shot_flag = 0;


extern uint16_t pressedKeyShiftMap[][2];


/*
 * @TODO:
 * implementar teclas especiales como shift, control, caps lock
 * por ahora en el buffer solo se guardan los PRESSED
 */

#define CANT_FUNCTION_KEYS 12
static function_key functionKeyFunArray[CANT_FUNCTION_KEYS];

void setFKeyFunction(uint64_t key_number, function_key f){
    if(key_number == 0 || key_number > CANT_FUNCTION_KEYS ){
        return;
    }
    key_number--;
    functionKeyFunArray[key_number] = f;
}
static void functionKeyHandler(uint64_t code){
    int64_t i = -1;
    switch (code) {
        case F1: i=0; break;
        case F2: i =1; break;
        case F3: i=2; break;
        case F4: i =3; break;
        case F5: i=4; break;
        case F6: i =5; break;
        case F7: i=6; break;
        case F8: i =7; break;
        case F9: i=8; break;
        case F10: i =9; break;
        case F11: i=10; break;
        case F12: i =11; break;
    }
    function_key f = 0;
    if(i != -1){
        f =  functionKeyFunArray[i];
    }
    if(f != 0){
        f();
    }
}


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

static void updateBufferIndex(uint64_t index){
    if(index < BUFFER_SIZE){
        index++;
        return;
    }
    index = 0;
}


 uint64_t bufferHasNext(){
    return ( buffer_dim > 0 ) && ( buffer_current < buffer_dim );
}

uint64_t getCurrent(){
    if(bufferHasNext()) {
        return buffer[buffer_current++];
    }
    return 0;
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
    reg_shot_flag = 0;
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
    }

    if(!key_is_pressed){
        return;
    }
    
    if(code == F1 ){
        reg_shot_flag = 1;
        return;
    }
    // functionKeyHandler(code);


    buffer[buffer_dim] = code;
    if(buffer_dim < BUFFER_SIZE){
        buffer_dim++;
    }else{
        buffer_dim = 1;
    }
}



uint8_t should_take_reg_shot() {
    return reg_shot_flag;
}
