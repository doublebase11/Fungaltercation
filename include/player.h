#pragma once
#include "drawplayers.h"
#include "swordcollisions.h"
#include "specialmoves.h"
#include "elbow.h"
#include "stage.h"
#include "sfx.h"
#include "effects.h"

int checkdead(int health);

void dead(player &player1, player &player2);

void calculatePlayerCentre(player &player);

void hitstun(player &player1);

void move(player &player1, player &player2, int frame, stage stage); // don't look inside

void UpdatePlayers(player &player1, player &player2, stage stage, vector2i mouse, vector2i mouse2, int frame, SDL_Renderer* renderer, viewport &viewport, std::ofstream &log);
