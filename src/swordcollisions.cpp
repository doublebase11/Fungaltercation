#include "swordcollisions.h"

void calculateSwordHitboxLocations(player &player)
{
    player.sword.tiphitboxpos= {player.swordpos.x + player.sword.relativetiphitboxpos.x, player.sworddrawpos.y - player.sword.size.y+ player.sword.relativetiphitboxpos.y};
    player.sword.bladehitboxpos= {player.swordpos.x + player.sword.relativebladehitboxpos.x, player.sworddrawpos.y - player.sword.size.y+ player.sword.relativebladehitboxpos.y};
}

vector2f calculateswordplayercollisionpoint(player &player1, player &player2)
{
    vector2f swordtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, player1.swordrotation);
    vector2f swordhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, player1.swordrotation);
    axis knockbackdirection;
    vector2f2 swordendpoints = calculateswordendpoints(player1);
    knockbackdirection = gradient(swordendpoints.v1, swordendpoints.v2);
    knockbackdirection.g = -knockbackdirection.g;
    int player2centrex = (int)(player2.pos.x + (player2.idleanimation.size.x/2.0));
    int player2centrey = (int)(player2.drawpos.y + (player2.idleanimation.size.y/2.0));

    vector2f collisionpoint = { lerp(swordhilt.x, swordtip.x, 1), lerp(swordhilt.y, swordtip.y, 0.8)};
    float distx = player1.centre.x - player2.centre.x;
    float disty = player1.centre.y - player2.centre.y;
    float distance = sqrtf((distx*distx) + (disty*disty));
    float lvalue = 1;

    if((distance <= 40 + player1.sword.size.y*0.9))
    {
        lvalue = 0.9;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.9);
    }
    if((distance <= 40 + player1.sword.size.y*0.8))
    {
        lvalue = 0.8;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.8);
    }
    if((distance <= 40 + player1.sword.size.y*0.7))
    {
        lvalue = 0.7;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.7);
    }
    if((distance <= 40 + player1.sword.size.y*0.6))
    {
        lvalue = 0.6;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.6);
    }
    if((distance <= 40 + player1.sword.size.y*0.5))
    {
        lvalue = 0.5;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.5);
    }
    if((distance <= 40 + player1.sword.size.y*0.4))
    {
        lvalue = 0.4;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.4);
    }
    if((distance <= 40 + player1.sword.size.y*0.3))
    {
        lvalue = 0.3;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.3);
    }
    if((distance <= 40 + player1.sword.size.y*0.2))
    {
        lvalue = 0.2;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.2);
    }
    if((distance <= 40 + player1.sword.size.y*0.1))
    {
        lvalue = 0.1;
        collisionpoint.x = lerp(swordhilt.x, swordtip.x, 0.1);
    }

    if(player1.pos.x > player2.pos.x)
    {
        collisionpoint.x = lerp(swordtip.x, swordhilt.x, lvalue);
    }

    collisionpoint.x = lerp(collisionpoint.x, player2centrex, 0.2);
    collisionpoint.y = lerp(collisionpoint.y, player2centrey, 0.2);

    return collisionpoint;
}

