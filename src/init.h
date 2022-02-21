#ifndef __INIT_H_
#define __INIT_H_

#include "incs.h"

typedef struct {
  SDL_Window *win;
  SDL_Renderer *rend;
  SDL_Surface *background;
  SDL_Texture *bgTexture;
} Menu;

struct Menu *menu;

// so that main knows how to call the function
void initWindow();
bool bgLoad();
void errorSolution();

#endif
