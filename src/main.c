#include "init.h"

int main()
{
  SDL_Window *win = NULL;
  
  SDL_Surface *screen = NULL; // instead of using SDL_Renderer
  SDL_Surface *background = NULL;

  SDL_Event ev;
  
  bool loopMenu = true;
  
  initWindow(win, screen);

  if(bgLoad(background) == false)
    {
      loopMenu = false;
    }

  // actual menu loop
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

  errorSolution(win, background); 
}
