#pragma once

#include "gamestructs.h"
#include "collision.h"
#include "gfx.h"

vector2f2 calculateswordendpoints(player player);

vector2f calculateswordtippos(vector2f tiphitboxv2, vector2f tiphitboxpos, vector2i handle, vector2f relativetiphitboxpos, double swordrotation);

vector2f calculateswordhiltpos(vector2f bladehitboxv3, vector2f bladehitboxpos, vector2i handle, vector2f relativebladehitboxpos, double swordrotation);

vector2f calculatehandtippos(vector2f tiphitboxv2, vector2f tiphitboxpos, vector2i handle, vector2f relativetiphitboxpos, vector2i swordsize, double swordrotation);

axis findknockbackdirection(player player1);

int findknockbackdistance(player player);

vector2i FindCursorpos(vector2i mouse, vector2i &attackcentre, vector2i playercentre, int attackradius); //calculates where the cursor should be?

double FindSwordRotation(vector2i playercentre, vector2i swordpos); //finds the bearing from the player to the sword. This is written horribly but it works

double FindSwordRotation(vector2f playercentre, vector2f swordpos);

double FindSwordRotationChange(player player);

vector2f FindSwordpos(player &player, vector2i mouse); //HOOOOOOOOOO BOOOOOOOOOOOOOOOOOY

void movesword(player &player); //corrects the sword pos if attacking

void DrawSword(player &player1, SDL_Renderer* renderer, viewport &viewport);