int swordCollisions(player &player1, player &player2, std::ofstream &log)
{
    ////log << << (player1.swordpos.x > player1.centre.x) << std::endl;
    int hit = 0;
    if((player1.broadcollision == 1 ) && (player1.swordon == 1) && (player2.dead == 0))
    {
    if(player1.attacking == 3 && (findknockbackdistance(player1) > 0))
    {
        
        calculateSwordHitboxLocations(player1);

        int precisecollision = (collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))));
        
        double midswordangle = midpointofangles(player1.swordrotation, player1.swordprevrotation);

        vector2f swordtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, player1.swordrotation);
        vector2f swordhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, player1.swordrotation);
        vector2f swordprevtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, player1.swordprevrotation);
        vector2f swordprevhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, player1.swordprevrotation);
        vector2f swordmidtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, midswordangle);
        vector2f swordmidhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, midswordangle);
        hitbox h1 ={swordprevtip, swordprevhilt, swordmidhilt, swordmidtip};
        hitbox h2 = {swordtip, swordhilt, swordmidhilt, swordmidtip};
        int vaguercollision =  collision(h1, calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(h2, calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(h1, calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || collision(h2, calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || collision(h1, calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0)) || collision(h2, calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0)); 

        if(midswordangle == 0)
        {
            vaguercollision = 0;
            
        }

        if(abs(FindSwordRotationChange(player1)) < 10)
        {
            vaguercollision = 0;
        }
        
        if(precisecollision || vaguercollision)
        {   

            
            
            

            if(player2.stunned == 1)
            {
                player2.stunned = 0;
                player1.sporecollision = 1;
            }
            hit = 1;

            //code below this sends the other player
            //log << "" << std::endl;
            int iteration = 1;
            axis kbd = findknockbackdirection(player1);
            int m = findknockbackdistance(player1); //knockback distance
            m = m*(6.5/player2.mass);
            
            player2.health -= m;
            if(player2.health < 0)
            {
                player2.health = 0;
            }
            //log << "player " << player2.player << " health: " << player2.health << std::endl;
            //hitstun
            
            player2.hitstuntimer = player1.GetTicks;
            player2.timetospendinhitstun = (m*90/player2.mass);
            //log << << player2.timetospendinhitstun << std::endl;
            if(player2.inhitstun)
            {
                //log << << "trueeeeeeeeeeeeeeeeeeeeeee" << std::endl;
            }
            
            //
            float disttomove = sqrt((1)/(kbd.g*kbd.g + 1)); 


            ////log << << kbd.g << " " << disttomove <<  std::endl;
            int rotationchange = FindSwordRotationChange(player1);
        
            //SWORD TO THE RIGHT OF THE PLAYER
            if((player1.swordpos.x > player1.centre.x))
            {  
                if(rotationchange < 0)
                {
                    if(kbd.horv == -1)
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                        {
                            //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                            player2.pos.y -= disttomove;
                            player2.drawpos.y -= disttomove;
                            calculatePlayerHitboxLocations(player2);
                            iteration++;

                        }
                        player2.velocity.y = sqrt((m*m)/(kbd.g*kbd.g + 1));
                    }
                    else
                    {
                        if(kbd.g > 0)
                        {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x += disttomove;
                                player2.pos.y -= kbd.g * disttomove;
                                player2.drawpos.y -= kbd.g * disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;

                            }
                            player2.velocity.x = sqrt((m*m)/(kbd.g*kbd.g + 1));
                            player2.velocity.y = kbd.g * player2.velocity.x ;
                        }
                        else if(kbd.g < 0)
                        {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x -= disttomove;
                                player2.pos.y -= kbd.g * disttomove;
                                player2.drawpos.y -= kbd.g * disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;

                            }
                            player2.velocity.x = -sqrt((m*m)/(kbd.g*kbd.g + 1));
                            player2.velocity.y = kbd.g * player2.velocity.x ;                       
                        }
                    }
                }
                else if(rotationchange > 0)
                {
                    if(kbd.horv == -1)
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                        {
                            //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                            player2.pos.y += disttomove;
                            player2.drawpos.y += disttomove;
                            calculatePlayerHitboxLocations(player2);
                            iteration++;

                        }
                        player2.velocity.y = -sqrt((m*m)/(kbd.g*kbd.g + 1));
                    }
                    else
                    {
                    if(kbd.g > 0)
                        {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x -= disttomove;
                                player2.pos.y -= -kbd.g * disttomove;
                                player2.drawpos.y -= -kbd.g * disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;
    
                            }
                            player2.velocity.x = -sqrt((m*m)/(kbd.g*kbd.g + 1));
                            player2.velocity.y = kbd.g * player2.velocity.x ;
                        }
                        else if(kbd.g < 0)
                        {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x += disttomove;
                                player2.pos.y -= kbd.g * disttomove;
                                player2.drawpos.y -= kbd.g * disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;
    
                            }
                            player2.velocity.x = sqrt((m*m)/(kbd.g*kbd.g + 1));
                            player2.velocity.y = kbd.g * player2.velocity.x ;                       
                        }
                    }
                }
            }
            else if(player1.swordpos.x < player1.centre.x) //SWORD TO THE LEFT OF THE PLAYER
            {   
                if(rotationchange < 0)
                {
                    if(kbd.horv == -1)
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                        {
                            //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                            player2.pos.y -= disttomove;
                            player2.drawpos.y -= disttomove;
                            calculatePlayerHitboxLocations(player2);
                            iteration++;

                        }
                        player2.velocity.y = sqrt((m*m)/(kbd.g*kbd.g + 1));
                    }
                    else
                    {
                        if(kbd.g > 0)
                        {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x -= disttomove;
                                player2.pos.y += kbd.g * disttomove;
                                player2.drawpos.y += kbd.g * disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;

                            }
                            player2.velocity.x = -sqrt((m*m)/(kbd.g*kbd.g + 1));
                            player2.velocity.y = kbd.g * player2.velocity.x ;
                        }
                        else if(kbd.g < 0)
                        {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x += disttomove;
                                player2.pos.y += kbd.g * disttomove;
                                player2.drawpos.y += kbd.g * disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;

                            }
                            player2.velocity.x = sqrt((m*m)/(kbd.g*kbd.g + 1));
                            player2.velocity.y = kbd.g * player2.velocity.x ;                       
                        }
                    }
                }
                else if(rotationchange > 0)
                {
                    if(kbd.horv == -1)
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                        {
                            //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                            player2.pos.y += disttomove;
                            player2.drawpos.y += disttomove;
                            calculatePlayerHitboxLocations(player2);
                            iteration++;

                        }
                        player2.velocity.y = -sqrt((m*m)/(kbd.g*kbd.g + 1));
                    }
                    else
                    {
                    if(kbd.g > 0)
                        {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x += disttomove;
                                player2.pos.y += -kbd.g * disttomove;
                                player2.drawpos.y -= kbd.g * disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;
    
                            }
                            player2.velocity.x = sqrt((m*m)/(kbd.g*kbd.g + 1));
                            player2.velocity.y = kbd.g * player2.velocity.x ;
                        }
                        else if(kbd.g < 0)
                        {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x -= disttomove;
                                player2.pos.y += kbd.g * disttomove;
                                player2.drawpos.y += kbd.g * disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;
    
                            }
                            player2.velocity.x = -sqrt((m*m)/(kbd.g*kbd.g + 1));
                            player2.velocity.y = kbd.g * player2.velocity.x ;                       
                        }
                    }
                }
            }
            else
            {
                if(player1.pos.y < player2.pos.y)
                {
                    if(rotationchange < 0)
                    {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x += disttomove;
                                player2.drawpos.x += disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;

                            }
                            player2.velocity.x = sqrt((m*m)/(kbd.g*kbd.g + 1));                   
                    }
                    else if(rotationchange > 0)
                    {
                    if(rotationchange > 0)
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                        {
                            //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                            player2.pos.x -= disttomove;
                            player2.drawpos.x -= disttomove;
                            calculatePlayerHitboxLocations(player2);
                            iteration++;
                        }
                        player2.velocity.x = -sqrt((m*m)/(kbd.g*kbd.g + 1)); 
                    }
                    }
                }
                else if(player1.pos.y > player2.pos.y)
                {
                    if(rotationchange < 0)
                    {
                            while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                            {
                                //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                                player2.pos.x -= disttomove;
                                player2.drawpos.x -= disttomove;
                                calculatePlayerHitboxLocations(player2);
                                iteration++;

                            }
                            player2.velocity.x = -sqrt((m*m)/(kbd.g*kbd.g + 1));                   
                    }
                    else if(rotationchange > 0)
                    {
                    if(rotationchange > 0)
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && iteration <= 20)
                        {
                            //log << iteration << " " << player2.pos.x << " " << player2.drawpos.y << std::endl;
                            player2.pos.x += disttomove;
                            player2.drawpos.x += disttomove;
                            calculatePlayerHitboxLocations(player2);
                            iteration++;
                        }
                        player2.velocity.x = sqrt((m*m)/(kbd.g*kbd.g + 1)); 
                    }
                    }
                }

            }
            

            if(m != 0)
            {
                if(player2.velocity.x > 0)
                {
                    if(player1.velocity.x > 0)
                    {
                        player2.velocity.x = player2.velocity.x + (0.6 * player1.velocity.x);
                    }
                }
                if(player2.velocity.x < 0)
                {
                    if(player1.velocity.x < 0)
                    {
                        player2.velocity.x = player2.velocity.x + (0.6 * player1.velocity.x);
                    }
                }
            }
            //log << << m << " power " << std::endl; 
                //disable hitbox after attack#
                player1.attacking = 4;
            player1.timehit = player1.GetTicks; //time player1 hit player 2

            }                
    }
    }

    return hit;

}

