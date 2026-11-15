#include "ingameui.h"

void drawDashTimers(player &player1, player &player2, viewport v, SDL_Renderer* renderer)
{

    if((player1.showdashavailable == 0) && ((player1.GetTicks - player1.doubletapstarttime) > player1.doubletaptimelimit))
    {
        player1.showdashavailable = 1;
        player1.dashrechargeanimation.currentframe = 1;
    }
    if((player2.showdashavailable == 0) && ((player2.GetTicks - player2.doubletapstarttime) > player2.doubletaptimelimit))
    {
        player2.showdashavailable = 1;
        player2.dashrechargeanimation.currentframe = 1;
    }


    if(player1.showdashavailable == 1)
    {
        ////log << << ChooseSprite(player1.dashrechargeanimation) << std::endl;
        if(player1.dashrechargeanimation.currentframe == 45)
        {
            player1.showdashavailable = 2;
        }
        else
        {
            if(player1.pause == 0)
            {
                player1.dashrechargeanimation.currentframe++;
            }
            if(player1.velocity.y == 0 || player1.stagecollisionstate.y == 1 || player1.gamestart == 1 || (player1.pos.y + player1.dashrechargeanimation.size.y) > (400 + YOFFSET))
            {
                drawPngEx(renderer, player1.dashrechargeanimation.textures, v, ChooseSprite(player1.dashrechargeanimation), 0, player1.dashrechargeanimation.size.x, player1.dashrechargeanimation.size.y, player1.pos.x- (player1.dashrechargeanimation.size.x - player1.idleanimation.size.x)/2, player1.drawpos.y - player1.dashrechargeyoffset, 0, 0, 0, SDL_FLIP_NONE);
            }
            else
            {
                drawPngEx(renderer, player1.dashrechargeanimation.textures, v, ChooseSprite(player1.dashrechargeanimation), 0, player1.dashrechargeanimation.size.x, player1.dashrechargeanimation.size.y, player1.pos.x- (player1.dashrechargeanimation.size.x - player1.idleanimation.size.x)/2, player1.pos.y + 3, 0, 0, 0, SDL_FLIP_NONE);
            }
        }
    }

    if(player2.showdashavailable == 1)
    {
        ////log << << ChooseSprite(player1.dashrechargeanimation) << std::endl;
        if(player2.dashrechargeanimation.currentframe == 45)
        {
            player2.showdashavailable = 2;
        }
        else
        {
            if(player2.pause == 0)
            {
                player2.dashrechargeanimation.currentframe++;
            }
            if(player2.velocity.y == 0 || player2.stagecollisionstate.y == 1 || player2.gamestart == 1 || (player2.pos.y + player2.dashrechargeanimation.size.y) > (400 + YOFFSET))
            {
                drawPngEx(renderer, player2.dashrechargeanimation.textures, v, ChooseSprite(player2.dashrechargeanimation), 0, player2.dashrechargeanimation.size.x, player2.dashrechargeanimation.size.y, player2.pos.x- (player2.dashrechargeanimation.size.x - player2.idleanimation.size.x)/2, player2.drawpos.y - player2.dashrechargeyoffset, 0, 0, 0, SDL_FLIP_NONE);
            }
            else
            {
                drawPngEx(renderer, player2.dashrechargeanimation.textures, v, ChooseSprite(player2.dashrechargeanimation), 0, player2.dashrechargeanimation.size.x, player2.dashrechargeanimation.size.y, player2.pos.x- (player2.dashrechargeanimation.size.x - player2.idleanimation.size.x)/2, player2.pos.y + 3, 0, 0, 0, SDL_FLIP_NONE);
            }
        }
    }

}

void drawHealthBars(player &player1, player &player2, SDL_Texture* dot, SDL_Texture* healthbar, SDL_Renderer* renderer)
{
    int offset = 714;
    float ratio1 = player1.health;
    ratio1 = ((float)player1.health/200);

    float ratio2 = player2.health;
    ratio2 = ((float)player2.health/200);

    viewport ui; 

    int method1 = 0; //determines whether the health bar is read or green
    int method2 = 0;


    int ulength1 = (ratio1 * 215)+4;
    if(ulength1 > 215)
    {
        ulength1 = 215;
    }

    int ulength2 = (ratio2 * 215)+4;
    if(ulength2 > 215)
    {
        ulength2 = 215;
    }

    if(ratio1 < 0.33) //healthbar turns red under 20% of total health
    {
        method1 = 33;
    }
    if(ratio2 < 0.33)
    {
        method2 = 33;
    }

    //draw health bars
    drawPngEx(renderer, healthbar, ui, 0, 66, (215), 33, offset, 15, 0, 0, 0, SDL_FLIP_NONE);
    drawPngEx(renderer, healthbar, ui, 0, 66, (215), 33, 30, 15, 0, 0, 0, SDL_FLIP_NONE);
    if(ratio2 != 0)
    {
        drawPngEx(renderer, healthbar, ui, 0, method2+99, ulength2, 33, offset, 15, 0, 0, 0, SDL_FLIP_NONE);
    }
    if(ratio1 != 0)
    {
        drawPngEx(renderer, healthbar, ui, 0, method1+99, ulength1 , 33, 30, 15, 0, 0, 0, SDL_FLIP_NONE);
    }

    drawPngEx(renderer, healthbar, ui, 0, method2, (ratio2 * 215), 33, offset, 15, 0, 0, 0, SDL_FLIP_NONE);
    drawPngEx(renderer, healthbar, ui, 0, method1, (ratio1 * 215), 33, 30, 15, 0, 0, 0, SDL_FLIP_NONE);

}

