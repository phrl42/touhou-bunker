#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

int main(){

  //window and surface initialization
  SDL_Window *window = nullptr;
  SDL_Surface *windowSurface = nullptr;
  SDL_Surface *imageSurface = nullptr;
  bool menu = true;
  SDL_Event ev;  
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;
  
  //This is for keyboard handling stuff
  
  bool KEYS[322];  //322 SDLK_DOWN events

  for(int i = 0; i < 322; i++)  //set all events to false
    KEYS[i] = false;

  
  std::cout << "Don't mind all the logging." << std::endl;

  //loading video

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    std::cout << "Video Initialization error: " << SDL_GetError() << std::endl;

  //loading audio
  
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    std::cout << "Audio Initialization error: " << Mix_GetError() << std::endl;
  
  //if the video was able to be initialized

  else{ 

    //window parameters
    window = SDL_CreateWindow("Touhou-Bunker",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        640, 480,
                        SDL_WINDOW_SHOWN);
    
    //check if the window dies

  }if(!window)
    std::cout<< "Window Initialization failed: " << SDL_GetError() << std::endl;

  else{

    //window creation

    windowSurface = SDL_GetWindowSurface(window);
    imageSurface = SDL_LoadBMP("img/menu.bmp");

    //load the bgm

    Mix_Music *bgm = Mix_LoadMUS("bgm/test.mp3");

    //if the image wasn't able to be loaded

    if(imageSurface == NULL)
      std::cout << "Image loading failed: " << SDL_GetError() << std::endl;

    else{

      //play the music in a loop

      if(!Mix_PlayingMusic())
	Mix_PlayMusic(bgm, -1); //the -1 is for an infinite loop

      //the menu loop, only exits on demand (killing the program)

      while(menu){ 

	//this is the menu (no shit) 
	
        //load the bmp and draw it onto the windowSurface

	SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
        SDL_UpdateWindowSurface(window);

	while(SDL_PollEvent(&ev) != 0){
		  
	  switch(ev.type){
            //Look for a keypress
	  case SDL_KEYDOWN:
	    //Check the SDLKey values
	    switch(ev.key.keysym.sym){
		  
	    case SDLK_LEFT:
	      std::cout << "left" << std::endl;
	      break;
	    case SDLK_RIGHT:
	      std::cout << "right" << std::endl;
	      break;
	    case SDLK_UP:
	      std::cout << "up" << std::endl;
	      break;
	    case SDLK_DOWN:
	      std::cout << "down" << std::endl;
	      break;
	    case SDLK_q:
	      std::cout << "quitting menu..." << std::endl;
	      return -1;
	    case SDLK_RETURN: //this is the whole game lol
	      std::cout << "entering game..." << std::endl;
	      Mix_PauseMusic();
	      
	      SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	      
	      SDL_Texture* texture = IMG_LoadTexture(renderer, "img/reimuback.png");

	      SDL_Rect texture_rect;
	      texture_rect.x = 300;  //the x coordinate
	      texture_rect.y = 400; // the y coordinate
	      texture_rect.w = 50; //the width of the texture
	      texture_rect.h = 50; //the height of the texture
	      
	      
	      while(true){

		frameStart = SDL_GetTicks();
		
		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime){
		  SDL_Delay(frameDelay - frameTime);
		}
		
		SDL_RenderClear(renderer); //clears the renderer
		SDL_RenderCopy(renderer, texture, NULL, &texture_rect); // copies the Renderer
		SDL_RenderPresent(renderer); //updates the renderer
		
		while(SDL_PollEvent(&ev) != 0){
		  
		  switch(ev.type){
		    //Look for a keypress
		  case SDL_KEYDOWN:
		    //Check the SDLKey values
		    switch(ev.key.keysym.sym){
		      
		    case SDLK_q:
		      std::cout << "quitting out of stage1" << std::endl;
		      return -1;

		    case SDLK_LEFT:
		      std::cout << "left" << std::endl;
		      texture_rect.x -= 25;
		      break;
		      
		    case SDLK_RIGHT:
		      std::cout << "right" << std::endl;
		      texture_rect.x += 25;
		      break;
		      
		    case SDLK_UP:
		      std::cout << "up" << std::endl;
		      texture_rect.y -= 25;
		      break;
		      
		    case SDLK_DOWN:
		      std::cout << "down" << std::endl;
		      texture_rect.y += 25;
		      break;
		      
		    default:
		      break;
		    }
		  }
		}
	      }
      	    }
	  }	  
	}
      }
    }
  }
  //free the allocated memory
  SDL_FreeSurface(imageSurface);
  SDL_DestroyWindow(window);
  //Mix_FreeMusic(bgm);  ignore this for now
  Mix_Quit();
  SDL_Quit();

  return 0;
}
