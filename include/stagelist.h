#pragma once
#include "gamestructs.h"
#include "gfx.h"

void createstages(stage &grass, stage &sewer, SDL_Renderer * renderer);

void assignsoundeffectstoplayers(stage s, player &player1, player &player2);

void assignparticlestoplayers(stage s, player &player1, player &player2);