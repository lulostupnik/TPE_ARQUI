#include <video.h>
#include <font.h>

#define SCREEN_WIDTH VBE_mode_info->width
#define SCREEN_HEIGHT VBE_mode_info->height
#define STDOUT 0
#define STDERR 1 //@TODO cmabiar
#define CHAR_BUFFER_ROWS  48         // Numero de caracteres disponibles con la fuente en 1 (en x).
#define CHAR_BUFFER_COLS  128
#define Y_FONT_OFFSET (FONT_HEIGHT * font_size)
#define X_FONT_OFFSET (FONT_WIDTH * font_size)

typedef struct{
    uint64_t x;
    uint64_t y;
}Point;

static VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;
extern uint8_t font_bitmap[4096];
static Color background_color = {0,0,0};
static Color font_color = {255,255,255};
static uint64_t font_size = 1;
static uint8_t driver_mode = TEXT_MODE;
static Point current_screen_point = {0,0};
static uint8_t char_buffer[CHAR_BUFFER_ROWS * CHAR_BUFFER_COLS] = {0};
static uint64_t buffer_index = 0;
static uint8_t deleted_buffer_flag = 0;
static uint8_t override_mode = 0;
static uint64_t char_buffer_rows_zoomed = CHAR_BUFFER_ROWS;
static uint64_t char_buffer_cols_zoomed = CHAR_BUFFER_COLS;


static void printFont(uint8_t letter);
static void clearScreen();
static uint64_t inTextMode();
static uint64_t inVideoMode();
static void addCharToBuffer(uint8_t c);
static void printFont(uint8_t letter);
static void clearScreen();
static void newLinePrint();
static void newLineBuff();
static void newLine();
static void backSpaceBuffer();
static void backSpace();
static void backSpacePrint();
static void tabulator();



/*
 * @TODO
 * manejar mejor el STDOUT y STDIN. Se podria hacer una variable estatica que sea el color con el que se imprime. Implementar
 */


int64_t vdriver_set_font_color(Color c){
    font_color = c;
}

int64_t vdriver_text_set_font_size(uint64_t size) {
    if( !inTextMode()){
        return 0;
    }

    if (size < 0 || SCREEN_WIDTH < size * FONT_WIDTH || SCREEN_HEIGHT < size * FONT_HEIGHT) {
        return NOT_VALID_FONT_SIZE;
    }
    if (size == font_size) {
        return 1;
    }
    font_size = size;
    char_buffer_rows_zoomed = SCREEN_HEIGHT / (font_size * FONT_HEIGHT);
    char_buffer_cols_zoomed = SCREEN_WIDTH / (font_size * FONT_WIDTH);
    clearScreen();
}

/*
 * @Todo no es mejor devolver la estructura?
 */
int64_t vdriver_get_screen_information(ScreenInformation * screen_information){
    screen_information->width = SCREEN_WIDTH;
    screen_information->height = SCREEN_HEIGHT;
    return 1;
}

//no me gusta que reciba el color, deberia ser otra fun capaz.
int64_t vdriver_clear_screen(Color color){
    if(driver_mode == TEXT_MODE){
        background_color = color;
        current_screen_point.x = current_screen_point.y = 0;
        buffer_index = 0;
        deleted_buffer_flag = 1;
    }
    override_mode = 1;
    vdriver_video_draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
    override_mode = 0;
    return 0;
}



/*
 * @TODO
 * Testear. Fijarme que directamente lo mando a STDOUT
 */

int64_t vdriver_set_mode(uint64_t mode, Color c){
    if(!(mode == TEXT_MODE || mode == VIDEO_MODE) ){
        return -1;
    }
    if(mode == driver_mode ){
        return 0;
    }
    driver_mode = mode;
    background_color = c;

    if(mode==TEXT_MODE){
        uint64_t aux = buffer_index;
        clearScreen();
        for(int i=0 ; i<aux ; i++){
            vdriver_text_write(STDOUT, &char_buffer[i], 1 );
        }
    }else{
        vdriver_clear_screen(c);
    }

    return 0;

}






