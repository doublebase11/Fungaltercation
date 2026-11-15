#pragma once
#include "gamestructs.h"
#include "gfx.h"
#include <cstdlib>

void drawWalkParticles(player &player, SDL_Renderer* renderer, viewport viewport);

void drawDashparticles(player &player, SDL_Renderer* renderer, viewport viewport);
