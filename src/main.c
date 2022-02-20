#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


#include "init.h"

int main()
{
  SDL_Window *win;
  SDL_Surface *screen;

  bool loopMenu = true;
  
  initWindow(win, screen);
  
  while(loopMenu)
    {
      // add the event stuff now
    }
  
  
  SDL_DestroyWindow(win);
  SDL_Quit();
  
  return 0;
}
