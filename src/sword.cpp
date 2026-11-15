#include "sword.h"
#include <iostream>
#include <cmath>

vector2f2 calculateswordendpoints(player player) //fix function later
{
    vector2f2 topbottom;

    vector2f unrotatedtop = {0, 100};
    vector2f unrotatedbottom = {0, 0};
    double angler = player.swordrotation * PI; 
    angler = angler/180; //angle in radians. sdl uses degrees butcmath sin cosin etc functions use radians

    topbottom.v1 = {(cos(angler) *  unrotatedtop.x -sin(angler) * unrotatedtop.y), (sin(angler) * unrotatedtop.x + cos(angler)* unrotatedtop.y)};
    topbottom.v2 = unrotatedbottom;

    topbottom.v1.x = -(int)topbottom.v1.x;
    topbottom.v1.y = (int)topbottom.v1.y;
    topbottom.v2.x = (int)topbottom.v2.x;
    topbottom.v2.y = (int)topbottom.v2.y;

    return topbottom;
}

vector2f calculateswordtippos(vector2f tiphitboxv2, vector2f tiphitboxpos, vector2i handle, vector2f relativetiphitboxpos, double swordrotation)
{

    vector2f swordtippos = {0, 0};

    swordtippos = calculatevertex(tiphitboxv2, vector2f{(float)(handle.x - relativetiphitboxpos.x), (float)(handle.y - relativetiphitboxpos.y)}, swordrotation);
    swordtippos.x += tiphitboxpos.x;
    swordtippos.y += tiphitboxpos.y;


    return swordtippos;
}

vector2f calculateswordhiltpos(vector2f bladehitboxv3, vector2f bladehitboxpos, vector2i handle, vector2f relativebladehitboxpos, double swordrotation)
{
    vector2f swordtippos = {0, 0};

    swordtippos = calculatevertex(vector2f{bladehitboxv3.x/2,bladehitboxv3.y}, vector2f{(float)(handle.x - relativebladehitboxpos.x), (float)(handle.y - relativebladehitboxpos.y)}, swordrotation);
    swordtippos.x += bladehitboxpos.x;
    swordtippos.y += bladehitboxpos.y;

    return swordtippos;
}

vector2f calculatehandtippos(vector2f tiphitboxv2, vector2f tiphitboxpos, vector2i handle, vector2f relativetiphitboxpos, vector2i swordsize, double swordrotation)
{

    vector2f swordtippos = {0, 0};

    swordtippos = calculatevertex(vector2f{tiphitboxv2.x, tiphitboxv2.y+ 0.93*swordsize.y}, vector2f{(float)(handle.x - relativetiphitboxpos.x), (float)(handle.y - relativetiphitboxpos.y)}, swordrotation);
    swordtippos.x += tiphitboxpos.x;
    swordtippos.y += tiphitboxpos.y;


    return swordtippos;
}

axis findknockbackdirection(player player)
{
    axis knockbackdirection;
    vector2f2 swordendpoints = calculateswordendpoints(player);

    knockbackdirection = perpendicular(gradient(swordendpoints.v1, swordendpoints.v2));

    return knockbackdirection;
}

int findknockbackdistance(player player)
{

    int kbd = player.swordrelativeposchange * 2 * player.sword.weight/4;
    if(kbd < 0)
    {
        kbd = kbd * -1;
    }

    if(player.attacking != 3)
    {
        kbd = 0;
    }

    if(kbd == 0)
    {
        //kbd += 1;
    }
    else
    {
        //kbd += 9;
        double rotationchange = abs(FindRotationChange(player.swordprevrotation, player.initialattackangle));
        double possiblekbd = (rotationchange/140)*20;
        if(rotationchange < 112)
        {
            possiblekbd = (rotationchange/100)*4 * player.sword.weight;
            if(possiblekbd > 20)
            {
                possiblekbd = 18;
            }
        }
        if(possiblekbd > 20)
        {
            possiblekbd = 20;
        }
        //if((rotationchange > 60) && (possiblekbd < 12))
        //{
        //    possiblekbd = 12;
        //}
        kbd = possiblekbd;
        if(player.hit160 == 1)
        {
            kbd = 20 + (rotationchange/120)*player.sword.weight;
        }
    if(kbd > player.sword.maxdamage)
    {
        kbd = player.sword.maxdamage;
    }

    if(kbd < 9)
    {
        kbd = 9;
    }        
    }



    ////log << << kbd << " power " << player.swordrelativeposchange << "swordrelativeposchange" << std::endl;
    return kbd;
}

