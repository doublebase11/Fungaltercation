#pragma once
#include "movementcollisions.h"
#include "sword.h"
#include "sfx.h"

void calculateSwordHitboxLocations(player &player);

vector2f calculateswordplayercollisionpoint(player &player1, player &player2);

int swordCollisions(player &player1, player &player2, std::ofstream &log);

void resolveswordnotattackingcollision(player &player1, player &player2, vector2i mouse, int direction);

void swordnotattackingcollisions(player &player1, player &player2, vector2i mouse, std::ofstream &log);

void swordtogroundcollisions(player &player1, stage s, vector2i mouse);

int parry(player &player1, player &player2);

void resolveparry(player &player2);
