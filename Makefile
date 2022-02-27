CC=cc
CFLAGS=-Wall -Wextra -Wpedantic -g -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRC=src
BIN=bin
OBJ=obj

all: touhou-bunker

touhou-bunker: main.o init.o
	$(CC) $(CFLAGS) -o touhou-bunker $(OBJ)/main.o $(OBJ)/init.o 

main.o: 
	$(CC) $(CFLAGS) -o $(OBJ)/main.o -c $(SRC)/main.c

init.o:
	$(CC) $(CFLAGS) -o $(OBJ)/init.o -c $(SRC)/init.c

clean:
	rm touhou-bunker
	rm $(OBJ)/*.o

run:
	./touhou-bunker
