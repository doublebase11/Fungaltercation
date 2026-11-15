#include "effects.h"

void parryeffect(player &player1, viewport v, SDL_Renderer* renderer)
{
    if(player1.startparryeffectanimation == 1)
    {
        if(player1.parryeffectanimation.currentframe == player1.parryeffectanimation.maxframes)
        {
            player1.startparryeffectanimation = 0;
        }
        else
        {
            if(player1.pause == 0 && player1.gameover == 0)
            {
                player1.parryeffectanimation.currentframe++;
            }
            drawPngEx(renderer, player1.parryeffectanimation.textures, v, ChooseSprite(player1.parryeffectanimation), 0, player1.parryeffectanimation.size.x, player1.parryeffectanimation.size.y, player1.parryeffectpos.x - (player1.parryeffectanimation.size.x)/2, player1.parryeffectpos.y - (player1.parryeffectanimation.size.y)/2, 0, 0, 0, SDL_FLIP_NONE);
        }
    }
}

void hiteffect(player &player1, viewport v, SDL_Renderer* renderer)
{
    if(player1.starthiteffectanimation == 1)
    {
        if(player1.hiteffectanimation.currentframe == player1.hiteffectanimation.maxframes)
        {
            player1.starthiteffectanimation = 0;
        }
        else
        {
            if(player1.pause == 0 && player1.gameover == 0)
            {
                player1.hiteffectanimation.currentframe++;
            }
            drawPngEx(renderer, player1.hiteffectanimation.textures, v, ChooseSprite(player1.hiteffectanimation), 0, player1.hiteffectanimation.size.x, player1.hiteffectanimation.size.y, player1.hiteffectpos.x - (player1.hiteffectanimation.size.x)/2, player1.hiteffectpos.y - (player1.hiteffectanimation.size.y)/2, 0, 0, 0, SDL_FLIP_NONE);
        }
    }
}

