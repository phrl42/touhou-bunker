#include "init.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_thread.h>

SDL_Window *win;
SDL_Renderer *rend;

//-------------MENU STUFF---------------
SDL_Rect rectfont0 = {(WINDOW_WIDTH / 2) + 400, (WINDOW_HEIGHT / 2), FONT_MENU_WIDTH, FONT_MENU_HEIGHT};
SDL_Rect rectfont1 = {(WINDOW_WIDTH / 2) + 370, (WINDOW_HEIGHT / 2) + 55, FONT_MENU_WIDTH, FONT_MENU_HEIGHT};
TTF_Font *font0;
SDL_Texture *texturefont0;
SDL_Texture *bgTexture;

TTF_Font *font1;
SDL_Texture *texturefont1;

int w = FONT_MENU_WIDTH;
int h = FONT_MENU_HEIGHT;

int speed = 8;
int menuLocation = 0;

SDL_Color colorOff = {255, 255, 255, 255};
SDL_Color colorOn = {255, 255, 0, 255};

SDL_Surface *surfacefont0;
SDL_Surface *surfacefont1;

//--------------GENERAL STUFF--------------
SDL_Texture *bgStages;
SDL_Rect rectStageArea = {(WINDOW_WIDTH / 45), (WINDOW_HEIGHT / 35), (WINDOW_WIDTH / 2) + 100, (WINDOW_HEIGHT - (WINDOW_HEIGHT / 20))};
TTF_Font *fontHighScore;
TTF_Font *fontScore;
SDL_Texture *textureHighScore;
SDL_Texture *textureScore;

SDL_Rect rectHighScore = {(WINDOW_WIDTH / 2) + 150, (WINDOW_HEIGHT / 35), FONT_MENU_WIDTH + 80, FONT_MENU_HEIGHT - 10};
SDL_Rect rectScore = {(WINDOW_WIDTH / 2) + 150, (WINDOW_HEIGHT / 35) + 100, FONT_MENU_WIDTH, FONT_MENU_HEIGHT - 10};

SDL_Texture *player[24];
SDL_Rect rectPlayer = {((WINDOW_WIDTH / 2) + 100) / 2, (WINDOW_HEIGHT - (WINDOW_HEIGHT / 20)) - 100, 70, 70};

bool up = false, down = false, left = false, right = false, idle = true;

SDL_Thread *threadAnimation;
char file[18] = "src/img/reimuX.png";
//-------------STAGE 1 STUFF---------------
SDL_Texture *bgStageOne;

const Uint8 *keys;

void initWindow()
{
  // initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    SDL_Log("initializing sdl failed: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  // create a window
  win = SDL_CreateWindow("touhou-bunker", 30, 30,
                         WINDOW_WIDTH, WINDOW_HEIGHT,
                         SDL_WINDOW_SHOWN);

  // create a renderer
  rend = SDL_CreateRenderer(win, -1,
                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!rend)
  {
    SDL_Log("renderer error: %s\n", SDL_GetError());
  }

  if (Mix_Init(MIX_INIT_OGG) == 0)
  {
    SDL_Log("mixer failure: %s\n", Mix_GetError());
    Mix_Quit();
    SDL_Quit();
  }

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
  {
    SDL_Log("mixer open audio failure: %s\n", Mix_GetError());
    Mix_Quit();
    SDL_Quit();
    exit(2);
  }
  // I dont want ahmed to overflow the repo with issues
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
  // to mix music (play sounds simultaneously)
  Mix_AllocateChannels(8);

  SDL_SetHint(SDL_HINT_RENDER_DRIVER,"opengl");
}

void initMenu()
{
  // loading image into memory
  SDL_Surface *background = IMG_Load("src/img/menu.png");

  if (!background)
  {
    SDL_Log("loading menu.png failed: %s\n", SDL_GetError());
    exit(3);
  }

  // load image data into graphics card hardware memory
  bgTexture = SDL_CreateTextureFromSurface(rend, background);

  // remove image data from memory
  SDL_FreeSurface(background);

  if (!bgTexture)
  {
    SDL_Log("creating texture failed: %s\n", SDL_GetError());
    exit(4);
  }
  if (TTF_Init() == -1)
  {
    SDL_Log("failed to load sdl2-ttf: %s\n", TTF_GetError());
  }

  // give it the actual font file
  font0 = TTF_OpenFont("src/ttf/mononoki-Regular.ttf", 25);
  font1 = TTF_OpenFont("src/ttf/mononoki-Regular.ttf", 25);

  // create surface for font
  surfacefont0 = TTF_RenderText_Solid(font0, "Start", colorOn);
  // create texture to load into hardware
  texturefont0 = SDL_CreateTextureFromSurface(rend, surfacefont0);
  // give font dimensions
  SDL_QueryTexture(texturefont0, NULL, NULL, &w, &h);
  // clear from memory
  SDL_FreeSurface(surfacefont0);

  surfacefont1 = TTF_RenderText_Solid(font1, "Quit", colorOff);
  texturefont1 = SDL_CreateTextureFromSurface(rend, surfacefont1);
  SDL_QueryTexture(texturefont1, NULL, NULL, &w, &h);
  SDL_FreeSurface(surfacefont1);
}

