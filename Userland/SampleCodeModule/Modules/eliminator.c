#include <eliminator.h>

void welcome(){

}

void winScreen(){

}

void exit(){
    
}

void eliminator(){
    // puts("Welcome to Eliminator!\n");
    enter_video_mode();

    print_centered_string(512, 384, "Welcome to Eliminator!", 3);

    char c;
    while(( c = getChar() ) != 'q' ){}
    enter_text_mode();
    return;
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