void resolveswordnotattackingcollision(player &player1, player &player2, vector2i mouse, int direction) //direction is 1 for getting out clockwise and -1 for getting out anticlockwise
{

                int loop = 0; //limit the number of times the following while loops can be carried out to prevent crashing

                int precisecollision = 0;
                float distancefromswordtohand = CalculateHypotenuse(vector2i{player1.swordprevrelativepos.x, player1.swordprevrelativepos.y});
                player1.swordrotation = player1.swordprevrotation;
                vector2f satdegrees = polartocartesian(20, player1.swordrotation-90);
                player1.sworddrawpos.y = satdegrees.y + player1.centre.y- player1.idleanimation.size.y;
                player1.swordpos.y = satdegrees.y + player1.centre.y;
                player1.swordpos.x = satdegrees.x + player1.centre.x;     

                while(precisecollision == 0 && loop < 50)
                {
                    player1.swordrotation-=direction;
                    satdegrees = polartocartesian(player1.attackradius, player1.swordrotation-90);
                    player1.sworddrawpos.y = satdegrees.y + player1.centre.y- player1.idleanimation.size.y;
                    player1.swordpos.y = satdegrees.y + player1.centre.y;
                    player1.swordpos.x = satdegrees.x + player1.centre.x;
                    calculateSwordHitboxLocations(player1);
                    precisecollision = ((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))));
                    loop++;
                }
                loop = 0;
                while(precisecollision == 1 && loop < 50)
                {
                    player1.swordrotation+=direction;
                    satdegrees = polartocartesian(player1.attackradius, player1.swordrotation-90);
                    player1.sworddrawpos.y = satdegrees.y + player1.centre.y- player1.idleanimation.size.y;
                    player1.swordpos.y = satdegrees.y + player1.centre.y;
                    player1.swordpos.x = satdegrees.x + player1.centre.x;
                    calculateSwordHitboxLocations(player1);
                    precisecollision = ((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))));
                    loop++;
                }    



              player1.swordrelativepos.x = player1.swordpos.x - player1.centre.x;
              player1.swordrelativepos.y = player1.swordpos.y - player1.centre.y;
              player1.attackcentre.x-=player1.swordrelativepos.x;
              player1.attackcentre.y-=player1.swordrelativepos.y;

}

