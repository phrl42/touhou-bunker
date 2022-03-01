#ifndef __INIT_H_
#define __INIT_H_

#include "incs.h"

extern SDL_Window *win;
extern SDL_Renderer *rend;
extern SDL_Texture *bgTexture;

extern SDL_Rect rectfont0;
extern SDL_Rect rectfont1;
extern TTF_Font *font0;
extern SDL_Texture *texturefont0;

extern TTF_Font *font1;
extern SDL_Texture *texturefont1;

// so that main knows how to call the function
void initWindow();
void initFont();
void menuHover(int menu);
bool menuExecute();
bool bgLoad();
void errorSolution();

#endif