vector2i FindCursorpos(vector2i mouse, vector2i &attackcentre, vector2i playercentre, int attackradius) //calculates where the cursor should be?
{
    // if mouse outside attacking circle, move attacking circle
    if(((mouse.x - attackcentre.x) * (mouse.x - attackcentre.x) + (mouse.y - attackcentre.y) * (mouse.y - attackcentre.y)) > (attackradius*attackradius))
    {

       vector2f intercept = PointCircleIntercept(vector2i{mouse.x, mouse.y}, attackcentre, attackradius); 
       attackcentre.x = attackcentre.x +(mouse.x - intercept.x);
       attackcentre.y = attackcentre.y +(mouse.y - intercept.y);

    }
    
    return PointCentreTranslationVector(mouse, attackcentre, playercentre);
    
}

double FindSwordRotationChange(player player)
{
    double rotationchange = 0;

    rotationchange = FindRotationChange(player.cursorrotation, player.swordprevrotation);

    return rotationchange;

}

double FindSwordRotation(vector2i playercentre, vector2i swordpos) //finds the bearing from the player to the sword. This is written horribly but it works
{
    
    
    int centrex = playercentre.x;
    int centrey = playercentre.y;

    double a = swordpos.x - centrex; //a and b are the coordinates of the sword when the player has been translated to (0, 0) (this makes it easier to work out the angle of the sword- look at the picture
    double b = -(swordpos.y - centrey);


    double angle = 5; //bearing of the sword. look at the picture

    if((a == 0 && b == 0))
    {
        angle = 90;
    }
    if((a == 0 && b > 0))
    {
        angle = 0;
    }
    else if(a == 0 && b < 0)
    {
        angle = 180;
    }
    else if(a > 0 && b == 0)
    {
        angle = 90;
    }
    else if(a < 0 && b == 0)
    {
        angle = 270;
        
    } 
    else if(a < 0 && b < 0)
    {
        double c = (a/b);
        ////log << << c << " c" << std::endl;
        angle = atan(c); //inverse tan IN RADIANSnnenfoineon
        angle = (angle*180)/PI;
        angle = angle + 180;
    }   
    else if(a < 0)
    {
        double c = ((-a)/b);
        angle = atan(c);
        angle = (angle*180)/PI;
        angle = 270 - (angle - 90);
        ////log << << a << "njndjn" << b << std::endl;
    }
    else if(b < 0)
    {
        double c = -(a/b);
        angle = (atan(c));
        angle = (angle*180)/PI;
        angle = 180 - angle;
       // //log << << a << " dddd" << b << std::endl;
    }
    else
    {
        double c = (a/b);
        ////log << << c << " c" << std::endl;
        angle = atan(c);
        angle = (angle*180)/PI;
        ////log << << a << " " << b << std::endl;
    }

    return (angle);  
}

double FindSwordRotation(vector2f playercentre, vector2f swordpos) //finds the bearing from the player to the sword. This is written horribly but it works
{
    
    
    int centrex = playercentre.x;
    int centrey = playercentre.y;

    double a = swordpos.x - centrex; //a and b are the coordinates of the sword when the player has been translated to (0, 0) (this makes it easier to work out the angle of the sword- look at the picture
    double b = -(swordpos.y - centrey);


    double angle = 5; //bearing of the sword. look at the picture

    if((a == 0 && b == 0))
    {
        angle = 90;
    }
    if((a == 0 && b > 0))
    {
        angle = 0;
    }
    else if(a == 0 && b < 0)
    {
        angle = 180;
    }
    else if(a > 0 && b == 0)
    {
        angle = 90;
    }
    else if(a < 0 && b == 0)
    {
        angle = 270;
        
    } 
    else if(a < 0 && b < 0)
    {
        double c = (a/b);
        ////log << << c << " c" << std::endl;
        angle = atan(c); //inverse tan IN RADIANSnnenfoineon
        angle = (angle*180)/PI;
        angle = angle + 180;
    }   
    else if(a < 0)
    {
        double c = ((-a)/b);
        angle = atan(c);
        angle = (angle*180)/PI;
        angle = 270 - (angle - 90);
        ////log << << a << "njndjn" << b << std::endl;
    }
    else if(b < 0)
    {
        double c = -(a/b);
        angle = (atan(c));
        angle = (angle*180)/PI;
        angle = 180 - angle;
       // //log << << a << " dddd" << b << std::endl;
    }
    else
    {
        double c = (a/b);
        ////log << << c << " c" << std::endl;
        angle = atan(c);
        angle = (angle*180)/PI;
        ////log << << a << " " << b << std::endl;
    }

    return (angle);  
}

