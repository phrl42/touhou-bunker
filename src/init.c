#include <SDL2/SDL.h>

void initWindow(SDL_Window *win, SDL_Surface *screen)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
      SDL_GetError();
    }

  win = SDL_CreateWindow("title", 30, 30, 640, 480, SDL_WINDOW_SHOWN);
  
  screen = SDL_GetWindowSurface(win);
  
  return;
}

void contentWindow(SDL_Surface *test, SDL_Rect *pos)
{
  pos->x = 640 / 2;
  pos->y = 480;

}

