#ifndef __INIT_H_
#define __INIT_H_

#include "incs.h"

extern SDL_Window *win;
extern SDL_Renderer *rend;
extern SDL_Surface *background;
extern SDL_Texture *bgTexture;

// so that main knows how to call the function
void initWindow();
bool bgLoad();
void errorSolution();

#endif
