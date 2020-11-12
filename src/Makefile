include Makefile.inc

all: run_me server client

server: server.c random.c ctfs.c lib.c run_me.o
		$(GCC) server.c random.c ctfs.c lib.c run_me.o -I./include $(GCCFLAGS) -o server

client: client.c
		$(GCC) client.c $(GCCFLAGS) -o client

run_me: run_me.asm
		$(ASM) $(ASMFLAGS) run_me.asm -o run_me.o

clean:
		rm run_me.o server client

.PHONY: all server client run_me clean