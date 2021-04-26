#!/bin/bash

echo "Installing Touhou-Bunker..."

g++ main.cpp -o game -lSDL2 -lSDL2_image

echo "Succesfully installed, run the game by running ./game"
