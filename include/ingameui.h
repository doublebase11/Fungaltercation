#pragma once
#include "gamestructs.h"
#include "gfx.h"

void drawDashTimers(player &player1, player &player2, viewport v, SDL_Renderer* renderer);

void drawHealthBars(player &player1, player &player2, SDL_Texture* dot, SDL_Texture* healthbar, SDL_Renderer* renderer);

void drawspecialmovecooldowntimers(player &player1, player &player2, SDL_Texture* greendot, SDL_Texture* reddot, SDL_Texture* blackdot, SDL_Texture* hollowspecialmovebar, stage s, SDL_Renderer* renderer);