void menuHover(int menu)
{
  // hover ,,animation''
  menuLocation += menu;
  if (menuLocation < 0)
  {
    menuLocation = MENU_ENTRIES;
  }
  else if (menuLocation > MENU_ENTRIES)
  {
    menuLocation = 0;
  }
  else
  {
    // dead
  }

  switch (menuLocation)
  {
  // START
  case 0:
    // reset non-active label
    surfacefont1 = TTF_RenderText_Solid(font1, "Quit", colorOff);
    texturefont1 = SDL_CreateTextureFromSurface(rend, surfacefont1);
    SDL_QueryTexture(texturefont1, NULL, NULL, &w, &h);
    SDL_FreeSurface(surfacefont1);

    // activate active label
    surfacefont0 = TTF_RenderText_Solid(font0, "Start", colorOn);
    texturefont0 = SDL_CreateTextureFromSurface(rend, surfacefont0);
    SDL_QueryTexture(texturefont0, NULL, NULL, &w, &h);
    SDL_FreeSurface(surfacefont0);
    break;

  // QUIT
  case 1:
    // reset non-active label
    surfacefont0 = TTF_RenderText_Solid(font0, "Start", colorOff);
    texturefont0 = SDL_CreateTextureFromSurface(rend, surfacefont0);
    SDL_QueryTexture(texturefont0, NULL, NULL, &w, &h);
    SDL_FreeSurface(surfacefont0);

    // activate active label
    surfacefont1 = TTF_RenderText_Solid(font1, "Quit", colorOn);
    texturefont1 = SDL_CreateTextureFromSurface(rend, surfacefont1);
    SDL_QueryTexture(texturefont1, NULL, NULL, &w, &h);
    SDL_FreeSurface(surfacefont1);
    break;
  }
}

bool menuExecute()
{
  // this is being called when pressing  enter
  switch (menuLocation)
  {
  // START
  case 0:
    return true;
    break;

  // QUIT
  case 1:
    return false;
    break;

  default:
    return true;
    break;
  }
}

// TODO: use typedefs or commit suicide god dammit
// I am too stupid for typedefs so I'll just use global variables || please dont kill me

void stagesPrepare()
{
  // clear stuff from menu
  SDL_DestroyTexture(texturefont0);
  SDL_DestroyTexture(texturefont1);
  SDL_DestroyTexture(bgTexture);

  // load background
  SDL_Surface *surfaceStages = IMG_Load("src/img/bgFilled.png");

  bgStages = SDL_CreateTextureFromSurface(rend, surfaceStages);

  // SDL_FreeSurface(surfaceStages); This is being used for other stages as well

  //------------------Text Stuff---------------------------------
  fontHighScore = TTF_OpenFont("src/ttf/mononoki-Regular.ttf", 20);
  fontScore = TTF_OpenFont("src/ttf/mononoki-Regular.ttf", 20);

  SDL_Surface *surfaceHighScore = TTF_RenderText_Solid(fontHighScore, "Top Score", colorOff);
  SDL_Surface *surfaceScore = TTF_RenderText_Solid(fontHighScore, "Score", colorOff);

  textureHighScore = SDL_CreateTextureFromSurface(rend, surfaceHighScore);
  textureScore = SDL_CreateTextureFromSurface(rend, surfaceScore);

  SDL_QueryTexture(textureHighScore, NULL, NULL, &w, &h);
  SDL_QueryTexture(textureScore, NULL, NULL, &w, &h);

  SDL_FreeSurface(surfaceHighScore);
  SDL_FreeSurface(surfaceScore);

  //--------------Player-------------------
  //  surfacePlayer[0 - 7] reimua-h IDLE
  //  surfacePlayer[8 - 16] reimui-p LEFT
  //  surfacePlayer[17 - 23] reimuq-x RIGHT
  //  self-explanatory, I know

  SDL_Surface *surfacePlayer[24];

  for (int i = 0; i < 24; i++)
  {
    // replace character at line 13
    file[13] = i + 'a'; // 97 == a in ASCII then increment --> 98 == b in ASCII

    surfacePlayer[i] = IMG_Load(file);
    player[i] = SDL_CreateTextureFromSurface(rend, surfacePlayer[i]);

    SDL_FreeSurface(surfacePlayer[i]);

    if (!player[i])
    {
      SDL_Log("loading player models failed: %s\n", SDL_GetError());
    }
  }
}

