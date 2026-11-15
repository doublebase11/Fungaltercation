#include "specialmoves.h"
void drawspores(player &player, SDL_Renderer* renderer, viewport &viewport)
{
    if(player.specialmove == 1)
    {
        for(int i = 0; i <player.sporecount; i++)
        {
            if(player.pause == 0 && player.gameover == 0)
            {
                //move spore
                if(abs(player.s[i].velocity.x) < 0.1)
                {
                    player.s[i].velocity.x = player.s[i].velocity.x/10;
                }
                if(abs(player.s[i].velocity.y) < 0.1)
                {
                    player.s[i].velocity.y = 0;
                }
                player.s[i].pos.x += player.s[i].velocity.x;
                player.s[i].pos.y -= player.s[i].velocity.y;
                ////log << << player.sporevelocity.x << " " << player.sporevelocity.y << std::endl;
                if(player.s[i].velocity.x > 0) //deceleration????
                {
                    player.s[i].velocity.x -= 0.1;
                }
                if(player.s[i].velocity.x < 0)
                {
                    player.s[i].velocity.x += 0.1;
                }
                if(player.s[i].velocity.y > 0) //deceleration????
                {
                    player.s[i].velocity.y -= 0.1;
                }
                if(player.s[i].velocity.y < 0)
                {
                    player.s[i].velocity.y += 0.1;
                }   
            }

            if(player.gameover == 0 && player.pause == 0)
            {
                player.s[i].rotation += player.s[i].rotationdirection;
            }


            //draw spore
            if(player.s[i].size < 22)
            {
                drawPngEx(renderer, player.sporetexture, viewport, 90, 16, 12, 12, player.s[i].pos.x, player.s[i].pos.y, 6, 6, player.s[i].rotation, SDL_FLIP_NONE); //2 | 12

            }
            else if(player.s[i].size < 44)
            {
                drawPngEx(renderer, player.sporetexture, viewport, 90, 80, 14, 14, player.s[i].pos.x, player.s[i].pos.y, 7, 7, player.s[i].rotation, SDL_FLIP_NONE); //5 | 14

            }
            else if(player.s[i].size < 66)
            {
            
                drawPngEx(renderer, player.sporetexture, viewport, 22, 12, 20, 20, player.s[i].pos.x, player.s[i].pos.y, 10, 10, player.s[i].rotation, SDL_FLIP_NONE); //1 | 20

            }
            else if(player.s[i].size < 76)
            {
                drawPngEx(renderer, player.sporetexture, viewport, 148, 10, 24, 24, player.s[i].pos.x, player.s[i].pos.y, 12, 12, player.s[i].rotation, SDL_FLIP_NONE); //3 | 24

            }
            else if(player.s[i].size < 86)
            {

                drawPngEx(renderer, player.sporetexture, viewport, 28, 82, 8, 8, player.s[i].pos.x, player.s[i].pos.y, 4, 4, player.s[i].rotation, SDL_FLIP_NONE); //4 | 8
            }
            else if(player.s[i].size < 96)
            {

                drawPngEx(renderer, player.sporetexture, viewport, 96, 158, 5, 5, player.s[i].pos.x, player.s[i].pos.y, 2, 2, player.s[i].rotation, SDL_FLIP_NONE); //8 | 5
            }
            else if(player.s[i].size < 97)
            {
               drawPngEx(renderer, player.sporetexture, viewport, 160, 158, 5, 5, player.s[i].pos.x, player.s[i].pos.y, 2, 2, player.s[i].rotation, SDL_FLIP_NONE); //9 | 5 

            }
            else if(player.s[i].size < 98)
            {
                drawPngEx(renderer, player.sporetexture, viewport, 30, 156, 2, 2, player.s[i].pos.x, player.s[i].pos.y, 1, 1, player.s[i].rotation, SDL_FLIP_NONE); //7 | 2

            }
            else if(player.s[i].size < 99)
            {

                drawPngEx(renderer, player.sporetexture, viewport, 158, 82, 6, 6, player.s[i].pos.x, player.s[i].pos.y, 3, 3, player.s[i].rotation, SDL_FLIP_NONE); //6 | 6
            }

        }
    }
}

