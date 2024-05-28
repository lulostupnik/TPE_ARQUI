#include <video.h>
#include <font.h>

#define SCREEN_WIDTH VBE_mode_info->width
#define SCREEN_HEIGHT VBE_mode_info->height

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

typedef struct{
    uint64_t x;
    uint64_t y;
}Point;

extern uint8_t font_bitmap[4096];
static Color background_color = {0,0,0};
static Color font_color = {255,255,255};
static uint64_t font_size = 1;
static uint8_t driver_mode = TEXT_MODE;
static Point current_screen_point = {0,0};



#define CHAR_BUFFER_ROWS  48         // Numero de caracteres disponibles con la fuente en 1 (en x).
#define CHAR_BUFFER_COLS  128


static uint8_t char_buffer[CHAR_BUFFER_ROWS * CHAR_BUFFER_COLS] = {0};
static uint64_t buffer_index = 0;
static uint64_t deleted_buffer_flag = 0;


static void printFont(uint8_t letter);


/*
 * @TODO importante
 */

static uint64_t screen_witdh_;
static uint64_t screen_height_;
//static ScreenInformation;  // igual creo qeu no me sirve para la matrix de chars.
void initialize_video_driver(){
    screen_witdh_ = VBE_mode_info->width;
    screen_height_ = VBE_mode_info -> height;
    //si quiero puedo inicializar aca a screenInformation

}

static void addCharToBuffer(uint8_t c) {
    char_buffer[buffer_index] = c;
    buffer_index ++;
    if (buffer_index  >= CHAR_BUFFER_ROWS*CHAR_BUFFER_COLS) {
        buffer_index = 0;
        char_buffer[0] = c;
        deleted_buffer_flag = buffer_index =1 ;
    }
}


/*
 * @Todo no es mejor devolver la estructura?
 */
int64_t vdriver_get_screen_information(ScreenInformation * screen_information){
    screen_information->width = SCREEN_WIDTH;
    screen_information->height = SCREEN_HEIGHT;
    return 1;
}

int64_t vdriver_clear_screen(Color color){
    vdriver_video_draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
}

//for text mode
static void clearScreen() {
    vdriver_clear_screen(background_color);
    current_screen_point.x = current_screen_point.y = 0;
    buffer_index = 0;
    deleted_buffer_flag = 1;
}

/*
 * @TODO
 * Testear. Fijarme que directamente lo mando a STDOUT
 */
#define STDOUT 0
#define STDERR 1
int64_t vdriver_set_mode(uint64_t mode){
    if(!(mode == TEXT_MODE || mode == VIDEO_MODE)){
        return 0;
    }
    driver_mode = mode;
    vdriver_clear_screen(background_color);
    if(mode==TEXT_MODE){
        uint8_t c;
        vdriver_text_write(STDOUT, char_buffer, buffer_index );
    }

}



#define Y_FONT_OFFSET (FONT_HEIGHT * font_size)
#define X_FONT_OFFSET (FONT_WIDTH * font_size)



static void newLinePrint(){
    current_screen_point.x = 0;
    current_screen_point.y = current_screen_point.y+ FONT_HEIGHT * font_size;
    if(current_screen_point.y + FONT_HEIGHT * font_size >= SCREEN_HEIGHT){
        clearScreen();
    }
}
static void newLineBuff(){
    if(buffer_index > CHAR_BUFFER_COLS*CHAR_BUFFER_ROWS - CHAR_BUFFER_COLS){
        clearScreen();
    }
    for(int i=buffer_index ; i<CHAR_BUFFER_COLS*CHAR_BUFFER_ROWS  ; i++){
        char_buffer[i] = 0;
        if((i%CHAR_BUFFER_COLS==0 ) && i !=buffer_index){
            buffer_index = i;
            return;
        }
    }
}
static void newLine(){
    newLinePrint();
    newLineBuff();
}

//VERIFICAR CASOS BORDES
static void backSpacePrint(){
    if(current_screen_point.x == 0 && current_screen_point.y == 0){
        return;
    }
    if(current_screen_point.x == 0){

        current_screen_point.y -= font_size*FONT_HEIGHT;  // y es dif a 0
        current_screen_point.x = SCREEN_WIDTH - font_size*FONT_WIDTH;
    }else{
        current_screen_point.x -= font_size*FONT_WIDTH;
    }
    vdriver_video_draw_rectangle(current_screen_point.x , current_screen_point.y, FONT_WIDTH * font_size, FONT_HEIGHT*font_size, background_color);
}

