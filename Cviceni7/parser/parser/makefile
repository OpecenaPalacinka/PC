# Použitý překladač
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi

# Binární soubory projektu
BIN = parser
OBJ = stack.o parser.o operators.o

# Návody pro sestavení projektu
$(BIN): $(OBJ)
	gcc $(OBJ) -o $(BIN) $(CFLAGS)

stack.o: stack.c stack.h
	gcc -c stack.c $(CFLAGS)

parser.o: parser.c
	gcc -c parser.c $(CFLAGS)

operators.o: operators.c operators.h
	gcc -c operators.c $(CFLAGS)

clean:
	rm -f $(BIN) $(OBJ)