void shootspores(player &player)
{
    if(player.specialmove == 1)
    {
        if(player.special == 1)
        {
            //log << << "wheheh" << std::endl;
            player.sporecount = 0;
            player.specialstarttime = player.GetTicks;
            player.special = 2;
            player.sporecollision = 0;

        }
        if((player.special == 2) && ((player.GetTicks-player.specialstarttime) < player.sporeattackduration)) //attack active
        {
            if(player.sporecount < player.sporecountlimit)
            {
                player.swordon = 0;
            }
            else     
            {
                player.swordon = 1;
            }

            for(int i = 1; i < (player.sporefirespeed+1); i++)
            {
                if(player.sporecount < player.sporecountlimit) //create new spore
                {
                    if(player.dead == 0)
                    {
                        vector2f swordhilt = calculateswordhiltpos(player.sword.bladehitbox.v3, player.sword.bladehitboxpos, player.sword.handle, player.sword.relativebladehitboxpos, player.swordrotation);
                        player.s[player.sporecount].pos = {(int)(swordhilt.x), (int)(swordhilt.y)};
                    }
                    else
                    {
                        player.s[player.sporecount].pos = {player.pos.x + player.idleanimation.size.x/2, player.drawpos.y + player.idleanimation.size.y/2};
                    }

                    float addvelocity = (rand()%100);
                    addvelocity = addvelocity/100;
                    addvelocity = addvelocity*player.sporerandomizedspeed;

                    float anglevariance = (rand()%100);
                    anglevariance = anglevariance/100;
                    anglevariance = anglevariance*player.sporespreadangle;
                    if(player.GetTicks%2 == 0)
                    {
                        anglevariance = -anglevariance;
                    }
                    double angler =  (player.swordrotation+anglevariance+90)* 3.14159265;
                    angler = angler/180; //converts player.swordrotation to radians
                    player.s[player.sporecount].velocity = {(-cos(angler)*(player.sporebasespeed+addvelocity)),(sin(angler) *(player.sporebasespeed+addvelocity))};

                    player.s[player.sporecount].size =  (rand()%98);

                    if((rand()%100)<50)
                    {
                        player.s[player.sporecount].rotationdirection = 1;
                    }

                    player.s[player.sporecount].rotationdirection = player.s[player.sporecount].rotationdirection*((rand()%player.sporespinmaxspeed)+1);

                    player.sporecount++;
                }
            }


        }
        else
        {
            player.special = 0;
            player.swordon = 1;
            int p = (rand()%100);
            if(p < player.sporedissapearancethreshold)
            {
                player.sporecount--;
            }

            for(int i = 1; i < player.sporesdisappearingperframe; i++)
            {
                p = (rand()%100);
                if(p < player.sporedissapearancethreshold)
                {
                    player.sporecount--;
                }
            }



        }
    }

}

void sporecollisions(player &player1, player &player2)
{
    if(player1.specialmove == 1 && player1.dead == 0)
    {
        player2.stunned = 0;
        if(player1.sporecount > 0)
        {
            hitbox sporehitbox;
            vector2f sporehitboxpos = {0, 0};
            double sporehitboxsize = 0;

            for(int i = 0; i < player1.sporecount; i++)
            {
                if((player2.stunned == 0) && (player1.sporecollision == 0))
                {
                    if(player1.s[i].size < 22)
                    {
                        //2 
                        sporehitboxsize = 8;

                    }
                    else if(player1.s[i].size < 44)
                    {
                        //5 
                        sporehitboxsize = 10;

                    }
                    else if(player1.s[i].size < 66)
                    {
                        //1 
                        sporehitboxsize = 16;

                    }
                    else if(player1.s[i].size < 76)
                    {
                        //3 
                        sporehitboxsize = 20;

                    }
                    else if(player1.s[i].size < 86)
                    {
                        //4 
                        sporehitboxsize = 4;
                    }
                    else if(player1.s[i].size < 96)
                    {
                        //8 
                        sporehitboxsize = 2;
                    }
                    else if(player1.s[i].size < 97)
                    {
                       //9 
                       sporehitboxsize = 2;

                    }
                    else if(player1.s[i].size < 98)
                    {
                        //7 
                        sporehitboxsize = 2;

                    }
                    else if(player1.s[i].size < 99)
                    {
                        //6 
                        sporehitboxsize = 2;
                    }

                    sporehitboxpos.x = player1.s[i].pos.x;
                    sporehitboxpos.y = player1.s[i].pos.y;
                    sporehitbox = {{0, 0}, {sporehitboxsize, 0}, {sporehitboxsize, sporehitboxsize}, {0, sporehitboxsize}};

                    player2.bodyhitboxpos= {player2.pos.x + player2.relativebodyhitboxpos.x, player2.drawpos.y + player2.relativebodyhitboxpos.y};

                    if(sporehitboxsize > 0)
                    {
                        hitbox csporehitbox = calculatevertices(sporehitbox, sporehitboxpos, vector2f{sporehitboxsize/2, sporehitboxsize/2}, player1.s[i].rotation);
                        int bodycollision = (collision(csporehitbox, calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)));
                        int capcollision = (collision(csporehitbox, calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)));
                        if(bodycollision || capcollision)
                        {
                            ////log << << "lone and level sands" <<  player1.GetTicks << std::endl;
                            player2.stunned = 1;

                            player2.timetospendinhitstun = 500;
                            player2.hitstuntimer = player1.GetTicks;
                        }
                    }
                }

            }
        }
    }

}

