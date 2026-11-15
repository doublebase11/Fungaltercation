#include "movementcollisions.h"


void calculatePlayerHitboxLocations(player &player)
{
    player.bodyhitboxpos= {player.pos.x + player.relativebodyhitboxpos.x, player.drawpos.y + player.relativebodyhitboxpos.y};
    player.body2hitboxpos= {player.pos.x + player.relativebody2hitboxpos.x, player.drawpos.y + player.relativebody2hitboxpos.y};
    player.caphitboxpos= {player.pos.x + player.relativecaphitboxpos.x, player.drawpos.y + player.relativecaphitboxpos.y};
    player.cap2hitboxpos= {player.pos.x + player.relativecap2hitboxpos.x, player.drawpos.y + player.relativecap2hitboxpos.y};
    player.cap3hitboxpos= {player.pos.x + player.relativecap3hitboxpos.x, player.drawpos.y + player.relativecap3hitboxpos.y};
    player.feethitboxpos= {player.pos.x + player.relativefeethitboxpos.x, player.drawpos.y + player.relativefeethitboxpos.y};
}

void broadPlayerCollisions(player &player1, player &player2)
{
    player1.broadcollision = 0;
    player2.broadcollision = 0;
    float distx = player1.centre.x - player2.centre.x;
    float disty = player1.centre.y - player2.centre.y;
    float distance = sqrtf((distx*distx) + (disty*disty));
    ////log <<<< (distance <= 40 + player1.sword.size.y + player2.sword.size.y) << std::endl;
    if((distance <= 40 + player1.sword.size.y + player2.sword.size.y))
    {
        player1.broadcollision = 1;
        player2.broadcollision = 1;
    }

}

void bodyCollisionVelocities(player &player1, player &player2)
{
    player1.velocity.x = 0;

}

void bodyCollisions(player &player1, player &player2) //this should probably be in a different file
{
    player1.bodycollided = 0;
    if(player1.broadcollision == 1 && (player2.dead == 0))
    {
        if(collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)))
        {
            player1.bodycollided = 1;
            if(player1.velocity.x < 0)
            {
            
                bodyCollisionVelocities(player1, player2);
                while(collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)))
                {
                     player1.pos.x ++;
                     calculatePlayerHitboxLocations(player1);
                }
            }
            else if(player1.velocity.x > 0)
            {
            
                bodyCollisionVelocities(player1, player2);
                while(collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)))
                {
                     player1.pos.x -= 0.1;
                     calculatePlayerHitboxLocations(player1);
                }  
    
            }
        }
    }
}

void capCollisions(player &player1, player &player2) //this should probably be in a different file
{
    player1.capcollided = 0;
    float potentialv = -0.75*player1.velocity.y;

    if(player2.velocity.y > 0 && potentialv < 10)
    {
        potentialv = 10;
    }

    if(player1.broadcollision == 1 && (player2.dead == 0))
    {
        if((collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && (player1.velocity.y < player2.velocity.y) && (player1.pos.y < player2.pos.y))
        {
            player1.capcollided = 1;
            if(player1.stagecollisionstate.y == 0)
            {
                while((collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))))
                {
                    player1.pos.y = player1.pos.y - 1;
                    player1.drawpos.y = player1.drawpos.y - 1;
                    calculatePlayerHitboxLocations(player1);
                }
                player1.velocity.y = potentialv;
                if(player1.fastfalling == 1)
                {
                    player1.fastfalling = -1;
                }
            }
            else
            {
                if(player2.velocity.y > 0)
                {
                    player2.velocity.y = -0.1;  
                    while((collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))))
                    {
                        player2.pos.y = player2.pos.y + 1;
                        player2.drawpos.y = player2.drawpos.y + 1;
                        calculatePlayerHitboxLocations(player2);
                    }  
                    while((collision(calculatevertices(player1.feethitbox, player1.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))))
                    {
                        player2.pos.y = player2.pos.y + 1;
                        player2.drawpos.y = player2.drawpos.y + 1;
                        calculatePlayerHitboxLocations(player2);
                    }
                }         
            }
        }
    
        if((collision(calculatevertices(player1.feethitbox, player1.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))) && (player1.velocity.y < player2.velocity.y) && (player1.pos.y < player2.pos.y))
        { 
            player1.capcollided = 1;

            if(player1.stagecollisionstate.y == 0)
            {  
                while((collision(calculatevertices(player1.feethitbox, player1.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))))
                {
                    player1.pos.y = player1.pos.y - 1;
                    player1.drawpos.y = player1.drawpos.y - 1;
                    calculatePlayerHitboxLocations(player1);
                }

                player1.velocity.y = potentialv;

                if(player1.fastfalling == 1)
                {
                    player1.fastfalling = -1;
                }
            }  
            else
            {
                if(player2.velocity.y > 0)
                {
                    {
                        player2.velocity.y = -0.1;  
                        while((collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))))
                        {
                            player2.pos.y = player2.pos.y + 1;
                            player2.drawpos.y = player2.drawpos.y + 1;
                            calculatePlayerHitboxLocations(player2);
                        }  
                        while((collision(calculatevertices(player1.feethitbox, player1.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0))))
                        {
                            player2.pos.y = player2.pos.y + 1;
                            player2.drawpos.y = player2.drawpos.y + 1;
                            calculatePlayerHitboxLocations(player2);
                        }
                    }  
                    player2.velocity.y = -0.1;    
                }      
            }
        }
    }
}

