#pragma once
#include "gamestructs.h"
#include "gfx.h"

void drawStageLeafParticles(stage &s, int pause, int gameover,  SDL_Renderer* renderer, viewport &viewport);

void drawStageSporeParticles(stage &s, int pause, int gameover, SDL_Renderer* renderer, viewport &viewport);

void drawGroundParticles(stage s, player &player, SDL_Renderer* renderer, viewport &viewport);

void waterCollisions(stage s, player &player1, player &player2);

void drawStageWater(stage s, SDL_Renderer* renderer, viewport v);

void drawStageBackground(stage &s, int pause, int gameover,  SDL_Renderer* renderer, viewport v);

void drawStagePlatforms(stage s, SDL_Renderer* renderer, viewport v);

void drawStageGround(stage s, SDL_Renderer* renderer, viewport v);

void drawStageForeground(stage s, SDL_Renderer* renderer, viewport v);

void calculateplatformcentres(stage &s);

void initstage(stage &s, viewport &v);

