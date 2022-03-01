#include "init.h"

int main()
{
  SDL_Event ev;

  bool loopMenu = true;
  bool stage1 = false;

  int menu;

  initWindow();

  Mix_Music *select = Mix_LoadMUS("src/bgm/select.ogg");

  if (!bgLoad())
  {
    loopMenu = false;
  }

  initFont();

  // actual menu loop
  while (loopMenu)
  {
    // clear the window
    SDL_RenderClear(rend);

    // draw image/font to window
    SDL_RenderCopy(rend, bgTexture, NULL, NULL);
    SDL_RenderCopy(rend, texturefont0, NULL, &rectfont0);
    SDL_RenderCopy(rend, texturefont1, NULL, &rectfont1);

    // switch back buffer with front buffer
    SDL_RenderPresent(rend);

    while (SDL_PollEvent(&ev))
    {
      switch (ev.type)
      {
      case SDL_QUIT:
        loopMenu = false;
        break;

      case SDL_KEYDOWN:
        switch (ev.key.keysym.sym)
        {
        case SDLK_UP:
          menu = -1;
          menuHover(menu);
          Mix_PlayMusic(select, 1);
          break;

        case SDLK_DOWN:
          menu = 1;
          menuHover(menu);
          Mix_PlayMusic(select, 1);
          break;

        case SDLK_RETURN:
          Mix_PlayMusic(select, 1);
          if (!menuExecute())
          {
            loopMenu = false;
          }
          else
          {
            loopMenu = false;
            stage1 = true;
          }
          break;

        default:
          break;
        }

      default:
        break;
      }
    }
  }

  stageOneInit();

  while (stage1)
  {
    // clear the window
    SDL_RenderClear(rend);

    // draw stuff
    SDL_RenderCopy(rend, bgStageOne, NULL, NULL);

    // switch back buffer with front buffer
    SDL_RenderPresent(rend);

    while (SDL_PollEvent(&ev))
    {
      switch (ev.type)
      {
      case SDL_QUIT:
        stage1 = false;
        break;
      }
    }
  }

  errorSolution();
}
