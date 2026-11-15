#pragma once
#pragma balls
#include "gamestructs.h"
#include "player.h"
#include "particle.h"
#include "ingameui.h"
#include "stage.h"

int checkdeathscreen(player &player1, player &player2);

void showdeathscreen(int gameover, int &deathscreenx, SDL_Renderer* renderer, SDL_Texture* deathscreen);

void game(player &player1, player &player2, stage &stage, vector2i mouse, vector2i mouse2, SDL_Renderer* renderer, viewport &v, viewport &v2, viewport &v3, SDL_Texture* dot, SDL_Texture* reddot, SDL_Texture* greendot, SDL_Texture* hollowspecialmovebar, SDL_Texture* healthbar, int frame, std::ofstream &log);