vector2i stageCollisions(stage &s, player &player)
{

    vector2i touching = {0, 0};
    if(player.gamestart == 0 && (player.dead == 0))
    {
    for(int i = 0; i < (s.hitboxnumber); i++) //loops through each platform to check for collision
    {
        //detects if landing on platform
        if(collision(calculatevertices(player.feethitbox, player.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(s.h[i], s.hpos[i], vector2f{0, 0}, 0)) == 1) 
        {
        
            if(player.velocity.y <= 0)
            {
                 player.velocity.y = 0;
                 player.fastfalling = 0;   

                while(collision(calculatevertices(player.feethitbox, player.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(s.h[i], s.hpos[i], vector2f{0, 0}, 0)) == 1)
                {
                     player.pos.y -= 0.2;
                     player.drawpos.y -= 0.2;
                     calculatePlayerHitboxLocations(player);
                }

                touching.x = 1;
                player.pos.y += 1;
                player.drawpos.y += 1;
                calculatePlayerHitboxLocations(player);
            }
        }

        int bothercheckingsidecollision = 0;
        if(player.velocity.x > 0)
        {
            if(player.centre.x < lerp(s.h[i].v1.x + s.hpos[i].x, (s.h[i].v3.x) + s.hpos[i].x, 0.5))
            {
                bothercheckingsidecollision = 1;
            }
        }
        else if (player.velocity.x < 0)
        {
            if(player.centre.x > lerp(s.h[i].v1.x + s.hpos[i].x, (s.h[i].v3.x) + s.hpos[i].x, 0.5))
            {
                bothercheckingsidecollision = 1;
            }
        }
        
        //detects if colliding with the bottom of the platform
        if(collision(calculatevertices(player.caphitbox, player.caphitboxpos, vector2f{0, 0}, 0), calculatevertices(hitbox{{s.h[i].v4.x, s.h[i].v4.y - 1},{s.h[i].v3.x, s.h[i].v3.y - 1},s.h[i].v3,s.h[i].v4}, s.hpos[i], vector2f{0, 0}, 0)) || (collision(calculatevertices(player.bodyhitbox, player.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(hitbox{{s.h[i].v4.x+10, s.h[i].v4.y - 1},{s.h[i].v3.x-10, s.h[i].v3.y - 1},s.h[i].v3,s.h[i].v4}, s.hpos[i], vector2f{0, 0}, 0))))
        {

            if(player.velocity.y > 0)
            {
                 player.velocity.y = -0.1;
                while(collision(calculatevertices(player.caphitbox, player.caphitboxpos, vector2f{0, 0}, 0), calculatevertices(hitbox{{s.h[i].v4.x, s.h[i].v4.y - 1},{s.h[i].v3.x, s.h[i].v3.y - 1},s.h[i].v3,s.h[i].v4}, s.hpos[i], vector2f{0, 0}, 0)) || (collision(calculatevertices(player.bodyhitbox, player.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(hitbox{{s.h[i].v4.x+10, s.h[i].v4.y - 1},{s.h[i].v3.x-10, s.h[i].v3.y - 1},s.h[i].v3,s.h[i].v4}, s.hpos[i], vector2f{0, 0}, 0))))
                {
                     player.pos.y += 1;
                     player.drawpos.y += 1;
                     calculatePlayerHitboxLocations(player);
                }
                touching.y = 1;
            }
        }
        //dectecting if colliding from the side

    if(player.capcollided == 0)
    {


    if(bothercheckingsidecollision)
    { 
        if(collision(calculatevertices(player.bodyhitbox, player.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(s.h[i], s.hpos[i], vector2f{0, 0}, 0)) || collision(calculatevertices(player.body2hitbox, player.body2hitboxpos, vector2f{0, 0}, 0), calculatevertices(s.h[i], s.hpos[i], vector2f{0, 0}, 0)))
        {

            if(player.velocity.x < 0)
            {
                 player.velocity.x = 0;
                while(collision(calculatevertices(player.bodyhitbox, player.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(s.h[i], s.hpos[i], vector2f{0, 0}, 0)) || collision(calculatevertices(player.body2hitbox, player.body2hitboxpos, vector2f{0, 0}, 0), calculatevertices(s.h[i], s.hpos[i], vector2f{0, 0}, 0)))
                {
                     player.pos.x ++;
                     calculatePlayerHitboxLocations(player);
                }
            }
            else if(player.velocity.x > 0)
            {
                 player.velocity.x = 0;
                while(collision(calculatevertices(player.bodyhitbox, player.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(s.h[i], s.hpos[i], vector2f{0, 0}, 0)) || collision(calculatevertices(player.body2hitbox, player.body2hitboxpos, vector2f{0, 0}, 0), calculatevertices(s.h[i], s.hpos[i], vector2f{0, 0}, 0)))
                {
                     player.pos.x -= 0.1;
                     calculatePlayerHitboxLocations(player);
                }  

            }
        }
         }
    }

   
    }
    }

    return touching;
}