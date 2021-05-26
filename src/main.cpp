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
	      SDL_DestroyWindow(window);
	      
	      window = SDL_CreateWindow("Touhou-Bunker",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					640, 480,
					SDL_WINDOW_SHOWN);

	      SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	      
	      SDL_Texture* texture = IMG_LoadTexture(renderer, "img/reimuback.png");

	      SDL_Rect texture_rect;
	      texture_rect.x = 300;  //the x coordinate
	      texture_rect.y = 400; // the y coordinate
	      texture_rect.w = 50; //the width of the texture
	      texture_rect.h = 50; //the height of the texture
	      
	      
	      while(true){

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
		      texture_rect.x -= 10;
		      break;
		      
		    case SDLK_RIGHT:
		      std::cout << "right" << std::endl;
		      texture_rect.x += 10;
		      break;
		      
		    case SDLK_UP:
		      std::cout << "up" << std::endl;
		      texture_rect.y -= 10;
		      break;
		      
		    case SDLK_DOWN:
		      std::cout << "down" << std::endl;
		      texture_rect.y += 10;
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

void start() {
	win->init();
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(IMG_INIT_PNG);

	background* bg = new background(win);
	bg->loadTexture(BACKGROUND1);

	terrain* o = new terrain(win);

	player* p = new player(win);

	boss_AI* b = new boss_AI(win, o);

	frametimer.start();
	projtimer.start();
	while(1) {
		if(!InputOutputManager(b, p, o)) break;

		win->clear(); //Clear GameWindow

		//Draw everything
		bg->draw();
		p->draw();
		o->draw();
		drawAllProjs();
		drawAllAnims();
		b->draw();

		win->present(); //Show everything we've drawn in the last step

		//Update everything
		updateAllAnims();
		b->update();
		p->update(o);
		bg->update(win->camera->ViewPortOffset);
		updateAllProjs(o);

		while(frametimer.elapsedTime()<MIN_FRAMETIME) SDL_Delay(1); //Really high framerates ruin physics :(
		frametimer.start();
	}
}

void drawAllAnims() {
	for(int i=0; i<anims.size(); i++) anims[i]->draw();
}

void drawAllProjs() {
	for(int i=0; i<projs.size(); i++) projs[i]->draw();
}

void updateAllProjs(terrain* ter) {
	for(int i=0; i<projs.size(); i++) {
		if(projs[i]->dead) {
			//spawn animation
			animation* onDeath = new animation(win);
			onDeath->setPos(projs[i]->getPos().x, projs[i]->getPos().y);
			onDeath->setAnim(EXPLOSIONSPRITE, 4, 4, 50, 1);
			anims.push_back(onDeath);
			//remove projectile
			delete projs[i];
			projs.erase(projs.begin()+i-1);
			i--;
		}
		projs[i]->update(ter);
	}
}

void updateAllAnims() {
	for(int i=0; i<anims.size(); i++) {
		if(anims[i]->dead) {
					delete anims[i];
					anims.erase(anims.begin()+i-1);
					i--;
		}
		anims[i]->update();
	}
}

bool InputOutputManager(boss_AI* b, player* p, terrain* o) {
	mousePos = win->getMousePosition();
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	if ( SDL_PollEvent(&e) ) {
		if (e.type == SDL_QUIT)	return false;
		else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) return false;
		else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1) {
			b->launchAttack(LASER);
		}
		else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2) {
			b->launchAttack(ROCKETS);
		}
		else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3) {
			b->spawnRockets = !b->spawnRockets;
		}
	}

	win->camera->follow(p->getPos());

	if(SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_GetMouseState(NULL, NULL)) == 8) o->create_square(mousePos, 25); // looks like right mouse button is 8. SDL_BUTTON_RIGHT seems to be broken
	if(SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_GetMouseState(NULL, NULL)) == SDL_BUTTON_LEFT && projtimer.elapsedTime()>300) {
		projectile* np = new projectile(win);
		np->setPos(p->getPos());
		np->launch(mousePos);
		projs.push_back(np);
		projtimer.start();
	}
	if (keys[SDL_SCANCODE_W]) p->accelerate(0,-PLAYER_ACCEL_Y);
	if (keys[SDL_SCANCODE_S]) p->accelerate(0,PLAYER_ACCEL_Y);
	if (keys[SDL_SCANCODE_D]) p->accelerate(PLAYER_ACCEL_X,0);
	if (keys[SDL_SCANCODE_A]) p->accelerate(-PLAYER_ACCEL_X,0);
	return true;
}