void chargehit(player &player1, player &player2)
{
    if(player1.specialmove == 2)
    {
        if((player1.inhitstun) && (player1.chargehitboxactive))
        {
            player1.chargehitboxactive = 0;
            player1.specialstarttime = player1.GetTicks;
            player1.timetospendinhitstun = 1000;
            player1.charge = 2;
        }
        else if(((player1.GetTicks-player1.chargestarttime) > player1.chargeduration))
        {
            player1.chargehitboxactive = 0;
        }
        else if(hypot(player1.velocity.x, player1.velocity.y) < 3)
        {
            player1.chargehitboxactive = 0;
        }
        else if(player1.chargedirection.x == 0)
        {
            if(player1.velocity.y/abs(player1.velocity.y) != player1.chargedirection.y)
            {
                player1.chargehitboxactive = 0;
            }
        }
        else if(player1.chargedirection.y == 0)
        {
            if(player1.velocity.x/abs(player1.velocity.x) != player1.chargedirection.x)
            {
                player1.chargehitboxactive = 0;
            }
        }
        else if(player1.velocity.x == 0)
        {
            if(player1.velocity.y/abs(player1.velocity.y) != player1.chargedirection.y)
            {
                player1.chargehitboxactive = 0;
            }         
        }
        else if(player1.velocity.y == 0)
        {
            if(player1.velocity.x/abs(player1.velocity.x) != player1.chargedirection.x)
            {
                player1.chargehitboxactive = 0;
            }      
        }
        else if((player1.velocity.x/abs(player1.velocity.x) != player1.chargedirection.x) || (player1.velocity.y/abs(player1.velocity.y) != player1.chargedirection.y))
        {
            player1.chargehitboxactive = 0;
        }


        if(player1.special == 1)
        {   

            player1.chargestarttime = player1.GetTicks;
            player1.chargehitboxactive = 1;
            if(player1.charge == 1)
            {
                player1.specialstarttime = player1.GetTicks - (0.5*player1.specialcooldown);
            }
            else
            {
                player1.specialstarttime += (0.5*player1.specialcooldown);
            }
                        
            vector2f distancebetweenplayers = {(double)(player2.pos.x - player1.pos.x), (double)(player2.pos.y - player1.pos.y)};
            double magnitude = hypotf(distancebetweenplayers.x, distancebetweenplayers.y);

            player1.velocity.x = (distancebetweenplayers.x/magnitude)*20;
            player1.velocity.y = -(distancebetweenplayers.y/magnitude)*20;
            player1.initialchargevelocity = player1.velocity;
            player1.chargedirection = {player1.velocity.x/abs(player1.velocity.x), player1.velocity.y/abs(player1.velocity.y)};
            


            if(player1.chargedirection.x != player1.chargedirection.x)
            {
                player1.chargedirection.x = 0;
            }
            else
            {
                if(player1.chargedirection.x == 1)
                {
                    player1.flip = SDL_FLIP_NONE;
                }
                else
                {
                    player1.flip = SDL_FLIP_HORIZONTAL;
                }
            }
            if(player1.chargedirection.y != player1.chargedirection.y)
            {
                player1.chargedirection.y = 0;
            }
            

            player1.special = 0;
        } 
    }
}

void chargecollisions(player &player1, player &player2)
{
    if(player1.chargehitboxactive)
    {
        int bb = (collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)));
        int bc = (collision(calculatevertices(player1.bodyhitbox, player1.bodyhitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)));
        int fc = (collision(calculatevertices(player1.feethitbox, player1.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.caphitbox, player2.caphitboxpos, vector2f{0, 0}, 0)));
        int cf = (collision(calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player1.caphitbox, player1.caphitboxpos, vector2f{0, 0}, 0)));
        int fb = (collision(calculatevertices(player1.feethitbox, player1.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player2.bodyhitbox, player2.bodyhitboxpos, vector2f{0, 0}, 0)));
        if(bb || bc || fc || cf || player1.capcollided || player2.capcollided || player1.bodycollided || player2.bodycollided)
        {
            if(player1.chargehitboxactive)
            {
                //log << << "hit" << std::endl;
                if(player2.inhitstun)
                {
                    //log << << "trueeeeeeeeeeeeeeee" << std::endl;
                }
                player2.velocity = player1.initialchargevelocity;
                player2.velocity.x *=0.3;
                player2.velocity.y = 6;
                player2.timetospendinhitstun =player1.chargehitstun;
                player2.hitstuntimer = player1.GetTicks;
                player2.health -= player1.chargedamage;
                player1.chargehitboxactive = 0;
                
            }
        }
    
    }
}
