#!/bin/bash

echo "Compiling Touhou-Bunker..."

g++ main.cpp -o game -lSDL2 -lSDL2_image -lSDL2_mixer

echo "If you don't see any errors above, you have successfully compiled a binary for touhou-bunker! Start the game by executing ./game"
