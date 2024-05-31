#include <eliminator.h>


void eliminator(){
    enter_video_mode();
    draw_pixel(0, 0, (Color) {255, 0, 0});
    draw_pixel(5, 5, (Color) {0, 255, 0});
    draw_pixel(20, 20, (Color) {0, 0, 255});
    draw_rectangle(10, 10, 10, 10, (Color) {255, 0, 0});
    draw_rectangle(30, 30, 10, 10, (Color) {0, 255, 0});
    draw_rectangle(50, 50, 10, 10, (Color) {0, 0, 255});
    sys_nano_sleep(36);
    draw_letter(10, 10, 'A', (Color) {0, 255, 0}, 2);
    // clear_screen();
    char c;
    while(( c = getChar() ) != 'q' ){}
    enter_text_mode();
    return;
}

void welcome(){

}
void winScreen(){

}

void exit(){

}

// int64_t sys_draw_letter(uint64_t x, uint64_t y, char letter, Color color);
// dimensiones de la pantalla: 1024x768 --> se pueden conseguir usando sys_get_screen_information

void print_centered_string(uint64_t x, uint64_t y, const char* str, uint64_t font_size) {
    uint64_t character_width = CHARACTER_WIDTH * font_size;

    /*
    ScreenInformation screen_info;
    sys_get_screen_information(&screen_info);
    */

    uint64_t len = strlen(str);
    uint64_t start_x = x - (len / 2) * character_width;
    uint64_t start_y;
    // start_y = y - screen_info.character_height / 2;
    start_y = y;

    for (uint64_t i = 0; i < len; i++) {
        draw_letter(start_x + i * character_width, start_y, str[i], (Color){255, 0, 0}, font_size);
    }

}