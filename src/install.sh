#!/bin/bash

echo "Installing Touhou-Bunker..."

g++ main.cpp -o game -lSDL2 -lSDL2_image -lSDL2_mixer

echo "Successfully installed, run the game by executing ./game"
