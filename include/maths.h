#pragma once
#include <cmath>
#include <iostream>

struct vector2i 
{
    int x, y;
};

struct vector2f 
{
    double x, y;
};

vector2i PointCentreTranslationVector(vector2i mouse, vector2i attackCentre, vector2i playerCentre);
//works out where the sword? should go given the mouse pos. Someone make a better name

vector2f PointCircleIntercept(vector2i point, vector2i circleCentre, int radius); //Finds the intersecting points between a line and a circle 
// using the coordinates of a point, the centre of the circle and the radius. 
// Don't ask how this works shoutout to this guy https://cp-algorithms.com/geometry/circle-line-intersection.html.
//  m and n are the cooordinates of the point, o and p the centre of the circle, r the radius

double midpointofangles(double bearingA, double bearingB);

vector2f polartocartesian(float modulus, float arg);

double FindRotationChange(double angle, double prevangle);

double CalculateHypotenuse(vector2i lengths);

double lerp(int start, int end, float percent);



