//
// Created by lulos on 24/5/2024.
//
#include <stdint.h>
#ifndef TPE_ARQUI_LIBC_H
#define TPE_ARQUI_LIBC_H

/*
 * @TODO En la documentacion del kernel deberia decir que las funciones del KeyDriver devuelven estos valores si no son caracteres ACII.
 */
typedef enum {
    LEFT_CONTROL = 256,         // NOTAR: El valor con el que empieza tiene que ser mas grande al ultimo de la tabla ASCII
    LEFT_SHIFT,
    RIGHT_SHIFT,
    KEYPAD_STAR_PRTSC,
    LEFT_ALT,
    CAPS_LOCK,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    NUM_LOCK,
    SCROLL_LOCK,
    HOME_KEYPAD,
    UP_ARROW_KEYPAD,
    PG_UP_KEYPAD,
    LEFT_ARROW_KEYPAD,
    RIGHT_ARROW_KEYPAD,
    PLUS_KEYPAD,
    END_KEYPAD,
    DOWN_ARROW_KEYPAD,
    PG_DN_KEYPAD,
    INS_KEYPAD,
    DEL_KEYPAD,
    SYS_REQ_AT,
    NONE1, // no hay tecla de scanCode 0x55
    NONE2, // no hay tecla de scan code 0x56
    F11,
    F12
} specialCodes;

uint64_t getFirstKeyStroke();

#endif //TPE_ARQUI_LIBC_H