vector2f FindSwordpos(player &player, vector2i mouse) //HOOOOOOOOOO BOOOOOOOOOOOOOOOOOY
{

    //ARRRRRRRRRRRRRRRRRUJGUOHUORHAR

    //dont question anything past this point

    vector2f swordpos = {(float)player.cursor.x, (float)player.cursor.y};

    if(player.sword.sword == 2)
    {
        if(abs(FindSwordRotationChange(player)) > 3)
        {
            player.sword.speed += 0.00011 * 1.7;
        }
        else
        {
            player.sword.speed -= 0.00011 * 1.5;
        }
    

        if(player.sword.speed > 0.09)
        {
            player.sword.speed = 0.09;
        }
        else if(player.sword.speed < 0.075)
        {
            player.sword.speed = 0.075;
        }
    }
    
    if(player.swordon == 1)
    {

        if(player.attacking == 0)
        {
            if((player.GetTicks - player.timehit) > player.timebetweenhits)
            {
                if(abs(FindSwordRotationChange(player)) > 5)
                {
                    player.attacking = 1;
                }
            }
        }

     
        if(player.attacking == 4)
        {
            player.timehit = player.GetTicks;
            player.attacking = 0;
        }

        if(player.attacking == 1)
        {       
            //1 means youve just pressed left click
            player.attackstart = player.swordpos;
            player.attacking = 2;
        }
        if(player.attacking == 2)
        {

            //2 means the player is starting to attack
            if(FindSwordRotationChange(player) != 0)
            {

                player.attackstarttime = player.GetTicks;
                player.hit160 = 0;
                player.hit80  = 0;
                player.attacking = 3;
                player.swordmomentum = 0;
                player.initialattackangle = player.swordrotation;
            }
        }   
        if(player.attacking == 3)
        {
            //3 means the player is attacking
            player.attackduration = player.GetTicks - player.attackstarttime; 
            {


                ////log << << FindRotationChange(player.swordprevrotation, player.initialattackangle) << std::endl;

                //player.attackcentre.y -= player.sword.weight/8; //MAKES THE SWORD FALL IE GRAVITY/WEIGHT


                if(player.hit160 == 0)
                {
                    if(abs(FindRotationChange(player.swordprevrotation, player.initialattackangle)) >  140)
                    {
                        player.hit160 = 1;
                        player.initialattackangle = player.swordrotation;
                    }
                }
                if(player.hit160 == 1)
                {
                    if(abs(FindRotationChange(player.swordprevrotation, player.initialattackangle)) >  140)
                    {
                        //limit = 0;
                    }
                }



                if((abs(FindSwordRotationChange(player)) < 3) || (player.inhitstun == 1) || (player.parried == 1))
                {
                    player.attacking = -1;
                }
            }

        }
        if(player.attacking == -1)
        {

            player.attacking = 0;

        }
    }
    else
    {
        player.attacking = 0;
    }
    
    return swordpos;
    
}



void movesword(player &player) //corrects the sword pos if attacking
{
    if(player.swordpos.x != player.cursor.x || player.swordpos.y != player.cursor.y)
    {
        //player.swordpos.x = player.swordpos.x + player.velocity.x;
        player.swordpos.y += player.ychange;

        player.swordpos.x += player.xchange;

    }
}

void DrawSword(player &player1, SDL_Renderer* renderer, viewport &viewport)
{
    if(player1.swordon == 1 && player1.dead == 0)
    {
        drawPngEx(renderer, player1.sword.texture1, viewport, 0, 0, player1.sword.size.x, player1.sword.size.y, (player1.swordpos.x), (player1.sworddrawpos.y - player1.sword.size.y), player1.sword.handle.x, player1.sword.handle.y, player1.swordrotation, SDL_FLIP_NONE); //draws the sword. for now
        //if(player1.swordro)
       //drawPngEx(renderer, player1.sword.texture1, viewport, 0, 0, player1.sword.size.x, player1.sword.size.y, (player1.swordpos.x), (player1.swordprevpos.y - player1.idleanimation.size.y - player1.sword.size.y), player1.sword.handle.x, player1.sword.handle.y, player1.swordprevrotation, SDL_FLIP_NONE);
    }
}
