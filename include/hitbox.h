#pragma once
#include "gamestructs.h"

vector2f calculatevertex(vector2f tpoint, vector2f centre, float angle);

hitbox calculatevertices(hitbox hbox, vector2f pos, vector2f centre, float angle);
