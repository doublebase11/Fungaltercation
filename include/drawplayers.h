#pragma once
#include "gamestructs.h"
#include "elbow.h"



void FlipPlayer(player &player);

void drawPlayerArm(player &player, SDL_Renderer* renderer, viewport &viewport);

void DrawPlayer(player &player, SDL_Renderer* renderer, viewport &viewport);

void drawplayers(player player1, player player2, SDL_Renderer* renderer, viewport &viewport);