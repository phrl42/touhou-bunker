CC=cc
CFLAGS=-Wall -Wextra -Wpedantic -g -lSDL2 -lSDL2_image -lSDL2_mixer

SRC=src
BIN=bin
OBJ=obj

all: touhou-bunker

touhou-bunker: main.o init.o
	$(CC) $(CFLAGS) -o $(BIN)/touhou-bunker $(OBJ)/main.o $(OBJ)/init.o 

main.o: 
	$(CC) $(CFLAGS) -o $(OBJ)/main.o -c $(SRC)/main.c

init.o:
	$(CC) $(CFLAGS) -o $(OBJ)/init.o -c $(SRC)/init.c

clean:
	rm $(BIN)/touhou-bunker
	rm $(OBJ)/*.o
