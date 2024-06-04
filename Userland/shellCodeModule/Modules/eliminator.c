#include <eliminator.h>

char map[MAP_HEIGHT][MAP_WIDTH];

static void get_player_1_direction(uint16_t c, int64_t * direction);
static void get_player_2_direction(uint16_t c, int64_t * direction);

void welcome(){
    clear_screen();
    print_centered_string(512, 10,"Bienvenido al Eliminator!",3);
    sys_nano_sleep(18);
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

void singlePlayer(){
    initialize_map();
    uint64_t p1x = PLAYER_1_INIT_X;
    uint64_t p1y = PLAYER_1_INIT_Y - 10;
    uint64_t p1_lost = 0;
    int64_t direction[2] = {0,-1}; // al principio va hacía arriba
    uint16_t buffer[10];
    uint64_t buffer_size = 0;

    fill_position(p1x, p1y, RED);

    while(1){
        sys_nano_sleep(1);
        buffer_size = 0;
        buffer_size = sys_read(0, buffer, 1);


        if(buffer_size > 0){
            get_player_1_direction(buffer[buffer_size - 1], direction);
        }
        p1x += direction[0];
        p1y += direction[1];
        if(map[p1y][p1x] == 1){
            p1_lost = 1;
            break;
        }
        fill_position(p1x, p1y, RED);

    }

    print_centered_string(512, 384, "Perdiste", 2);

}



void multiPlayer(){
    initialize_map();
    uint64_t p1x = PLAYER_1_INIT_X;
    uint64_t p1y = PLAYER_1_INIT_Y - 1;
    uint64_t p2x = PLAYER_1_INIT_X;
    uint64_t p2y = 1;

    uint64_t p1_lost = 0;
    uint64_t p2_lost = 0;

    int64_t p1dir[2] = {0,-1};
    int64_t p2dir[2] = {0, 1};

    uint16_t buffer[10];
    uint64_t buffer_size = 0;

    fill_position(p1x, p1y, RED);
    fill_position(p2x, p2y, GREEN);

    while(1){
        sys_nano_sleep(3);
        buffer_size = 0;
        buffer_size = sys_read(0, buffer, 1);


        if(buffer_size > 0){
            get_player_1_direction(buffer[buffer_size - 1], p1dir);
            get_player_2_direction(buffer[buffer_size - 1], p2dir);
        }
        p1x += p1dir[0];
        p1y += p1dir[1];
        p2x += p2dir[0];
        p2y += p2dir[1];
        if(map[p1y][p1x] == 1){
            p1_lost = 1;
        }
        if(map[p2y][p2x] == 1){
            p2_lost = 1;
        }
        if(p1_lost || p2_lost){
            break;
        }
        fill_position(p1x, p1y, RED);
        fill_position(p2x, p2y, GREEN);

    }

    print_centered_string(512, 384, "Perdiste", 2);

}



static void get_player_1_direction(uint16_t c, int64_t * direction){
    switch(c) {
        case ('w'):
            if(direction[1] == 1){
                break;
            }
            direction[0] = 0;
            direction[1] = -1;
            break;
        case ('a'):
            if(direction[0] == 1){
                break;
            }
            direction[0] = -1;
            direction[1] = 0;
            break;
        case ('s'):
            if(direction[1] == -1){
                break;
            }
            direction[0] = 0;
            direction[1] = 1;
            break;
        case ('d'):
            if(direction[0] == -1){
                break;
            }
            direction[0] = 1;
            direction[1] = 0;
            break;
    }
}


get_player_2_direction(uint16_t c, int64_t * direction){
    switch(c) {
        case ('i'):
            if(direction[1] == 1){
                break;
            }
            direction[0] = 0;
            direction[1] = -1;
            break;
        case ('j'):
            if(direction[0] == 1){
                break;
            }
            direction[0] = -1;
            direction[1] = 0;
            break;
        case ('k'):
            if(direction[1] == -1){
                break;
            }
            direction[0] = 0;
            direction[1] = 1;
            break;
        case ('l'):
            if(direction[0] == -1){
                break;
            }
            direction[0] = 1;
            direction[1] = 0;
            break;
    }
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


void print_centered_string(uint64_t x, uint64_t y, const char* str, uint64_t font_size) { // @todo - está función podría no recibir coordenada x y directamente colocar el texto en el centro de la pantalla
    uint64_t len = strlen(str);
    uint64_t start_x = x - (len / 2) * CHARACTER_WIDTH * font_size;
    uint64_t start_y = y;
    print_string(start_x, start_y, str, font_size);
}



void print_string(uint64_t x, uint64_t y, const char* str, uint64_t font_size) {
    for (uint64_t i = 0; str[i] != '\0'; i++) {
        draw_letter(x + i * CHARACTER_WIDTH * font_size, y, str[i], (Color){255, 0, 0}, font_size);
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
        draw_rectangle(PIXEL * 2, PIXEL * 2, CHARACTER_WIDTH * 2,CHARACTER_HEIGHT * 2, BLACK);
        draw_letter(PIXEL * 2, PIXEL * 2, (char) ('0' + buffer_size), WHITE, 2);

        draw_rectangle(PIXEL * 5, PIXEL * 5, CHARACTER_WIDTH * 2,CHARACTER_HEIGHT * 2, BLACK);
        draw_letter(PIXEL * 5, PIXEL * 5, (char) buffer[buffer_size - 1], WHITE, 2);
        */