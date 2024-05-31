#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <video.h>
#include <idtLoader.h>
#include <syscalls.h>
#include <keyboard.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

void function1_key(){
//    uint8_t * c = "funciona mi implementacion!\n";
//    sys_write(1, c, 28);
}

int main()
{
    load_idt();
    setFKeyFunction(1, function1_key);
    //uint64_t drawString(uint64_t x, uint64_t y, uint8_t *string, uint64_t charsToDraw , uint64_t fontSize) {

    //drawString(0,0,"holas",4,43);
    // setFontSize(2);


//    int x = 0;
//    sysWrite(x,0,"a");
//    drawString(x,0,"a");

      // video_main();
      // int64_t sys_read(uint64_t fd, char * buffer, uint64_t amount);
        // putRectangle(100,50,200,120,120,20,20);
        // vdriver_video_draw_rectangle(120,120,20,20, (Color){100,50,200});

        /*
        sys_set_mode(1);
        Color co = {255,0,0};
        char ma = 'A';
        sys_draw_letter(100, 100, &ma, &co, 2);

        uint16_t c;
        while( sys_read(0, &c, 1) == 0);

        sys_set_mode(0);
         */


        /*
         printFont('A');
        */

//        while(1){
//            Color co = {0,0,0};
//        while( sys_read(0, &c, 1) == 0); //@TODO: definir STDIN
//            if(c == 1000){
//            }else if(c == '0'){
//
//                vdriver_set_mode(0,co );
//            }else if(c == '1'){
//                vdriver_set_mode(1,co );
//            }else if(c >= '2' && c<='9'){
//                vdriver_text_set_font_size(c - '0');
//            }
//            sys_write(1, &c, 1); // ¿porque le paso 1?
//        }


        /*
        printFont('B');
         */
	((EntryPoint)sampleCodeModuleAddress)();
	return 0;
}
