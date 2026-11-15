#include "maths.h"

vector2i PointCentreTranslationVector(vector2i mouse, vector2i attackCentre, vector2i playerCentre) 
//works out where the sword? should go given the mouse pos. Someone make a better name
{
    vector2i drawxy; //where the sword should be drawn(appproximately)

    drawxy.x = playerCentre.x + (mouse.x - attackCentre.x); //(mouseX - attackcentrex) is the distance from the cursor to the centre of the attacking circle. This distance is added to the centre of the player to give the x coordinate of the sword
    drawxy.y = playerCentre.y + (mouse.y - attackCentre.y); //same as the last line but for the y coordinate

    ////log << << (mouseX - attackcentrex) << " ";
    ////log << << (mouseY - attackcentrey) << std::endl;
    
    return drawxy;
}

vector2f PointCircleIntercept(vector2i point, vector2i circleCentre, int radius) //Finds the intersecting points between a line and a circle 
// using the coordinates of a point, the centre of the circle and the radius. 
// Don't ask how this works shoutout to this guy https://cp-algorithms.com/geometry/circle-line-intersection.html.
//  m and n are the cooordinates of the point, o and p the centre of the circle, r the radius
{
    vector2f intercepts;

    double ax, ay, bx, by; //ax ay is the first intercept. bx by is the second intercept

    if(((point.y-circleCentre.y) == 0) && ((point.x-circleCentre.x) != 0))
    {
        ax = radius + circleCentre.x;
        bx = -radius + circleCentre.x;
        ay = 0 + circleCentre.y;
        by = 0 + circleCentre.y;

    }
    else if(((point.y-circleCentre.y) != 0) && ((point.x-circleCentre.x) == 0))
    {
        ax = 0 + circleCentre.x;
        bx = 0 + circleCentre.x;
        ay = radius + circleCentre.y;
        by = -radius + circleCentre.y;
    }
    else //everything above is edge cases
    {  
        
        double  x1 = (point.x-circleCentre.x);
        double y1 = point.y-circleCentre.y;
        double a = y1; //ax + by + c = 0 - the line through the circle centre and point
        double b = -x1;
        double c = 0;

        //this is what the guy from competitive programming did so im as lost as you are. perhaps why its so buggy
        double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);    

        double d = radius*radius - c*c/(a*a+b*b);
        double mult = sqrt (d / (a*a+b*b));

        ax = x0 + b * mult + circleCentre.x;
        bx = x0 - b * mult + circleCentre.x;
        ay = y0 - a * mult + circleCentre.y;
        by = y0 + a * mult + circleCentre.y;

    }



    if((sqrt((bx - point.x)*(bx-point.x) + (by - point.y)*(by-point.y)) < sqrt((ax - point.x)*(ax-point.x) + (ay - point.y)*(ay-point.y))))
    {
        intercepts.x = (bx);
        intercepts.y = (by);
    }
    else
    {
        intercepts.x = (ax);
        intercepts.y = (ay);
    }

    // //log << << intercepts.x + " " + intercepts.y << std::endl;  
    return intercepts;

}

double midpointofangles(double bearingA, double bearingB) //shout out to this guy for writing this https://oldschooldotnet.blogspot.com/2011/04/calculating-average-of-two-angles-two.html
{
            if (bearingA > bearingB)
            {

                double temp = bearingA;
                bearingA = bearingB;

                bearingB = temp;
            }
 
            if (bearingB - bearingA > 180) bearingB -= 360;
 
            double finalBearing = (bearingB + bearingA)/2;
 
            if (finalBearing < 0) finalBearing += 360;
            
            return finalBearing;
}

vector2f polartocartesian(float modulus, float arg)
{
    float argr = arg*3.14159265;
    argr = argr/180;
    vector2f cartestiancoords = {modulus*cos(argr), modulus*sin(argr)};
    ////log << << cartestiancoords.
    return cartestiancoords;
}

double FindRotationChange(double angle, double prevangle)
{
    double rotationchange = 0;
    rotationchange = angle - prevangle;
    if(rotationchange < -180)
    {
        rotationchange += 360;
    }
    else if(rotationchange > 180)
    {
        rotationchange -= 360;
    }

    if(rotationchange != rotationchange) //solves the NAN problem
    {
        rotationchange = 0;
    }


    return rotationchange;
}

double CalculateHypotenuse(vector2i lengths)
{
    return sqrt((lengths.x*lengths.x) + (lengths.y*lengths.y));
}

double lerp(int start, int end, float percent)
{
    double lerpedvalue = (percent * (end-start)) + start;
    return lerpedvalue;
}