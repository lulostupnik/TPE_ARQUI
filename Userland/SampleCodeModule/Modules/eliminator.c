#include <eliminator.h>

char map[MAP_HEIGHT][MAP_WIDTH];

void welcome(){
    clear_screen();
    print_centered_string(512, 10,"Bienvenido al Eliminator!",3);
    sys_nano_sleep(54);
    clear_screen();
    print_centered_string(512, 100,"Elija su Game Mode: (Presione la tecla correspondiente)",2);
    print_centered_string(512, 200,"s. Single Player",2);
    print_centered_string(512, 250,"m. Multiplayer",2);
    print_centered_string(512, 300,"q. Exit",2);
    char c;
    while((( c = getChar() ) != 'q' ) && (c != 'm' ) && (c != 's' )){}
    clear_screen();
    switch (c){
        case 'q': exit(); break;
        case 's': singlePlayer(); break;
        case 'm': multiPlayer(); break;
    }
}

void winScreen(){
    return;
}

// initialize_map();
// fill_position(1,1,RED);
void singlePlayer(){
    initialize_map();
    char c;
    char lost = 0;
    while(!lost){
        c = getChar();
        switch(c){
            case('w'): lost = 1; break;
            case('a'): lost = 1; break;
            case('s'): lost = 1; break;
            case('d'): lost = 1; break;
        }
    }
    return;
}

void multiPlayer(){
    return;
}

void exit(){
    clear_screen();
    print_centered_string(512, 384,"Saliendo",3);
    sys_nano_sleep(5);
    enter_text_mode();
    return;
}

void eliminator(){
    enter_video_mode();
    welcome();
    char c;
    while(( c = getChar() ) != 'q' ){}
    enter_text_mode();
    return;
}



void print_centered_string(uint64_t x, uint64_t y, const char* str, uint64_t font_size) {
    uint64_t character_width = CHARACTER_WIDTH * font_size;

    uint64_t len = strlen(str);
    uint64_t start_x = x - (len / 2) * character_width;
    uint64_t start_y;
    start_y = y;

    for (uint64_t i = 0; i < len; i++) {
        draw_letter(start_x + i * character_width, start_y, str[i], (Color){255, 0, 0}, font_size);
    }

}



void fill_position(uint64_t x, uint64_t y, Color color){
    if(x < 0 || y < 0 || x >= MAP_WIDTH || y > MAP_HEIGHT){
        return;
    }
    draw_rectangle(x*PIXEL, y*PIXEL, PIXEL, PIXEL, color);
    map[y][x] = 1;
    return;
}


/*
void makeBorders(){
    draw_rectangle(0, 0, screenW, PIXEL, BLUE);
    draw_rectangle(0, 0, screenW, PIXEL, BLUE);

    for(int i=0;i<screenW;i++){
        draw_pixel(i,0,BLUE);
        draw_pixel(i,screenW,BLUE);
    }
    for(int i=0;i<screenH;i++){
        draw_pixel(0,i,BLUE);
        draw_pixel(screenH,i,BLUE);
    }
    return;
}
*/
void initialize_map(){
    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_WIDTH; j++){
            map[i][j] = 0;
            if(i == 0 || i == MAP_HEIGHT-1 || j == 0 || j == MAP_WIDTH-1){
                fill_position(j, i, BLUE);
            }
        }
    }
    return;
}


/*
void singlePlayer(){
    initialize_map();
    char c;
    char lost = 0;
    while(!lost){
        c = getChar();
        switch(c){
            case('w'): lost = 1; break;
            case('a'): lost = 1; break;
            case('s'): lost = 1; break;
            case('d'): lost = 1; break;
        }
    }
    return;
}
 */