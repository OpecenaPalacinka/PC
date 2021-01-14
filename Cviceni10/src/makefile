# Použitý překladač
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi

# Binární soubory projektu
BIN = loader
OBJ = loader.o person.o vector.o

# Návody pro sestavení projektu
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS)

loader.o: loader.c
	$(CC) -c loader.c $(CFLAGS)

person.o: person.c
	$(CC) -c person.c $(CFLAGS)

vector.o: vector.c
	$(CC) -c vector.c $(CFLAGS)

# Na Windows místo rm bude del!
clean:
	rm -f $(BIN) $(OBJ)