void callThread()
{
  threadAnimation = SDL_CreateThread(animationPlayer, "animation thread", (void*)NULL);

  if(!threadAnimation)
  {
    SDL_Log("creating thread failed: %s\n", SDL_GetError());
  }
}

void stageOnePrepare()
{
  SDL_Surface *surfaceStageOne = IMG_Load("src/img/bgStageOne.png");
  bgStageOne = SDL_CreateTextureFromSurface(rend, surfaceStageOne);
  SDL_FreeSurface(surfaceStageOne);
}

void movementPlayer()
{
  // this fixed the ,,start-stop'' issue by getting a snapshot of the current keyboard ; refer to the SDL2 Documentation
  keys = SDL_GetKeyboardState(NULL);

  if (keys[SDL_SCANCODE_LSHIFT] == 1)
  {
    speed = 4;
  }
  else
  {
    speed = 8;
  }

  if (keys[SDL_SCANCODE_UP] == 1)
  {
    up = true;
    rectPlayer.y -= speed;
  }
  else
  {
    up = false;
  }

  if (keys[SDL_SCANCODE_DOWN] == 1)
  {
    down = true;
    rectPlayer.y += speed;
  }
  else
  {
    down = false;
  }

  if (keys[SDL_SCANCODE_LEFT] == 1)
  {
    left = true;
    rectPlayer.x -= speed;
  }
  else
  {
    left = false;
  }

  if (keys[SDL_SCANCODE_RIGHT] == 1)
  {
    right = true;
    rectPlayer.x += speed;
  }
  else
  {
    right = false;
  }

  if((keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT]) != 1)
  {
    idle = true;
  }
  else
  {
    idle = false;
  }
}

void animate(int i)
{
  SDL_Delay(5);
  SDL_RenderCopy(rend, player[i], NULL, &rectPlayer);
}

int animationPlayer(void *ptr)
{
  ptr = &w; // get some random address, so that the compiler shuts up
  SDL_Log("thread number: %p", ptr);

  if (idle || down || up)
  {
    SDL_Log("1\n");
    for (int i = 0; i <= 7; i++)
    {
      animate(i);
    }
  }
  else if (left)
  {
    SDL_Log("2\n");
    for (int i = 8; i <= 17; i++)
    {
      animate(i);
    }
  }
  else if (right)
  {
    SDL_Log("3\n");
    for (int i = 18; i <= 23; i++)
    {
      animate(i);
    }
  }
  return 1; // fuer die Katz!!
}

void errorSolution()
{
  //SDL_WaitThread(threadAnimation, NULL);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);

  //-------------MENU STUFF---------------
  TTF_CloseFont(font0);
  TTF_CloseFont(font1);

  SDL_DestroyTexture(texturefont0);
  SDL_DestroyTexture(texturefont1);
  SDL_DestroyTexture(bgTexture);

  //-------------GENERAL STUFF---------------
  for (int i = 0; i < 24; i++)
  {
    SDL_DestroyTexture(player[i]);
    player[i] = NULL;
  }
  SDL_DestroyTexture(bgStages);
  TTF_CloseFont(fontHighScore);
  TTF_CloseFont(fontScore);
  //-------------STAGE 1 STUFF---------------
  SDL_DestroyTexture(bgStageOne);
  SDL_DestroyTexture(textureHighScore);
  SDL_DestroyTexture(textureScore);

  win = NULL;
  rend = NULL;
  font0 = NULL;
  font1 = NULL;
  texturefont0 = NULL;
  texturefont1 = NULL;
  textureHighScore = NULL;
  textureScore = NULL;
  bgTexture = NULL;
  bgStages = NULL;

  Mix_CloseAudio();
  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}