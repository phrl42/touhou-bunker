#include "init.h"

SDL_Window *win;
SDL_Renderer *rend;
SDL_Surface *background;
SDL_Texture *bgTexture; 

void initWindow()
{

  // initialize SDL
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      printf("initializing sdl failed: %s\n", SDL_GetError());
      SDL_Quit();
    }

  win = SDL_CreateWindow("touhou-bunker", 30, 30,
			 WINDOW_WIDTH, WINDOW_HEIGHT,
			 SDL_WINDOW_SHOWN);

  // create a renderer
  
  rend = SDL_CreateRenderer(win, -1,
			    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(!rend)
    {
      printf("renderer error: %s\n", SDL_GetError());
    }
  
}

bool bgLoad()
{
  // loading image into memory
  
  background = IMG_Load("src/img/menu.png");

  if(!background)
    {
      printf("loading menu.png failed: %s\n", SDL_GetError());
      return false;
    }
  
  // load image data into graphics card hardware memory

  bgTexture = SDL_CreateTextureFromSurface(rend, background);

  // remove image data from memory
  
  SDL_FreeSurface(background);

  if(!bgTexture)
    {
      printf("creating texture failed: %s\n", SDL_GetError());
      return false;
    }

  return true;
  
}

//TODO: use typedefs or commit suicide god damnit
// i am too stupid for typedefs so I'll just use global variables || please dont kill me


void errorSolution()
{
  SDL_DestroyTexture(bgTexture);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  
  SDL_Quit();
}

