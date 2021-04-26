#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(){

  /*Window and surface Initialization*/
  SDL_Window *window = nullptr;
  SDL_Surface *windowSurface = nullptr;
  SDL_Surface *imageSurface = nullptr;
  bool gameLoop = true;
  SDL_Event ev;

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
  }if(window == NULL)
    std::cout<< "Window Initialization failed: " << SDL_GetError() << std::endl;

    else{

      /*Window creation*/
      windowSurface = SDL_GetWindowSurface(window);
      imageSurface = SDL_LoadBMP("panzer.bmp");
      /*if the image wasn't able to be loaded*/
      if(imageSurface == NULL)
        std::cout << "Image loading failed: " << SDL_GetError() << std::endl;

      else{
        /*the game loop, only exits on demand (killing the program)*/
        while(gameLoop){

        /*load the bmp and draw it onto the windowSurface*/
        SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
        SDL_UpdateWindowSurface(window);

          while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT)
              gameLoop = false;
          }
        }
      }
  }
    /*free the memory*/
  SDL_FreeSurface(imageSurface);
  imageSurface = nullptr;
  SDL_DestroyWindow(window);
  window = nullptr;
  windowSurface = nullptr;
  SDL_Quit();

    return 0;
 }
