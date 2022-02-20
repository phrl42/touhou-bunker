#ifndef __INIT_H_
#define __INIT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <stdbool.h>

#include "defs.h"

// so that main knows how to call the function
void initWindow(SDL_Window *win, SDL_Renderer *rend);
bool bgLoad(SDL_Renderer *rend, SDL_Texture *bgTexture);
void errorSolution(SDL_Window *win, SDL_Surface *background, SDL_Renderer *rend);

#endif
