CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi

default: sudos.exe

sudos.o:  sudos.c sudoku.c
	$(CC) $(CFLAGS) -c sudos.c sudoku.c

sudos.exe:  sudos.o
	$(CC) $(CFLAGS) -o sudos.exe  sudos.o sudoku.o


clean:
	-rm -f sudos.exe sudos.o sudoku.o
