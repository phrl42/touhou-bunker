#include "init.h"
#include <SDL2/SDL_render.h>

SDL_Window *win;
SDL_Renderer *rend;
SDL_Texture *bgTexture;

// there has to be a better solution for this
SDL_Rect rectfont0 = {(WINDOW_WIDTH / 2) + 400 ,(WINDOW_HEIGHT / 2), FONT_MENU_WIDTH, FONT_MENU_HEIGHT};
SDL_Rect rectfont1 = {(WINDOW_WIDTH / 2) + 370, (WINDOW_HEIGHT / 2) + 55, FONT_MENU_WIDTH, FONT_MENU_HEIGHT};
TTF_Font *font0;
SDL_Texture *texturefont0;

TTF_Font *font1;
SDL_Texture *texturefont1;

int w = FONT_MENU_WIDTH;
int h = FONT_MENU_HEIGHT;

int menuLocation = 0;

SDL_Color colorOff = { 255, 255, 255 };
SDL_Color colorOn = { 255, 255, 0 };

SDL_Surface *surfacefont0;
SDL_Surface *surfacefont1;

void initWindow()
{
  // initialize SDL
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      printf("initializing sdl failed: %s\n", SDL_GetError());
      SDL_Quit();
    }

  // create a window
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

void initFont()
{
  if(TTF_Init() == -1)
    {
      printf("failed to load sdl2-ttf: %s\n", TTF_GetError());
    }

  // give it the actual font file 
  font0 = TTF_OpenFont("src/ttf/mononoki-Regular.ttf", 25); 
  font1 = TTF_OpenFont("src/ttf/mononoki-Regular.ttf", 25);

  // create surface for font
  surfacefont0 = TTF_RenderText_Solid(font0, "Start", colorOn);
  // create texture to load into hardware
  texturefont0 = SDL_CreateTextureFromSurface(rend, surfacefont0);
  // give font dimensions
  SDL_QueryTexture(texturefont0, NULL, NULL, &w, &h);
  // clear from memory
  SDL_FreeSurface(surfacefont0);

  surfacefont1 = TTF_RenderText_Solid(font1, "Quit", colorOff); 
  texturefont1 = SDL_CreateTextureFromSurface(rend, surfacefont1);
  SDL_QueryTexture(texturefont1, NULL, NULL, &w, &h);
  SDL_FreeSurface(surfacefont1);
}

void menuHover(int menu)
{
  menuLocation += menu;
  if(menuLocation < 0)
  {
    menuLocation = MENU_ENTRIES;
  }
  else if(menuLocation > MENU_ENTRIES)
  {
    menuLocation = 0;
  }
  else
  {
    // dead
  }

  switch(menuLocation)
  {
    case 0:
      // reset non-active label
      surfacefont1 = TTF_RenderText_Solid(font1, "Quit", colorOff); 
      texturefont1 = SDL_CreateTextureFromSurface(rend, surfacefont1);
      SDL_QueryTexture(texturefont1, NULL, NULL, &w, &h);
      SDL_FreeSurface(surfacefont1);
      
      // activate active label
      surfacefont0 = TTF_RenderText_Solid(font0, "Start", colorOn); 
      texturefont0 = SDL_CreateTextureFromSurface(rend, surfacefont0);
      SDL_QueryTexture(texturefont0, NULL, NULL, &w, &h);
      SDL_FreeSurface(surfacefont0);
      break;
    
    case 1: 
      // reset non-active label
      surfacefont0 = TTF_RenderText_Solid(font0, "Start", colorOff); 
      texturefont0 = SDL_CreateTextureFromSurface(rend, surfacefont0);
      SDL_QueryTexture(texturefont0, NULL, NULL, &w, &h);
      SDL_FreeSurface(surfacefont0);

      // activate active label
      surfacefont1 = TTF_RenderText_Solid(font1, "Quit", colorOn); 
      texturefont1 = SDL_CreateTextureFromSurface(rend, surfacefont1);
      SDL_QueryTexture(texturefont1, NULL, NULL, &w, &h);
      SDL_FreeSurface(surfacefont1);
      break;
  }
}

bool bgLoad()
{
  // loading image into memory
  SDL_Surface *background = IMG_Load("src/img/menu.png");

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

  TTF_CloseFont(font0);
  SDL_DestroyTexture(texturefont0);
  SDL_DestroyTexture(texturefont1);

  TTF_Quit();
  SDL_Quit();
}

