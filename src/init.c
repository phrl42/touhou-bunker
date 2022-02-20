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

void errorSolution(SDL_Window *win, SDL_Surface *screen)
{
  SDL_DestroyWindow(win);
  SDL_Quit();
  return EXIT_SUCCESS;
}

