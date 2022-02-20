#include "init.h"

void initWindow(SDL_Window *win, SDL_Surface *screen)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      printf("initializing sdl failed: %s\n", SDL_GetError());
      SDL_Quit();
    }

  win = SDL_CreateWindow("touhou-bunker", 30, 30, 1280, 960, SDL_WINDOW_SHOWN);
  
  screen = SDL_GetWindowSurface(win);
}

bool bgLoad(SDL_Surface *background)
{
  int flags = IMG_INIT_PNG;
  int imgFlags = IMG_Init(flags);
  
  if((flags&imgFlags) != flags)
    {
      printf("loading png library failed: %s\n", IMG_GetError());
      return false;
    }
  
  
  background = IMG_Load("img/menu.png");

  if(!background)
    {
      printf("IMG_Load: %s\n", IMG_GetError());
      return false;
    }
  return true;
}


void errorSolution(SDL_Window *win, SDL_Surface *background)
{
  SDL_FreeSurface(background);
  SDL_DestroyWindow(win);
  IMG_Quit();
  SDL_Quit();
}

