# Použitý překladač
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi

# Binární soubory projektu
BIN = fsmgen.exe
OBJ = fsmgen.o

# Návody pro sestavení projektu
$(BIN): $(OBJ)
	gcc $(OBJ) -o $(BIN) $(CFLAGS)

fsmgen.o: fsmgen.c
	gcc -c fsmgen.c $(CFLAGS)

clean:
	del -f $(BIN) $(OBJ)