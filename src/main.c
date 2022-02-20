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
  SDL_Event ev;
  SDL_Rect pos;
  SDL_Surface *test;

  bool loopMenu = true;
  
  initWindow(win, screen);
  
  while(loopMenu)
    {
      while(SDL_PollEvent(&ev))
	{
	  
	  switch(ev.type)
	    {  
	      case SDL_QUIT:
		loopMenu = false;
		break;
	    }
	  
	}
    }
  
  SDL_FreeSurface(test);
  SDL_FreeSurface(screen);
  SDL_DestroyWindow(win);
  SDL_Quit();
  
  return 0;
}
