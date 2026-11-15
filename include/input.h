#pragma once
//this whole thing will be eventually rewritten

#include "gamestructs.h"
#include <windows.h>
void setupmiceinput(HANDLE &m1, HANDLE &m2, RAWINPUTDEVICELIST *&pRawInputDeviceList);

void miceclicks(int m1leftdown, int m1rightdown, int m2leftdown,int m2rightdown, player &player1, player &player2);

//void HandlePauseInput(SDL_Event &event, player &player1, player &player2, vector2i &mouse, vector2i &mouse2, int &pausetime, int &totalpausetime, HANDLE &m1, HANDLE &m2, RAWINPUTDEVICELIST *&pRawInputDeviceList);

void miceinput(int &m1x, int &m1y, int &m1leftdown, int &m1rightdown, int &m2x, int &m2y, int &m2leftdown, int &m2rightdown, HANDLE m1, HANDLE m2, int gaming, player &player1, player &player2);

void HandleInput(SDL_Event &event, int &quit, int &gaming, int &mousedown, vector2i &mouse, vector2i &mouse2, vector2i &mouse2keyboarddirection, SDL_Joystick* gGameController, player &player1, player &player2, int &pausetime, int &totalpausetime, HANDLE &m1, HANDLE &m2, RAWINPUTDEVICELIST *&pRawInputDeviceList, viewport &viewport, SDL_Window * window);

void lockCursor(vector2i &mouse);
