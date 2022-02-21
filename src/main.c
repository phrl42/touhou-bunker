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