//CHECK !
static void backSpaceBuffer(){
    if(buffer_index != 0){
        char_buffer[--buffer_index] = 0;
    }
}

static void backSpace(){
    backSpacePrint();
    backSpaceBuffer();
}


static void printFont(uint8_t letter){

    if (current_screen_point.x+FONT_WIDTH*font_size >= SCREEN_WIDTH) {
        current_screen_point.y += FONT_HEIGHT*font_size;
        current_screen_point.x = 0;
    }
    if(current_screen_point.y + Y_FONT_OFFSET >= SCREEN_HEIGHT){
        clearScreen();
    }

    vdriver_video_draw_font(current_screen_point.x, current_screen_point.y, letter, font_color, font_size);
    current_screen_point.x+=FONT_WIDTH*font_size;
}

#define SPACE_PER_TAB 4

static void tabulator(){
    uint8_t c =' ';
    for(int i=0; i<SPACE_PER_TAB ; i++){
        addCharToBuffer(c);
        printFont(c);
    }
}
/*
 * @TODO cambiarle el color en stderr
 */
int64_t vdriver_text_write(uint64_t fd, const char * buffer, int64_t amount){
    uint64_t i = 0;
    if(!(fd == STDOUT || fd== STDERR)){
        return 0;
    }

    while (buffer[i] != 0 && i<amount) {
        switch (buffer[i]) {
            case '\n':
                newLine();
                break;
            case '\b':
                backSpace();
                break;
            case '\t':
                tabulator();
                break;
            default:
                if(buffer[i] >= FIRST_ASCII_FONT && buffer[i] <=LAST_ASCII_FONT){
                    addCharToBuffer(buffer[i]);
                    printFont(buffer[i]);
                }
                break;
        }
        i++;
    }
    return i;
}

/*
 * @TODO
 * test validaciones
 */
int64_t vdriver_video_draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, Color color){
    if(x+width > SCREEN_WIDTH || y+height > SCREEN_HEIGHT){
        return 1;
    }

    for (uint64_t i = 0; i < width; i++) {
        for (uint64_t j = 0; j < height; j++) {
            vdriver_video_draw_pixel( x + i, y + j, color);
        }
    }
    return 0;
}
int64_t vdriver_video_draw_font(uint64_t x, uint64_t y, uint8_t ascii, Color color,uint64_t fontSize){
    if(ascii < FIRST_ASCII_FONT || ascii > LAST_ASCII_FONT){
        return NOT_VALID_ASCII;
    }
    if(fontSize < 0 || SCREEN_WIDTH < fontSize*FONT_WIDTH || SCREEN_HEIGHT < fontSize*FONT_HEIGHT){
        return NOT_VALID_FONT_SIZE;
    } //esta validacion deberia ir  a setFontSoze

    int letter = (ascii-' ')*16;
    for (uint64_t i = 0; i < 16; i++) {
        for (uint64_t j = 0; j < 8; j++) {
            if((font_bitmap[letter+i] >> (7-j)) & 0x1){
                vdriver_video_draw_rectangle((x +j*fontSize), (y +i*fontSize),fontSize,fontSize, color);
            }
        }
    }
    return 0;
}


/*
 * @TODO validacion



/**
 * Puts a pixel at the specified (x, y) coordinates with the specified RGB color.
 * @para color: the color struct to draw the pixel.
 * @param x: The x-coordinate of the pixel.
 * @param y: The y-coordinate of the pixel.
 */

/*
 * @TODO validar la validacion
 */

int64_t vdriver_video_draw_pixel(uint64_t x, uint64_t y, Color color){

    if(x >= SCREEN_WIDTH || y>= SCREEN_HEIGHT){
        return 1;
    }

    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  color.b;
    framebuffer[offset+1]   =  color.g;
    framebuffer[offset+2]   =  color.r;
    return 0;
}





void video_main(){
    uint8_t c = 'a';
    uint8_t c2[] = "HOLA";

    for(int i=0; i<CHAR_BUFFER_ROWS*CHAR_BUFFER_COLS-200;i++){

//            vdriver_text_write(1, c2,5);
            vdriver_text_write(1, &c,1);

        if(c < 'z'){
            c++;
        }else{
            c = 'a';
        }
    }

}

