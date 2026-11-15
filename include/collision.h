#pragma once
#include "maths.h"
#include <cmath>
#include "gamestructs.h"
#include "hitbox.h"

axis gradient(vector2f p1, vector2f p2);

axis perpendicular(axis oaxis);

vector2f2 findMostDistantPoints(vector2f a, vector2f b, vector2f c, vector2f d, axis paxis);

vector2f findoverlapdistance(vector2f2 fls1, vector2f2 fls2, axis paxis);

int checkOverlap(vector2f2 fls1, vector2f2 fls2, axis paxis);

vector2f projectPoint(axis paxis, vector2f point);//axis is the gradient of the line to project the point onto, point is the point to project

int collision(hitbox h1, hitbox h2);

