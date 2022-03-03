#include "init.h"
#include <SDL2/SDL_render.h>

SDL_Window *win;
SDL_Renderer *rend;

//-------------MENU STUFF---------------
SDL_Rect rectfont0 = {(WINDOW_WIDTH / 2) + 400, (WINDOW_HEIGHT / 2), FONT_MENU_WIDTH, FONT_MENU_HEIGHT};
SDL_Rect rectfont1 = {(WINDOW_WIDTH / 2) + 370, (WINDOW_HEIGHT / 2) + 55, FONT_MENU_WIDTH, FONT_MENU_HEIGHT};
TTF_Font *font0;
SDL_Texture *texturefont0;
SDL_Texture *bgTexture;

TTF_Font *font1;
SDL_Texture *texturefont1;

int w = FONT_MENU_WIDTH;
int h = FONT_MENU_HEIGHT;

int menuLocation = 0;

SDL_Color colorOff = {255, 255, 255, 255};
SDL_Color colorOn = {255, 255, 0, 255};

SDL_Surface *surfacefont0;
SDL_Surface *surfacefont1;

//-------------STAGE 1 STUFF---------------
SDL_Texture *bgStageOne;

void initWindow()
{
  // initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printf("initializing sdl failed: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  // create a window
  win = SDL_CreateWindow("touhou-bunker", 30, 30,
                         WINDOW_WIDTH, WINDOW_HEIGHT,
                         SDL_WINDOW_SHOWN);

  // create a renderer
  rend = SDL_CreateRenderer(win, -1,
                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!rend)
  {
    printf("renderer error: %s\n", SDL_GetError());
  }

  if (Mix_Init(MIX_INIT_OGG) == 0)
  {
    printf("mixer failure: %s\n", Mix_GetError());
    Mix_Quit();
    SDL_Quit();
  }

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
  {
    printf("mixer open audio failure: %s\n", Mix_GetError());
    Mix_Quit();
    SDL_Quit();
    exit(2);
  }
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
  Mix_AllocateChannels(8);
}

void initFont()
{
  if (TTF_Init() == -1)
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
  if (menuLocation < 0)
  {
    menuLocation = MENU_ENTRIES;
  }
  else if (menuLocation > MENU_ENTRIES)
  {
    menuLocation = 0;
  }
  else
  {
    // dead
  }

  switch (menuLocation)
  {
  // START
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

  // QUIT
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

bool menuExecute()
{
  switch (menuLocation)
  {
  // START
  case 0:
    return true;
    break;

  // QUIT
  case 1:
    return false;
    break;

  default:
    return true;
    break;
  }
}

bool bgLoad()
{
  // loading image into memory
  SDL_Surface *background = IMG_Load("src/img/menu.png");

  if (!background)
  {
    printf("loading menu.png failed: %s\n", SDL_GetError());
    return false;
  }

  // load image data into graphics card hardware memory
  bgTexture = SDL_CreateTextureFromSurface(rend, background);

  // remove image data from memory
  SDL_FreeSurface(background);

  if (!bgTexture)
  {
    printf("creating texture failed: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

// TODO: use typedefs or commit suicide god dammit
//  i am too stupid for typedefs so I'll just use global variables || please dont kill me

void stageOneInit()
{
  SDL_DestroyTexture(texturefont0);
  SDL_DestroyTexture(texturefont1);
  SDL_DestroyTexture(bgTexture);

  SDL_Surface *surfaceStageOne = IMG_Load("src/img/bgFilled.png");

  bgStageOne = SDL_CreateTextureFromSurface(rend, surfaceStageOne);

  SDL_FreeSurface(surfaceStageOne);
  
  SDL_Surface *surfaceMap = IMG_Load("src/img/");
}

void errorSolution()
{
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);

  //-------------MENU STUFF---------------
  TTF_CloseFont(font0);
  SDL_DestroyTexture(texturefont0);
  SDL_DestroyTexture(texturefont1);
  SDL_DestroyTexture(bgTexture);

  //-------------STAGE 1 STUFF---------------
  SDL_DestroyTexture(bgStageOne);

  Mix_CloseAudio();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}