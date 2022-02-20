#include "init.h"

void initWindow(SDL_Window *win, SDL_Renderer *rend)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      printf("initializing sdl failed: %s\n", SDL_GetError());
      SDL_Quit();
    }

  win = SDL_CreateWindow("touhou-bunker", 30, 30,
			 WINDOW_WIDTH, WINDOW_HEIGHT,
			 SDL_WINDOW_SHOWN);

  rend = SDL_CreateRenderer(win, -1,
			    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(!rend)
    {
      printf("renderer error: %s\n", SDL_GetError());
    }
  
}


bool bgLoad(SDL_Renderer *rend, SDL_Texture *bgTexture)
{
  IMG_Init(IMG_INIT_PNG);
  
  bgTexture = IMG_LoadTexture(rend, "src/img/menu.png");

  if(!bgTexture)
    {
      printf("bgtexture: %s\n", IMG_GetError());
      return false;
    }
  
  return true;
}

//TODO: use typedefs or commit suicide god damnit


void errorSolution(SDL_Window *win, SDL_Surface *background, SDL_Renderer *rend)
{
  SDL_DestroyRenderer(rend);
  SDL_FreeSurface(background);
  SDL_DestroyWindow(win);
  IMG_Quit();
  SDL_Quit();
}

