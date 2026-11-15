#pragma once
//#pragma balls
#include "characterlist.h"
#include "button.h"
#include "player.h"
#include "stagelist.h"
#include "windows.h"
#include "input.h"


void initialpausehandler(player &player1, player &player2, button &titlescreen, button &characterselect, button &settings);

int creditscreen(int &creditsscroll, int mousedown, SDL_Texture* creditscreentexture,  SDL_Renderer* renderer);

int titlescreen(button play, button credits, button quitbutton, int &creditsscroll,  vector2i mouse, int mousedown, SDL_Texture* titlescreentexture,  SDL_Renderer* renderer);

int pausemenu(button &titlescreen, button &characterselect, button &settings, vector2i mouse, int mousedown,  SDL_Renderer* renderer);

int characterselect(SDL_Texture* grey2, player &player1, player &player2, player &defaultplayer, player &defaultplayer2, sword sword1, sword sword2, sword sword3, sword sword4, stage &currentstage, stage stage1, stage stage2, vector2i mouse, vector2i mouse2, int mousedown, int mouse2down, button ccbutton, button playbutton, button larrowbutton, button rarrowbutton,  SDL_Renderer* renderer, viewport &v);

int settingsmenu(button ccbutton, vector2i mouse, int mousedown,  SDL_Renderer* renderer, HANDLE &m1, HANDLE &m2, RAWINPUTDEVICELIST *&pRawInputDeviceList);