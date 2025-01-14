#include <eliminator.h>
#include <libc.h>

char map[MAP_HEIGHT][MAP_WIDTH];

static void get_player_1_direction(uint16_t c, int64_t * direction);
static void get_player_2_direction(uint16_t c, int64_t * direction);
static void play_arcade_song();
static void retryMenuSingleplayer();
static void singlePlayer();
static void retryMenuMultiplayer(int whoWon, int scores[]);
static void multiPlayer();

static void print_centered_string(uint64_t x, uint64_t y, const char* str, uint64_t font_size);
static void print_string(uint64_t x, uint64_t y, const char* str, uint64_t font_size);
static void fill_position(uint64_t x, uint64_t y, Color color);
static void initialize_map();


void welcome(){
    clear_screen();
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,"Bienvenido al Eliminator!",3);
    play_arcade_song();
    clear_screen();
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-100,"Elija su Game Mode: (Presione la tecla correspondiente)",2);
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-50,"s. Single Player",2);
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,"m. Multiplayer",2);
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+50,"q. Exit",2);

    char c;
    while((( c = getChar() ) != 'q' ) && (c != 'm' ) && (c != 's' )){}
    clear_screen();
    switch (c){
        case 'q': break;
        case 's': singlePlayer(); break;
        case 'm': multiPlayer(); break;
    }
    return;
}

static void retryMenuSingleplayer(){
    clear_screen();
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-300,"Perdiste! Mejor suerte la proxima",2);
    sys_nano_sleep(18);
    clear_screen();
    print_centered_string(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2,"r. Retry",2);
    print_centered_string(SCREEN_WIDTH/2+100, SCREEN_HEIGHT/2,"m. Main Menu",2);
    
    char c;
    while((( c = getChar() ) != 'r' ) && (c != 'm' )){}
    clear_screen();
    switch (c){
        case 'r': singlePlayer(); break;
        case 'm': welcome(); break;
    }
}

static void singlePlayer(){
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,"Utilice W-A-S-D para moverse",2);
    sys_nano_sleep(50);
    clear_screen();
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

    retryMenuSingleplayer();

}

static void retryMenuMultiplayer(int whoWon, int scores[]){
    clear_screen();
    if(whoWon == 1)
        print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,"Ganador: Jugador 1",3);
    else if(whoWon == 2)
        print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,"Ganador: Jugador 2",3);
    else
        print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2,"Empate",3);

    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 50,"Puntaje",2);
    print_centered_string(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2 + 100,numToString(scores[0],10),2);
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100," VS ",2);
    print_centered_string(SCREEN_WIDTH/2+100, SCREEN_HEIGHT/2 + 100,numToString(scores[1],10),2);

    sys_nano_sleep(50);
    clear_screen();
    print_centered_string(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2,"r. Retry",2);
    print_centered_string(SCREEN_WIDTH/2+100, SCREEN_HEIGHT/2,"m. Main Menu",2);
    
    char c;
    while((( c = getChar() ) != 'r' ) && (c != 'm' )){}
    clear_screen();
    switch (c){
        case 'r': multiPlayer(); break;
        case 'm': welcome(); break;
    }
}

static void multiPlayer(){
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-50,"Jugador 1: Utilice W-A-S-D para moverse",2);
    print_centered_string(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+50,"Jugador 2: Utilice I-J-K-L para moverse",2);
    sys_nano_sleep(50);
    clear_screen();
    static int scores[2] = {0,0}; //No Funciona Si Jugas mas de 2^64 Veces jaja :D
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
        sys_nano_sleep(1);
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
        if(p1y==p2y && p1x==p2x){
            p1_lost = 1;
            p2_lost = 1;
            break;
        }
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
    if(p1_lost && p2_lost){
     retryMenuMultiplayer(0,scores);
    }
    if(p2_lost){
        scores[0]++;
        retryMenuMultiplayer(1,scores);
    } else {
        scores[1]++;
        retryMenuMultiplayer(2,scores);

    }

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


static void get_player_2_direction(uint16_t c, int64_t * direction){
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

void eliminator(){
    enter_video_mode();
    welcome();
    clear_screen();
    print_centered_string(512, 384,"Saliendoo",3);
    beep(100,5);
    beep(50,5);
    enter_text_mode();
    return;
}


static void print_centered_string(uint64_t x, uint64_t y, const char* str, uint64_t font_size) {
    uint64_t len = strlen(str);
    uint64_t start_x = x - (len / 2) * CHARACTER_WIDTH * font_size;
    uint64_t start_y = y;
    print_string(start_x, start_y, str, font_size);
}


static void print_string(uint64_t x, uint64_t y, const char* str, uint64_t font_size) {
    for (uint64_t i = 0; str[i] != '\0'; i++) {
        draw_letter(x + i * CHARACTER_WIDTH * font_size, y, str[i], (Color){0, 255, 0}, font_size);
    }
}



static void fill_position(uint64_t x, uint64_t y, Color color){
    if(x < 0 || y < 0 || x >= MAP_WIDTH || y > MAP_HEIGHT){
        return;
    }
    draw_rectangle(x*PIXEL, y*PIXEL, PIXEL, PIXEL, color);
    map[y][x] = 1;
    return;
}


static void initialize_map(){
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

static void play_arcade_song() {
    // Frequencies for the notes in the song.
    uint32_t C4 = 262;
    uint32_t D4 = 294;
    uint32_t E4 = 330;
    uint32_t F4 = 349;
    uint32_t G4 = 392;
    uint32_t A4 = 440;
    uint32_t B4 = 494;
    uint32_t C5 = 523;

    // Duration of each note in milliseconds.
    int quarter_note = 500 / 55;
    int eighth_note = quarter_note / 3;

    // Play the song.
    beep(C4, eighth_note);
    beep(E4, eighth_note);
    beep(G4, eighth_note);
    beep(C5, eighth_note);
}