/*
 * @TODO cambiarle el color en stderr
 */
int64_t vdriver_text_write(uint64_t fd, const char * buffer, int64_t amount){
    if(!inTextMode()){
        return 0;
    }
    if(!(fd == STDOUT || fd == STDERR)){
        return 0;
    }

    uint64_t i = 0;
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
        return -1;
    }
    if(!inVideoMode()){
        return -1;
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
    if(!inVideoMode()){
        return 0;
    }
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
*/


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
        return -1;
    }
    if(!inVideoMode()){
        return -1; // @TODO podría devolver -2
    }

    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  color.b;
    framebuffer[offset+1]   =  color.g;
    framebuffer[offset+2]   =  color.r;
    return 0;
}



/*
//@TODO borrar
void video_main(){
    uint8_t c = 'a';
    uint8_t c2[] = "HOLA";
    Color co = {10,30,22};
    vdriver_clear_screen(co);
    Color co2 = {100,32,100};
    vdriver_set_font_color(co2);

    for(int i=0; i<char_buffer_rows_zoomed*char_buffer_cols_zoomed-200;i++){

        vdriver_text_write(1, &c,1);
        if(c < 'z'){
            c++;
        }else{
            c = 'a';
        }
    }
}*/

//Funciones STATIC:
static uint64_t inTextMode(){
    return ((driver_mode == TEXT_MODE ) || override_mode);
}
static uint64_t inVideoMode(){
    return ((driver_mode==VIDEO_MODE) || override_mode);
}
#define SPACE_PER_TAB 4
static void tabulator(){
    uint8_t c =' ';
    for(int i=0; i<SPACE_PER_TAB ; i++){
        addCharToBuffer(c);
        printFont(c);
    }
}

static void addCharToBuffer(uint8_t c) {
    char_buffer[buffer_index] = c;
    buffer_index ++;
    if (buffer_index  >= char_buffer_rows_zoomed*char_buffer_cols_zoomed) {
        buffer_index = 0;
        char_buffer[0] = c;
        deleted_buffer_flag = buffer_index =1 ;
    }
}



static void printFont(uint8_t letter){

    if (current_screen_point.x+FONT_WIDTH*font_size >= SCREEN_WIDTH) {
        current_screen_point.y += FONT_HEIGHT*font_size;
        current_screen_point.x = 0;
    }
    if(current_screen_point.y + Y_FONT_OFFSET >= SCREEN_HEIGHT){
        clearScreen();
    }
    override_mode=1;
    vdriver_video_draw_font(current_screen_point.x, current_screen_point.y, letter, font_color, font_size);
    override_mode=0;
    current_screen_point.x+=FONT_WIDTH*font_size;
}

static void clearScreen() {   // se podria borrar esto
    vdriver_clear_screen(background_color);
}



static void newLinePrint(){
    current_screen_point.x = 0;
    current_screen_point.y = current_screen_point.y+ FONT_HEIGHT * font_size;
    if(current_screen_point.y + FONT_HEIGHT * font_size >= SCREEN_HEIGHT){
        clearScreen();
    }
}
static void newLineBuff(){
    if(buffer_index > char_buffer_cols_zoomed*char_buffer_rows_zoomed - char_buffer_cols_zoomed){
        clearScreen();
    }
    //char_buffer[buffer_index] = '\n';
    for(int i=buffer_index ; i<char_buffer_cols_zoomed*char_buffer_rows_zoomed  ; i++){
        //char_buffer[i] = 0;
        char_buffer[i] = ' ';  // esto solo funciona bien porque al cambiar de FONT_SIZE se hace un clear !. Seria mejor guardar el \n y llenar de ceros, pero boe
        if((i%char_buffer_cols_zoomed==0 ) && i !=buffer_index){
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
    override_mode=1;
    vdriver_video_draw_rectangle(current_screen_point.x , current_screen_point.y, X_FONT_OFFSET, FONT_HEIGHT*font_size, background_color);
    override_mode=0;
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
