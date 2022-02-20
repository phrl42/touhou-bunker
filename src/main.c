#include "init.h"

int main() {
	SDL_Window *win = NULL;
	SDL_Surface *screen = NULL;

	SDL_Event ev;
	SDL_Rect pos;


	bool loopMenu = true;

	initWindow(win, screen);

	while(loopMenu) {
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
				case SDL_QUIT:
					loopMenu = false;
					break;
			}
		}
	}

	errorSolution(win, screen);
}

