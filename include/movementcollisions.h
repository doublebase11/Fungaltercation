#pragma once
#include "collision.h"
#include "hitbox.h"


void calculatePlayerHitboxLocations(player &player);

void broadPlayerCollisions(player &player1, player &player2);

void bodyCollisionVelocities(player &player1, player &player2);

void bodyCollisions(player &player1, player &player2);

void capCollisions(player &player1, player &player2);

vector2i stageCollisions(stage &s, player &player);