void drawspecialmovecooldowntimers(player &player1, player &player2, SDL_Texture* greendot, SDL_Texture* reddot, SDL_Texture* blackdot, SDL_Texture* hollowspecialmovebar, stage s, SDL_Renderer* renderer)
{
    //special move bar
    viewport ui;
    double ratio = (player1.GetTicks-player1.specialstarttime);
    ratio = ratio/(player1.specialcooldown);
    if(ratio > 0.95)
    {
        ratio = 1;
        player1.specialstarttime = -7000;
    }
    

    if(player1.specialmove == 1)
    {
        //drawPngEx(renderer, blackdot, ui, 0, 0, (ratio * 215), 10, 30, 49, 0, 0, 0, SDL_FLIP_NONE);
        if(ratio == 1)
        {
            drawpartcircle(264, 31, 15, ratio, greendot, ui, renderer);
        }
        else
        {
            drawpartcircle(264, 31, 15, ratio, blackdot, ui, renderer);
        }
    }
    else if(player1.specialmove == 2)
    {
        if(ratio == 1)
        {
            //drawPngEx(renderer, greendot, ui, 0, 0, (ratio * 215), 10, 30, 49, 0, 0, 0, SDL_FLIP_NONE);
            drawpartcircle(264, 31, 15, ratio, greendot, ui, renderer);
        }
        else if(player1.charge == 1)
        {
            //drawPngEx(renderer, reddot, ui, 0, 0, (ratio * 215), 10, 30, 49, 0, 0, 0, SDL_FLIP_NONE);
            drawpartcircle(264, 31, 15, ratio, reddot, ui, renderer);
        }
        else if(player1.charge == 2)
        {
            //drawPngEx(renderer, blackdot, ui, 0, 0, (ratio * 215), 10, 30, 49, 0, 0, 0, SDL_FLIP_NONE);
            drawpartcircle(264, 31, 15, ratio, blackdot, ui, renderer);
        }
    }

    drawPngEx(renderer, hollowspecialmovebar, ui, 0, 0, 35, 34, 33 + 215 + -2, 15, 0, 0, 0, SDL_FLIP_NONE);
//
    ////player 2 special move bar
    ratio = (player2.GetTicks-player2.specialstarttime);
    ratio = ratio/(player2.specialcooldown);
    if(ratio > 0.95)
    {
        ratio = 1;
        player2.specialstarttime = -5000;
    }
    
//
//
    if(player2.specialmove == 1)
    {
        //drawPngEx(renderer, blackdot, ui, 0, 0, (ratio * 215), 10, 30, 49, 0, 0, 0, SDL_FLIP_NONE);
        if(ratio == 1)
        {
            drawpartcircle(696, 30, 15, ratio, greendot, ui, renderer);
        }
        else
        {
            drawpartcircle(696, 30, 15, ratio, blackdot, ui, renderer);
        }
    }
    else if(player2.specialmove == 2)
    {
        if(ratio == 1)
        {
            //drawPngEx(renderer, greendot, ui, 0, 0, (ratio * 215), 10, 30, 49, 0, 0, 0, SDL_FLIP_NONE);
            drawpartcircle(697, 30, 15, ratio, greendot, ui, renderer);
        }
        else if(player2.charge == 1)
        {
            //drawPngEx(renderer, reddot, ui, 0, 0, (ratio * 215), 10, 30, 49, 0, 0, 0, SDL_FLIP_NONE);
            drawpartcircle(697, 30, 15, ratio, reddot, ui, renderer);
        }
        else if(player2.charge == 2)
        {
            //drawPngEx(renderer, blackdot, ui, 0, 0, (ratio * 215), 10, 30, 49, 0, 0, 0, SDL_FLIP_NONE);
            drawpartcircle(697, 30, 15, ratio, blackdot, ui, renderer);
        }
    }

    drawPngEx(renderer, hollowspecialmovebar, ui, 0, 0, 35, 34, 681 + -3, 15, 0, 0, 0, SDL_FLIP_NONE);
}