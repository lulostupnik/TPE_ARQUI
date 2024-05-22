include ../Makefile.inc
//@TODO: Arreglar Makefile para que compile las capetas nuevas
MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)

all: $(MODULE)

$(MODULE): $(SOURCES)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld _loader.c $(SOURCES) -o ../$(MODULE)
	$(GCC) $(GCCFLAGS) -I./include -T sampleCodeModule.ld -Wl,--oformat=elf64-x86-64 _loader.c $(SOURCES) $(OBJECTS_ASM) -o ../0000-sampleCodeModule.elf #debug

clean:
	rm -rf *.o
	rm -rf *.elf

.PHONY: all clean print
