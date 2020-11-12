include Makefile.inc

SOURCES_CLIENT := $(wildcard src/client/*.c)
SOURCES_SERVER := $(wildcard src/server/*.c)
SOURCES_ASM := $(wildcard src/server/*.asm)
OBJECTS_ASM := $(SOURCES_ASM:.asm=.o)

all: asm client server

asm:
	@echo "Creating files for asm"
	@$(ASM) $(ASMFLAGS) $(SOURCES_ASM)

client:
	@echo "Creating files for client"
	@$(GCC) $(GCCFLAGS) $(SOURCES_CLIENT) -o client

server: asm
	@echo "Creating files for server"
	@$(GCC) $(GCCFLAGS) $(SOURCES_SERVER) $(OBJECTS_ASM) -o server

clean:
	@echo "Deleting objects"
	@rm -rf server quine client ./src/server/*.o

.PHONY: all clean server client asm


