#include "init.h"


int main()
{
  SDL_Window *win = NULL;
  SDL_Renderer *rend = NULL;
  SDL_Surface *background = NULL;
  SDL_Texture *bgTexture;
  
  SDL_Event ev;
  
  bool loopMenu = true;
  
  initWindow(win, rend);

  if(!bgLoad(rend, bgTexture))
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

      SDL_RenderClear(rend);
      SDL_RenderCopy(rend, bgTexture, NULL, NULL);
      SDL_RenderPresent(rend);
    }

  errorSolution(win, background, rend); 
}
