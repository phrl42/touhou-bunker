#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(){

  /*window and surface initialization*/
  SDL_Window *window = nullptr;
  SDL_Surface *windowSurface = nullptr;
  SDL_Surface *imageSurface = nullptr;
  bool menu = true;
  SDL_Event ev;
  /*This is for keyboard handling stuff*/
  
  bool KEYS[322];  /* 322 SDLK_DOWN events*/

  for(int i = 0; i < 322; i++) { /* all events to false*/
    KEYS[i] = false;
}

  //  SDL_EnableKeyRepeat(0,0); /*check for holding the key down*/


  std::cout << "Don't mind all the logging." << std::endl;

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    std::cout << "Video Initialization error: " << SDL_GetError() << std::endl;

  else{ /*if the video was able to be initialized*/

    /*window parameters*/
    window = SDL_CreateWindow("Touhou-Bunker",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        640, 480,
                        SDL_WINDOW_SHOWN);
    /*if the window suddenly dies*/
  }if(!window)
    std::cout<< "Window Initialization failed: " << SDL_GetError() << std::endl;

    else{

      /*window creation*/
      windowSurface = SDL_GetWindowSurface(window);
      imageSurface = SDL_LoadBMP("menu.bmp");
      /*if the image wasn't able to be loaded*/
      if(imageSurface == NULL)
        std::cout << "Image loading failed: " << SDL_GetError() << std::endl;

      else{
        /*the menu loop, only exits on demand (killing the program)*/
        while(menu){ 

	  /*this is the menu*/
	
        /*load the bmp and draw it onto the windowSurface*/
        SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
        SDL_UpdateWindowSurface(window);

          while(SDL_PollEvent(&ev) != 0){
		  
	    switch(ev.type){
            /*Look for a keypress*/
            case SDL_KEYDOWN:
                /*Check the SDLKey values*/
                switch(ev.key.keysym.sym){
		  
                    case SDLK_LEFT:
		      std::cout << "left press" << std::endl;
                        break;
                    case SDLK_RIGHT:
		      std::cout << "right press" << std::endl;
                        break;
                    case SDLK_UP:
		      std::cout << "up press" << std::endl;
                        break;
                    case SDLK_DOWN:
		      std::cout << "down press" << std::endl;
                        break;
                    case SDL_QUIT:
		      menu = false;
		      std::cout << "do you see this" << std::endl;
		    case SDLK_RETURN:
		      std::cout << "Entering game..." << std::endl;
		      /*todo*/
		      break;
		    default:
                        break;
	       
                }
            }
        
          }
        }
   }
 }
    /*free the allocated memory*/
  SDL_FreeSurface(imageSurface);
  SDL_DestroyWindow(window);
  SDL_Quit();

    return 0;
 }
