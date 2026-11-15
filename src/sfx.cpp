#include "sfx.h"

void SFX_player2walk(player &player2)
{
    if((player2.velocity.y == 0) && (player2.prevvelocity.y == 0) && (player2.velocity.x != 0) && (!player2.dashdirection.x) && (!player2.dashdirection.y))
    {
        if(!Mix_Playing(6))
        {
            double pantotheright = (960 - player2.idleanimation.size.x) - player2.pos.x;
            pantotheright = pantotheright/(960 - player2.idleanimation.size.x);
            pantotheright*= 255; 
            if(pantotheright < 0)
            {
                pantotheright = 0;
            }
    
            Mix_SetPanning(6, pantotheright, 255 - pantotheright);
            if(player2.watercollision)
            {
                Mix_PlayChannel(6, player2.waterwalksfx[(rand()%6)], 0);
            }
            else
            {
                if((abs(player2.velocity.x == player2.terminalvelocity)) && !(rand()%5))
                {
                    Mix_PlayChannel(6, player2.fastwalksfx[(rand()%6)], 0);
                }
                else
                {
                    Mix_PlayChannel(6, player2.walksfx[(rand()%6)], 0);
                }
            }
        }
    }    
}

void SFX_player1walk(player &player1)
{
    if((player1.velocity.y == 0) && (player1.prevvelocity.y == 0) && (player1.velocity.x != 0) && (!player1.dashdirection.x) && (!player1.dashdirection.y)) //walking sound effect
    {
        if(!Mix_Playing(5))
        {
            double pantotheright = (960 - player1.idleanimation.size.x) - player1.pos.x;
            pantotheright = pantotheright/(960 - player1.idleanimation.size.x);
            pantotheright*= 255; 
            if(pantotheright < 0)
            {
                pantotheright = 0;
            }
            Mix_SetPanning(5, pantotheright, 255 - pantotheright);
            if(player1.watercollision)
            {
                Mix_PlayChannel(5, player1.waterwalksfx[(rand()%6)], 0);
            }
            else
            {
                if((abs(player1.velocity.x == player1.terminalvelocity)) && !(rand()%5))
                {
                    Mix_PlayChannel(5, player1.fastwalksfx[(rand()%6)], 0);
                }
                else
                {
                    Mix_PlayChannel(5, player1.walksfx[(rand()%6)], 0);
                }
            }
        }
    } 
}

void SFX_player2land(player &player2)
{
     if((player2.velocity.y == 0) && (player2.prevvelocity.y < 0))
    {
        if(!Mix_Playing(4))
        {
            double pantotheright = (960 - player2.idleanimation.size.x) - player2.pos.x;
            pantotheright = pantotheright/(960 - player2.idleanimation.size.x);
            pantotheright*= 255; 
                if(pantotheright < 0)
                {
                    pantotheright = 0;
                }

            Mix_SetPanning(4, pantotheright, 255 - pantotheright);
            if(player2.watercollision)
            {
                Mix_PlayChannel(4, player2.waterlandsfx[(rand()%3)], 0);     
            }
            else
            {
                Mix_PlayChannel(4, player2.landsfx[(rand()%3)], 0);
            }
        }

    }   
}

void SFX_player1land(player &player1)
{
    if((player1.velocity.y == 0) && (player1.prevvelocity.y < 0))
    {
        if(!Mix_Playing(3))
        {
            double pantotheright = (960 - player1.idleanimation.size.x) - player1.pos.x;
            pantotheright = pantotheright/(960 - player1.idleanimation.size.x);
            pantotheright*= 255; 
                if(pantotheright < 0)
                {
                    pantotheright = 0;
                }
            Mix_SetPanning(3, pantotheright, 255 - pantotheright);
            if(player1.watercollision)
            {
                Mix_PlayChannel(3, player1.waterlandsfx[(rand()%3)], 0);     
            }
            else
            {
                Mix_PlayChannel(3, player1.landsfx[(rand()%3)], 0);
            }
        }
    }
}

void SFX_player2getshit(player &player2)
{
    double pantotheright = (960 - player2.idleanimation.size.x) - player2.pos.x;
    pantotheright = pantotheright/(960 - player2.idleanimation.size.x);
    pantotheright*= 255; 
    if(pantotheright < 0)
    {
        pantotheright = 0;
    }
    Mix_SetPanning(4, pantotheright, 255 - pantotheright);
    Mix_PlayChannel(4, player2.hitsfx[(rand()%3)], 0);
}

void SFX_player1getshit(player &player1)
{
    double pantotheright = (960 - player1.idleanimation.size.x) - player1.pos.x;
    pantotheright = pantotheright/(960 - player1.idleanimation.size.x);
    pantotheright*= 255; 
    if(pantotheright < 0)
    {
        pantotheright = 0;
    }
    Mix_SetPanning(3, pantotheright, 255 - pantotheright);
    Mix_PlayChannel(3, player1.hitsfx[(rand()%3)], 0);
}

void SFX_player2death(player &player2)
{
    if(player2.character == 2)
    {
        if((rand()%500) == 1)
        {
            Mix_PlayChannel(7, player2.deathsfx[(rand()%2)], 0);
            player2.timetospendinhitstun = 2000;
        }
        else
        {
                Mix_PlayChannel(7, player2.deathsfx[(rand()%2)], 0);
                player2.timetospendinhitstun = 950;
        }
    }
    else
    {
        Mix_PlayChannel(7, player2.deathsfx[(rand()%3)], 0);
        player2.timetospendinhitstun = 950;
    }    
}

void SFX_player1death(player &player1)
{
    if(player1.character == 2)
    {
        if((rand()%500) == 1)
        {
            Mix_PlayChannel(7, player1.deathsfx[(rand()%2)], 0);
            player1.timetospendinhitstun = 2000;
        }
        else
        {
                Mix_PlayChannel(7, player1.deathsfx[(rand()%2)], 0);
                player1.timetospendinhitstun = 950;
        }
    }
    else
    {
        Mix_PlayChannel(7, player1.deathsfx[(rand()%3)], 0);
        player1.timetospendinhitstun = 950;
    }
}

void SFX_jump(player &player1)
{
    double pantotheright = (960 - player1.idleanimation.size.x) - player1.pos.x;
    pantotheright = pantotheright/(960 - player1.idleanimation.size.x);
    pantotheright*= 255; 
    if(pantotheright < 0)
    {
        pantotheright = 0;
    }
    Mix_SetPanning(player1.player, pantotheright, 255 - pantotheright);
    if(player1.watercollision)
    {
        Mix_PlayChannel(player1.player, player1.waterlandsfx[(rand()%2)], 0);    
    }
    else
    {
        Mix_PlayChannel(player1.player, player1.jumpsfx[(rand()%2)], 0);
    }
    player1.velocity.y = player1.jumpvelocity;
}

void SFX_parry(player &player2)
{
    if(!Mix_Playing(7))
    {
        double pantotheright = (960 - player2.idleanimation.size.x) - player2.pos.x;
        pantotheright = pantotheright/(960 - player2.idleanimation.size.x);
        pantotheright*= 255; 
        if(pantotheright < 0)
        {
            pantotheright = 0;
        }

        Mix_SetPanning(7, pantotheright, 255 - pantotheright);
        Mix_PlayChannel(7, player2.clanksfx[(rand()%7)], 0);
        
    }
}

void SFX_entrance(Mix_Chunk* entrancesfx)
{
    if(!Mix_Playing(7))
    {
        Mix_SetPanning(7, 128, 255 - 128);   
        Mix_PlayChannel(7, entrancesfx, 0);
    }
}