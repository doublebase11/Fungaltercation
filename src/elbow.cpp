#include "elbow.h"
#include "cmath"


vector2f findElbowpos(vector2f playercentre, vector2f swordpos, float armlength, int flip)
{
    //the code in here is based on these geogebra files https://www.geogebra.org/graphing/bryu5y37 and https://www.geogebra.org/calculator/sntehpjd by me
    //which took the code from this desmos file https://www.desmos.com/calculator/nmuftxapz6
    //from this https://youtu.be/wgpgNLEEpeY?si=71Uu7oa1hT4F68CH youtube video

    vector2f elbowpos = {0, 0};
    vector2f handpos = swordpos;

    double distancefromhandtocentre = sqrt(handpos.x*handpos.x + handpos.y*handpos.y);
    if(distancefromhandtocentre >= armlength)
    {
        elbowpos.x = 0.5*swordpos.x;
        elbowpos.y = 0.5*swordpos.y;
    }
    else
    {
        double halfarmlength = armlength/2;
        double handarg = 0;
        double elbowangle = acos(distancefromhandtocentre/armlength);
        ////log << << elbowangle << std::endl;
        vector2f unrotatedelbow = {cos(elbowangle)*halfarmlength, -sin(elbowangle)*halfarmlength};

        if(flip == SDL_FLIP_HORIZONTAL)
        {
            unrotatedelbow.y = sin(elbowangle)*halfarmlength;
        }

        ////log << << unrotatedelbow.x << " " << unrotatedelbow.y << std::endl;

        if(handpos.x >= 0)
        {
            handarg = atan(handpos.y/handpos.x);
        }
        else
        {
            handarg = PI - atan(handpos.y/-handpos.x);
        }
        double cosf = cos(handarg);
        double sinf = sin(handarg);
        elbowpos = {cosf*unrotatedelbow.x - sinf*unrotatedelbow.y, sinf*unrotatedelbow.x + cosf*unrotatedelbow.y};
    }



    return elbowpos;

}

void findElbowposAndAngles(player &player1)
{
    
    
    vector2f swordhilt = calculateswordhiltpos({player1.sword.bladehitbox.v3.x, player1.sword.size.y-8}, {player1.sword.bladehitboxpos.x, player1.sword.bladehitboxpos.y - player1.sword.relativebladehitboxpos.y}, player1.sword.handle, {player1.sword.relativebladehitboxpos.x, 0}, player1.swordrotation);
    
    if(player1.flip == SDL_FLIP_HORIZONTAL)
    {
        swordhilt = calculateswordhiltpos({player1.sword.bladehitbox.v3.x + 10, (double)player1.sword.size.y-8}, {player1.sword.bladehitboxpos.x, player1.sword.bladehitboxpos.y - player1.sword.relativebladehitboxpos.y}, player1.sword.handle, {player1.sword.relativebladehitboxpos.x, 0}, player1.swordrotation);
    }
    double player1centrey = (int)(player1.drawpos.y + (player1.idleanimation.size.y/2.0));
    double player1centrex = (int)(player1.pos.x + (player1.idleanimation.size.x/2.0));
    vector2f handpos;
    ////translates the hand to move the shoulder to (0, 0)
    handpos.x = swordhilt.x - player1centrex;
    handpos.y = -(swordhilt.y - player1centrey); 
    ////
    ////log << << handpos.x << " " << handpos.y << std::endl;
    vector2f p1elbow = findElbowpos(vector2f{player1centrex, player1centrex}, handpos, player1.elbowlength*2, player1.flip);

    ////log << << p1elbow.x << " " << p1elbow.y << std::endl;
    
    p1elbow.x += player1.centre.x;
    p1elbow.y = player1centrey -p1elbow.y;
    handpos.x = swordhilt.x;
    handpos.y = swordhilt.y;
    player1.upperarmangle = FindSwordRotation(vector2f{player1centrex, player1centrey}, p1elbow);
    player1.forearmangle = FindSwordRotation(p1elbow, handpos);

    player1.elbowpos = p1elbow;
    
    //////log << << upperarmangle << " " << forearmangle << std::endl;
}