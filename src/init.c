#include "init.h"

void initWindow()
{
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      printf("initializing sdl failed: %s\n", SDL_GetError());
      SDL_Quit();
    }

  menu->win = SDL_CreateWindow("touhou-bunker", 30, 30,
			      WINDOW_WIDTH, WINDOW_HEIGHT,
			      SDL_WINDOW_SHOWN);

  menu->rend = SDL_CreateRenderer(menu->win, -1,
				 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(!menu->rend)
    {
      printf("renderer error: %s\n", SDL_GetError());
    }
  
}


/*bool bgLoad()
{
  IMG_Init(IMG_INIT_PNG);
  
  bgTexture = IMG_LoadTexture(rend, "src/img/menu.png");

  if(!bgTexture)
    {
      printf("bgtexture: %s\n", IMG_GetError());
      return false;
    }
  
  return true;
  }*/

//TODO: use typedefs or commit suicide god damnit


void errorSolution()
{
  SDL_DestroyRenderer(menu->rend);
  SDL_FreeSurface(menu->background);
  SDL_DestroyWindow(menu->win);
  IMG_Quit();
  SDL_Quit();
}

