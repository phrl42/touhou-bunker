#include "init.h"

int main()
{
  int menu;
  SDL_Event ev; 
  bool loopMenu = true;
  
  initWindow();

  if(!bgLoad())
    {
      loopMenu = false;
    }

  initFont();
  

  // actual menu loop
  while(loopMenu)
    {
      // clear the window
      SDL_RenderClear(rend);

      // draw image/font to window
      SDL_RenderCopy(rend, bgTexture, NULL, NULL);
      SDL_RenderCopy(rend, texturefont0, NULL, &rectfont0);
      SDL_RenderCopy(rend, texturefont1, NULL, &rectfont1);

      // switch back buffer with front buffer
      SDL_RenderPresent(rend);
      
      while(SDL_PollEvent(&ev))
  	  {
	      switch(ev.type)
	      {  
	        case SDL_QUIT:
	         loopMenu = false;
	         break;

          case SDL_KEYDOWN:
            switch(ev.key.keysym.sym)
            {
              case SDLK_UP:
                menu = -1;
                menuHover(menu);
                break;
              
              case SDLK_DOWN:
                menu = 1;
                menuHover(menu);
                break;

              default:
                break;
            }
           default: 
           break;
	      }
      }
      //SDL_Delay(1000 / 60); // is this even neccessary??
    }

  errorSolution(); 
}
