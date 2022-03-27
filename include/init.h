#ifndef __INIT_H_
#define __INIT_H_

#include "incs.h"

extern SDL_Window *win;
extern SDL_Renderer *rend;

//-------------MENU STUFF---------------
extern SDL_Texture *bgTexture;
extern SDL_Rect rectfont0;
extern SDL_Rect rectfont1;
extern TTF_Font *font0;
extern SDL_Texture *texturefont0;

extern TTF_Font *font1;
extern SDL_Texture *texturefont1;

//--------------GENERAL STUFF--------------
extern SDL_Texture *bgStages;
extern SDL_Rect rectStageArea;

extern TTF_Font *fontHighScore;
extern TTF_Font *fontScore;
extern SDL_Texture *textureHighScore;
extern SDL_Texture *textureScore;

extern SDL_Rect rectHighScore;
extern SDL_Rect rectScore;

extern SDL_Texture *player;
extern SDL_Rect rectDestPlayer;
extern SDL_Rect rectSrcPlayer;

extern SDL_Texture *bullet[5];
extern SDL_Rect rectBullet[5];

extern SDL_Texture *textureHitBox;
extern SDL_Rect rectHitBox;

extern bool up, down, left, right, idle;
extern bool animate;
//-------------STAGE 1 STUFF---------------
extern SDL_Texture *bgStageOne;

// so that main knows how to call the function
void initWindow();
void initMenu();
void menuHover(int menu);
bool menuExecute();
void bgLoad();
void stagesPrepare();
void callThread();
void stageOnePrepare();
void movementPlayer();
void shootBullets();
int animationBullet(void *ptr);
void drawBullets();
int animationPlayer(void *ptr);
void errorSolution();

#endif