#pragma once
#include "gamestructs.h"
#include "sword.h"

vector2f findElbowpos(vector2f playercentre, vector2f swordpos, float armlength, int flip);

void findElbowposAndAngles(player &player1);