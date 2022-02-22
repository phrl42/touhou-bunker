#include "init.h"

int main()
{
  SDL_Event ev;
  
  bool loopMenu = true;
  
  initWindow();

  if(!bgLoad())
    {
      loopMenu = false;
    }
  
  // actual menu loop
  while(loopMenu)
    {

      // clear the window
      
      SDL_RenderClear(rend);

      // draw image to window

      SDL_RenderCopy(rend, bgTexture, NULL, NULL);

      // switch back buffer with front buffer
      
      SDL_RenderPresent(rend);
      
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

  errorSolution(); 
}
