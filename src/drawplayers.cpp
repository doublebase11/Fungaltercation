#include "drawplayers.h"

void FlipPlayer(player &player)
{
    if(player.pause == 0 && player.gameover == 0)
    {
        if(player.xmovementdirection == 1)
        {
            player.flip = SDL_FLIP_NONE;
        }
        else if(player.xmovementdirection == -1)
        {
            player.flip = SDL_FLIP_HORIZONTAL;
        }
    }
    else
    {
        if(player.pausexmovementdirection == 1)
        {
            player.flip = SDL_FLIP_NONE;
        }
        else if(player.pausexmovementdirection == -1)
        {
            player.flip = SDL_FLIP_HORIZONTAL;
        }       
    }
}

void drawPlayerArm(player &player1, SDL_Renderer* renderer, viewport &viewport)
{
    //vector2f swordhilt = calculateswordhiltpos({player1.sword.bladehitbox.v3.x, player1.sword.size.y-8}, {player1.sword.bladehitboxpos.x, player1.sword.bladehitboxpos.y - player1.sword.relativebladehitboxpos.y}, player1.sword.handle, {player1.sword.relativebladehitboxpos.x, 0}, player1.swordrotation);

    double player1centrey = (int)(player1.drawpos.y + (player1.idleanimation.size.y/2.0));
    double player1centrex = (int)(player1.pos.x + (player1.idleanimation.size.x/2.0));
    findElbowposAndAngles(player1);
drawPngEx(renderer, player1.forearmtexture, viewport, 0, 0, player1.elbowwidth, player1.elbowlength+3, player1.elbowpos.x - player1.forearmrotationcentre.x, player1.elbowpos.y - player1.forearmrotationcentre.y, player1.forearmrotationcentre.x, player1.forearmrotationcentre.y, player1.forearmangle, SDL_FLIP_NONE);
    drawPngEx(renderer, player1.upperarmtexture, viewport, 0, 0, player1.elbowwidth, player1.elbowlength+3, player1centrex-player1.upperarmrotationcentre.x, player1centrey - player1.upperarmrotationcentre.y, player1.upperarmrotationcentre.x, player1.upperarmrotationcentre.y, player1.upperarmangle, SDL_FLIP_NONE);
drawPngEx(renderer, player1.jointtexture, viewport, 0, 0, player1.elbowwidth, player1.elbowlength+3, player1.elbowpos.x - player1.forearmrotationcentre.x, player1.elbowpos.y - player1.forearmrotationcentre.y, player1.forearmrotationcentre.x, player1.forearmrotationcentre.y, player1.forearmangle, SDL_FLIP_NONE);
    
    //drawPngEx(renderer, player1.upperarmtexture, viewport, 0, 0, 5, 5, player1centrex, player1centrey, player1.upperarmrotationcentre.x, player1.upperarmrotationcentre.y, 0, SDL_FLIP_NONE);
    
    //drawPngEx(renderer, player1.forearmtexture, viewport, 0, 0, 5, 5, swordhilt.x, swordhilt.y, player1.upperarmrotationcentre.x, player1.forearmrotationcentre.y, 0, SDL_FLIP_NONE);
}
void DrawPlayer(player &player, SDL_Renderer* renderer, viewport &viewport)
{   

    if(player.dead == 0)
    {
        FlipPlayer(player);
        
        animation animation;
        if((player.pause == 0) && (player.stunned == 0) && (player.gameover == 0))
        {
            if(player.velocity.y > 0)
            {
                UpdateAnimation(player.jumpanimation, player.GetTicks);
                animation = player.jumpanimation;
            }
            else if(player.velocity.y < 0)
            {
                UpdateAnimation(player.fallanimation, player.GetTicks);
                animation = player.fallanimation;
            }
            else if(player.xmovementdirection != 0)
            {
                UpdateAnimation(player.walkanimation, player.GetTicks);
                animation = player.walkanimation;
            }
            else
            {
                UpdateAnimation(player.idleanimation, player.GetTicks);
                animation = player.idleanimation;
            }
        }
        else
        {
            if(player.velocity.y > 0)
            {
                animation = player.jumpanimation;
            }
            else if(player.velocity.y < 0)
            {
                animation = player.fallanimation;
            }
            else if(player.pausexmovementdirection != 0)
            {
                animation = player.walkanimation;
            }
            else
            {
                animation = player.idleanimation;
            }        
        }
    
        drawPlayerArm(player, renderer, viewport);
        drawPngEx(renderer, animation.textures, viewport, ChooseSprite(animation), 0, animation.size.x, animation.size.y, player.pos.x, player.drawpos.y, animation.size.x/2, animation.size.y/2, 0, player.flip);
    }
}

void drawplayers(player player1, player player2, SDL_Renderer* renderer, viewport &viewport)
{
    DrawSword(player1, renderer, viewport);
    DrawSword(player2, renderer, viewport);

    DrawPlayer(player1, renderer, viewport);
    DrawPlayer(player2, renderer, viewport);
}