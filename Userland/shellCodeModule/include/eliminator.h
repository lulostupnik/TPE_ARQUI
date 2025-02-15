#ifndef ELIMINATOR_H
#define ELIMINATOR_H

#include <libc.h>


#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 16
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define PIXEL 8

#define MAP_WIDTH 128
#define MAP_HEIGHT 96


#define BLACK (Color){0, 0, 0}
#define RED (Color){255, 0, 0}
#define GREEN (Color){0, 255, 0}
#define BLUE (Color){0, 0, 255}
#define WHITE (Color){255, 255, 255}

#define PLAYER_1_INIT_X 64
#define PLAYER_1_INIT_Y 94

void eliminator();


enum direction {UP, DOWN, LEFT, RIGHT};

typedef enum direction direction;

typedef struct position{
    int x;
    int y;
} position;


typedef struct player{
    direction dir;
    position pos;
    Color color;
} player;

#endif // ELIMINATOR_H