#!/bin/bash

echo "Installing Touhou-Bunker..."

g++ main.cpp -o game -lSDL2 -lSDL2_image -lSDL2_mixer

echo "Succesfully installed, run the game by running ./game"
