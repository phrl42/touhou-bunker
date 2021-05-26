#!/bin/bash

echo "Compiling touhou-bunker..."

g++ main.cpp -o game -lSDL2 -lSDL2_image -lSDL2_mixer

echo "If there are no errors above, the game installed itself successfully. Execute it by running: ./game"
