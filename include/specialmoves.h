#pragma once
#include "viewport.h"
#include "collision.h"
#include "gfx.h"
#include "sword.h"

void drawspores(player &player, SDL_Renderer* renderer, viewport &viewport);

void shootspores(player &player);

void sporecollisions(player &player1, player &player2);

void chargehit(player &player1, player &player2);

void chargecollisions(player &player1, player &player2);
