#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int main(){

  /*window and surface initialization*/
  SDL_Window *window = nullptr;
  SDL_Surface *windowSurface = nullptr;
  SDL_Surface *imageSurface = nullptr;
  bool menu = true;
  SDL_Event ev;
  
  /*This is for keyboard handling stuff*/
  
  bool KEYS[322];  /* 322 SDLK_DOWN events*/

  for(int i = 0; i < 322; i++)  /* all events to false*/
    KEYS[i] = false;

  
  std::cout << "Don't mind all the logging." << std::endl;

  /*loading video*/

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    std::cout << "Video Initialization error: " << SDL_GetError() << std::endl;

  /*loading audio*/
  
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    std::cout << "Audio Initialization error: " << Mix_GetError() << std::endl;
  
  /*if the video was able to be initialized*/

  else{ 

    /*window parameters*/
    window = SDL_CreateWindow("Touhou-Bunker",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        640, 480,
                        SDL_WINDOW_SHOWN);
    
    /*check if the window dies*/

  }if(!window)
    std::cout<< "Window Initialization failed: " << SDL_GetError() << std::endl;

  else{

    /*window creation*/

    windowSurface = SDL_GetWindowSurface(window);
    imageSurface = SDL_LoadBMP("menu.bmp");

    /*load the bgm*/

    Mix_Music *bgm = Mix_LoadMUS("test.mp3");

    /*if the image wasn't able to be loaded*/

    if(imageSurface == NULL)
      std::cout << "Image loading failed: " << SDL_GetError() << std::endl;

    else{

      /*play the music in a loop*/

      if(!Mix_PlayingMusic())
	Mix_PlayMusic(bgm, -1); /*the -1 is for an infinite loop*/

      /*the menu loop, only exits on demand (killing the program)*/

      while(menu){ 

	/*this is the menu (no shit) */
	
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
	    case SDLK_q:
	      menu = false;
	      std::cout << "quitting menu..." << std::endl;
	      break;
	    case SDLK_RETURN:
	      std::cout << "entering game..." << std::endl;
	      Mix_Quit();
	      
	      /*todo*/	
	    default:
	      break;
	       
	    }
	    /*there are 2 switch statements, so don't forget to break twice!(it was painful to find it out)*/
	    if(menu == false)
	      break;
	  }	  
	}
      }
    }
  }
  /*free the allocated memory*/
  SDL_FreeSurface(imageSurface);
  SDL_DestroyWindow(window);
  /*Mix_FreeMusic(bgm);  ignore this for now*/
  Mix_Quit();
  SDL_Quit();

  return 0;
}