void swordnotattackingcollisions(player &player1, player &player2, vector2i mouse, std::ofstream &log)
{
    calculateSwordHitboxLocations(player1);
    if((player1.broadcollision == 1) && (player1.swordon == 1) && (player2.dead == 0))
    {
        //if(player1.attacking != 3 || (findknockbackdistance(player1) == 0))
        {

            double midswordangle = midpointofangles(player1.swordrotation, player1.swordprevrotation);
            double q1 = midpointofangles(midswordangle, player1.swordprevrotation);
            double q3 = midpointofangles(midswordangle, player1.swordrotation);


            vector2f swordtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, player1.swordrotation);
            vector2f swordhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, player1.swordrotation);
            vector2f swordprevtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, player1.swordprevrotation);
            vector2f swordprevhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, player1.swordprevrotation);
            vector2f swordmidtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, midswordangle);
            vector2f swordmidhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, midswordangle);
            vector2f swordq1tip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, q1);
            vector2f swordq1hilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, q1);

            vector2f swordq3tip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, q3);
            vector2f swordq3hilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, q3); 
            
            hitbox h1 ={swordprevtip, swordprevhilt, swordq1hilt, swordq1tip};
            hitbox h2 = {swordq1tip, swordq1hilt, swordmidhilt, swordmidtip};
            hitbox h3 ={swordprevtip, swordprevhilt, swordq1hilt, swordq1tip};
            hitbox h4 = {swordq1tip, swordq1hilt, swordmidhilt, swordmidtip};

            int vaguercollision =  collision(h1, calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(h2, calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(h1, calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || collision(h2, calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || collision(h1, calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0)) || collision(h2, calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0)); 
            int vaguercollision2 = collision(h3, calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(h4, calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(h3, calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || collision(h4, calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || collision(h3, calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0)) || collision(h4, calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0)); 
            
            if(midswordangle == 0)
            {
                vaguercollision = 0;
                vaguercollision2 = 0;
                
            }
            if(q1 == 0)
            {
                vaguercollision = 0;
                vaguercollision2 = 0;
                
            }
            if(q3 == 0)
            {
                vaguercollision = 0;
                vaguercollision2 = 0;
                
            }

            if((vaguercollision || vaguercollision2 || ((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))))))
            {

            int direction = 1;
            float swordrotationchange = FindRotationChange(player1.swordrotation, player1.swordprevrotation);

            if(abs(swordrotationchange) >5)
            {
                if(swordrotationchange > 0)
                {
                    direction = -1;
                }
                else
                {
                    direction = 1;
                }
                ////log << << "resolve" << std::endl;
                resolveswordnotattackingcollision(player1, player2, mouse, direction);
            }
            else
            {

                ////log << << "assass" << std::endl;

                axis swordirection;
                vector2f2 swordendpoints = calculateswordendpoints(player1);
                swordirection = gradient(swordendpoints.v1, swordendpoints.v2);
                swordirection.g = -swordirection.g;
                int player2centrex = (int)(player2.pos.x + (player2.idleanimation.size.x/2.0));
                int player2centrey = (int)(player2.drawpos.y + (player2.idleanimation.size.y/2.0));
                vector2f tip = calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation).v1; 
                int collidey = (swordirection.g*((player2centrex) - tip.x) + tip.y);
                int collidex = tip.x + (player2centrey-tip.y)/swordirection.g;
                if ((swordirection.g < -2 )|| (swordirection.g > 2 ))
                {
                    if(collidex > player2centrex)
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))))
                        {
                            ////log << << "a" << std::endl;
                            player1.attackcentre.x--;
                            player1.swordpos = PointCentreTranslationVector(mouse, player1.attackcentre, player1.centre);
                            player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
                            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
                            calculateSwordHitboxLocations(player1);
                        }
                    }
                    else
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))))
                        {
                            ////log << << "b" << std::endl;
                            player1.attackcentre.x++;
                            player1.swordpos = PointCentreTranslationVector(mouse, player1.attackcentre, player1.centre);
                            player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
                            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
                            calculateSwordHitboxLocations(player1);
                        }
                    }
                }
                else if(swordirection.horv == -1)
                {
                    if(tip.x > player2centrex)
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))))
                        {
                            ////log << << "c" << std::endl;
                            player1.attackcentre.x--;
                            player1.swordpos = PointCentreTranslationVector(mouse, player1.attackcentre, player1.centre);
                            player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
                            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
                            calculateSwordHitboxLocations(player1);
                        }
                    }
                    else
                    {
                        while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))))
                        {
                            ////log << << "d" << std::endl;
                            player1.attackcentre.x++;
                            player1.swordpos = PointCentreTranslationVector(mouse, player1.attackcentre, player1.centre);
                            player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
                            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
                            calculateSwordHitboxLocations(player1);
                        }
                    }               
                }
                else if(collidey > player2centrey)
                {
                    while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))))
                    {
                        ////log << << "e" << std::endl;
                        player1.attackcentre.y--;
                        player1.swordpos = PointCentreTranslationVector(mouse, player1.attackcentre, player1.centre);
                        player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
                        player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
                        calculateSwordHitboxLocations(player1);
                    }
                }
                else if(collidey < player2centrey)
                {
                    while((collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)) || (collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)) || collision(calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)))))
                    {
                        ////log << << "f" << std::endl;
                        player1.attackcentre.y++;
                        player1.swordpos = PointCentreTranslationVector(mouse, player1.attackcentre, player1.centre);
                        player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
                        player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
                        calculateSwordHitboxLocations(player1);
                    }              
                }

            }

            }


        }

    }
}


