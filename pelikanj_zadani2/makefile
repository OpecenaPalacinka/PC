CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi

default: fsmgen.exe

fsmgen.exe:  fsmgen.o
	$(CC) $(CFLAGS) -o fsmgen.exe  fsmgen.o

fsmgen.o:  fsmgen.c
	$(CC) $(CFLAGS) -c fsmgen.c

clean:
	-rm -f fsmgen.exe fsmgen.o
