#include <libc.h>

void eliminator(){
    // puts("Welcome to Eliminator!\n");
    enter_video_mode();
    draw_pixel(0, 0, (Color) {255, 0, 0});
    draw_pixel(5, 5, (Color) {0, 255, 0});
    draw_pixel(20, 20, (Color) {0, 0, 255});
    char c;
    while(( c = getChar() ) != 'q' ){}
    enter_text_mode();
    return;
}