void swordtogroundcollisions(player &player1, stage s, vector2i mouse)
{
    calculateSwordHitboxLocations(player1);
    
    int c = collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(s.h[0], s.hpos[0], vector2f{0, 0}, 0));

    if(c)
    {
        int f = 0;
        while(c)
        {
            c = collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(s.h[0], s.hpos[0], vector2f{0, 0}, 0));
            player1.attackcentre.y++;
            player1.swordpos = PointCentreTranslationVector(mouse, player1.attackcentre, player1.centre);
            player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
            calculateSwordHitboxLocations(player1);
            f++;
        }
        //log << << "ground  ooll" << std::endl;
    }
}

int parry(player &player1, player &player2)
{
    int parry = 0;
    if(player2.parried == 0 && player1.parried == 0 && player1.swordon == 1 && (player1.broadcollision == 1) && (player2.dead == 0))
    {
    

    double midswordangle = midpointofangles(player1.swordrotation, player1.swordprevrotation);

    vector2f swordtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, player1.swordrotation);
    vector2f swordhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, player1.swordrotation);
    vector2f swordprevtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, player1.swordprevrotation);
    vector2f swordprevhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, player1.swordprevrotation);
    vector2f swordmidtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, midswordangle);
    vector2f swordmidhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, midswordangle);
    hitbox h1 ={swordprevtip, swordprevhilt, swordmidhilt, swordmidtip};
    hitbox h2 = {swordtip, swordhilt, swordmidhilt, swordmidtip};

    int h1b = collision(h1, calculatevertices(player2.sword.bladehitbox, player2.sword.bladehitboxpos, vector2f{(float)(player2.sword.handle.x - player2.sword.relativebladehitboxpos.x), (float)(player2.sword.handle.y - player2.sword.relativebladehitboxpos.y)}, player2.swordrotation));
    int h2b = collision(h2, calculatevertices(player2.sword.bladehitbox, player2.sword.bladehitboxpos, vector2f{(float)(player2.sword.handle.x - player2.sword.relativebladehitboxpos.x), (float)(player2.sword.handle.y - player2.sword.relativebladehitboxpos.y)}, player2.swordrotation));
    int bb = collision(calculatevertices(player1.sword.bladehitbox, player1.sword.bladehitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativebladehitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativebladehitboxpos.y)}, player1.swordrotation), calculatevertices(player2.sword.bladehitbox, player2.sword.bladehitboxpos, vector2f{(float)(player2.sword.handle.x - player2.sword.relativebladehitboxpos.x), (float)(player2.sword.handle.y - player2.sword.relativebladehitboxpos.y)}, player2.swordrotation));  
    
    axis sworddirection = perpendicular(findknockbackdirection(player2));
    vector2i swordchange = {player1.swordpos.x - player1.swordprevpos.x, player1.swordpos.y - player1.swordprevpos.y};
    if(bb || h1b || h2b)
      {
        //log << << "aowj" << std::endl;
        parry = 1;
        int p1player = player1.player;
        player2.attacking == 0;
        float swordrotationchange = FindRotationChange(player1.swordrotation, player1.swordprevrotation);

        int loop = 0;


        calculateSwordHitboxLocations(player1);
        calculateSwordHitboxLocations(player2);


        int direction = 0;  

        int p2swordtoright = (player2.swordpos.x > player2.centre.x);
        int p2swordabove = (player2.swordpos.y < player2.centre.y);

        if(abs(swordrotationchange) > 2)
        {
            //log << << "rotation" << std::endl;
            direction = -swordrotationchange;
            int limit = 26;
            if(direction > limit)
            {
                direction = limit;
            }
            if(direction < -limit)
            {
                direction = -limit;
            }
            //direction *= 10;
            if(abs(FindRotationChange(player1.swordrotation, player2.swordrotation)) < 90)
            {
                direction *= -1;
            }
        }
        else if((swordchange.x != 0) || (swordchange.y != 0))
        {
            //log << << "not" << std::endl;
            int turnstep = 10;
            if(swordchange.y != 0)
            {
            
            
                if(swordchange.y > 0)
                {
                    direction = -turnstep;
                }
                else
                {
                    direction = turnstep;
                }

                if(p2swordtoright)
                {
                    direction *= -1;
                }

            }
            else
            {
                direction = -turnstep;
                if(p2swordabove)
                {
                    direction *= -1;
                }
                if(p2swordtoright)
                {
                    if(swordchange.x < 0)
                    {
                        direction*=-1;
                    }
                }
                else if(swordchange.x < 0)
                {
                    direction *= -1;
                }
            }
        }

        player2.parried = 1;
        int fulldirection = 30;

        if(findknockbackdistance(player1) > 0)
        {
            player2.parryrotationdistance = 6;
            player2.parryrotationdistance *= findknockbackdistance(player1);
        }
        else if(abs(FindSwordRotationChange(player1)) > 2)
        {
            player2.parryrotationdistance = 20;
            fulldirection = 11;
        }
        else
        {
            player2.parryrotationdistance = 60;
        }

        if(player2.parryrotationdistance < 100)
        {
            fulldirection = 20;
        }
        if(player2.parryrotationdistance < 60)
        {
            fulldirection = 15;
        }

        if(direction > 0)
        {
            direction = fulldirection;
        }
        else
        {
            direction = -fulldirection;
        }
        player2.parrydirection = direction;
        player2.parryinitialrotation = player2.swordrotation;
    

        SFX_parry(player2);
        player2.startparryeffectanimation = 1;
        player2.parryeffectanimation.currentframe = 1;
        //vector2f player2swordtip = calculateswordtippos(player2.sword.tiphitbox.v2, player2.sword.tiphitboxpos, player2.sword.handle, player2.sword.relativetiphitboxpos, player2.swordrotation);
        player2.parryeffectpos = swordtip;


        }
      }    

  return parry;
}

void resolveparry(player &player2)
{
    if(player2.parried == 1)
    {
        if(abs(FindRotationChange(player2.swordrotation, player2.parryinitialrotation)) <  player2.parryrotationdistance)
        {
            player2.swordrotation+=player2.parrydirection;
            vector2f satdegrees = polartocartesian(player2.attackradius, player2.swordrotation-90);
            player2.sworddrawpos.y = satdegrees.y + player2.centre.y- player2.idleanimation.size.y;
            player2.swordpos.y = satdegrees.y + player2.centre.y;
            player2.swordpos.x = satdegrees.x + player2.centre.x;

            player2.swordrelativepos.x = player2.swordpos.x - player2.centre.x;
            player2.swordrelativepos.y = player2.swordpos.y - player2.centre.y;
            player2.attackcentre.x-=player2.swordrelativepos.x;
            player2.attackcentre.y-=player2.swordrelativepos.y;
        }
        else
        {
            player2.parried = 0;
        }
    }
}