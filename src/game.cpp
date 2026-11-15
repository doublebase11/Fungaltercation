//#define DEBUGIMAGES
#include "game.h"

int checkdeathscreen(player &player1, player &player2)
{
    int deathscreen = 0;
    if(player1.dead && !player1.inhitstun && !player1.gameover)
    {
    
        player1.gameover = 1;
        player2.gameover = 1;
        player1.pausexmovementdirection = player1.xmovementdirection; 
        player2.pausexmovementdirection = player2.xmovementdirection; 
        deathscreen = 1;
    }
    else if(player2.dead && !player2.inhitstun && !player2.gameover)
    {
    
        player2.gameover = 1;
        player1.gameover = 1;
        player1.pausexmovementdirection = player1.xmovementdirection; 
        player2.pausexmovementdirection = player2.xmovementdirection; 
        deathscreen = 1;
        
    }
    
    return deathscreen;
}  

void showdeathscreen(int gameover, int &deathscreenx, SDL_Renderer* renderer, SDL_Texture* deathscreen)
{
    if(gameover)
    {
        drawPng(renderer, deathscreen, 0, 0, 960, 540, deathscreenx, 0);
        deathscreenx += 20;
        if(deathscreenx > 0)
        {
            deathscreenx = 0;
        }
    }
}

void game(player &player1, player &player2, stage &stage, vector2i mouse, vector2i mouse2, SDL_Renderer* renderer, viewport &v, viewport &v2, viewport &v3, SDL_Texture* dot, SDL_Texture* reddot, SDL_Texture* greendot, SDL_Texture* hollowspecialmovebar, SDL_Texture* healthbar, int frame, std::ofstream &log)
{

    UpdateViewport(v, player1, player2, stage);



    drawStageBackground(stage, player1.pause, player1.gameover, renderer, v);    
    drawStagePlatforms(stage, renderer, v);   
    UpdatePlayers(player1, player2, stage, mouse, mouse2, frame, renderer, v, log);
    ////log << << checkdead(player2.health) << std::endl;
    if(player1.gameover == 0)
    {
        if(player1.pause == 0)
        {
            drawWalkParticles(player1, renderer, v);
            drawWalkParticles(player2, renderer, v);
            drawDashparticles(player1, renderer, v);
            drawDashparticles(player2, renderer, v);
        }
    }



    drawStageWater(stage, renderer, v);      
    drawStageGround(stage, renderer, v);   
    drawStageForeground(stage, renderer, v); 

    

    //ui
    if(player1.dead == 0 && player2.dead == 0)
    {
        drawDashTimers(player1, player2, v, renderer);
        drawHealthBars(player1, player2, greendot, healthbar, renderer);
        drawspecialmovecooldowntimers(player1, player2, greendot, reddot, dot, hollowspecialmovebar, stage, renderer);
    }

    #ifdef DEBUGIMAGES
    //debug

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
    
    
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordtip.x, swordtip.y, 10, 10, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordhilt.x, swordhilt.y, 10, 10, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordprevtip.x, swordprevtip.y, 10, 10, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordprevhilt.x, swordprevhilt.y, 10, 10, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordmidtip.x, swordmidtip.y, 10, 10, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordmidhilt.x, swordmidhilt.y, 10, 10, 0, SDL_FLIP_NONE);
//
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordq1tip.x, swordq1tip.y, 10, 10, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordq1hilt.x, swordq1hilt.y, 10, 10, 0, SDL_FLIP_NONE);
//
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordq3tip.x, swordq3tip.y, 10, 10, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordq3hilt.x, swordq3hilt.y, 10, 10, 0, SDL_FLIP_NONE);


    //vector2f hand = calculatehandtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, player1.sword.size, player1.swordrotation);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, hand.x, hand.y, 10, 10, 0, SDL_FLIP_NONE); 
    //for(int i = 1; i <= 360; i++)
    //{
    //        vector2f swordtip = calculateswordtippos(player1.sword.tiphitbox.v2, player1.sword.tiphitboxpos, player1.sword.handle, player1.sword.relativetiphitboxpos, i);
    //vector2f swordhilt = calculateswordhiltpos(player1.sword.bladehitbox.v3, player1.sword.bladehitboxpos, player1.sword.handle, player1.sword.relativebladehitboxpos, i);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordtip.x, swordtip.y, 10, 10, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, greendot, v, 0, 0, 2, 2, swordhilt.x, swordhilt.y, 10, 10, 0, SDL_FLIP_NONE);
//
    //}
    
    //for(int i = 0; i < (stage.hitboxnumber); i++) //loops through each platform
    //{
    //    drawPngEx(renderer, dot, v, 0, 0, 5, 5, stage.platformcentres[i].x, stage.platformcentres[i].y, 3, 3, 0, SDL_FLIP_NONE);
    //}
    
    viewport ui;

    //vector2f tip = calculatevertices(player1.sword.tiphitbox, player1.sword.tiphitboxpos, vector2f{(float)(player1.sword.handle.x - player1.sword.relativetiphitboxpos.x), (float)(player1.sword.handle.y - player1.sword.relativetiphitboxpos.y)}, player1.swordrotation).v1; 
    //if(knockbackdirection.horv == 0)
    //{
    //    ////log << << 11 << std::endl;
    //    for(int i = 0; i < 900; i++)
    //    {
    //        drawPngEx(renderer, dot, v, 0, 0, 2, 2, (tip.x+i), (knockbackdirection.g*((tip.x+i) - tip.x) + tip.y), 10, 10, 0, SDL_FLIP_NONE);
    //        drawPngEx(renderer, dot, v, 0, 0, 2, 2, (tip.x-i), (knockbackdirection.g*((tip.x-i) - tip.x) + tip.y), 10, 10, 0, SDL_FLIP_NONE);
    //    }
    //}
//int player1centrey = (int)(player1.drawpos.y + (player1.idleanimation.size.y/2.0));
//int player1centrex = (int)(player1.pos.x + (player1.idleanimation.size.x/2.0));

    vector2f collisionpoint = calculateswordplayercollisionpoint(player1, player2);
    drawPngEx(renderer, dot, v, 0, 0, 5, 5,collisionpoint.x, collisionpoint.y, 3, 3, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, dot, v, 0, 0, 5, 5, tip.x + (player2centrey-tip.y)/knockbackdirection.g, player2centrey, 3, 3, 0, SDL_FLIP_NONE);
//
    ////log << << knockbackdirection.g << std::endl;
//
    ////attack circle
    //drawPngEx(renderer, dot, ui, 0, 0, 5, 5, player1.attackcentre.x, player1.attackcentre.y, 3, 3, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, dot, ui, 0, 0, 5, 5, player1.attackcentre.x + player1.attackradius, player1.attackcentre.y, 3, 3, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, dot, ui, 0, 0, 5, 5, player1.attackcentre.x - player1.attackradius, player1.attackcentre.y, 3, 3, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, dot, ui, 0, 0, 5, 5, player1.attackcentre.x, player1.attackcentre.y + player1.attackradius, 3, 3, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, dot, ui, 0, 0, 5, 5, player1.attackcentre.x, player1.attackcentre.y - player1.attackradius, 3, 3, 0, SDL_FLIP_NONE);



//swordpos?
//vector2i egh =PointCentreTranslationVector(mouse, player1.attackcentre, player1.centre);
//drawPngEx(renderer, dot, v, 0, 0, 5, 5, egh.x, egh.y, 3, 3, 0, SDL_FLIP_NONE);

//player 2 centre

//int player2centrex = (int)(player2.pos.x + (player2.idleanimation.size.x/2.0));
//drawPngEx(renderer, dot, v, 0, 0, 5, 5, player2centrex, player2centrey, 3, 3, 0, SDL_FLIP_NONE);

//player 1 centre

//drawPngEx(renderer, dot, v, 0, 0, 5, 5, player1centrex, player1centrey, 3, 3, 0, SDL_FLIP_NONE);

//player1 swordpos
//drawPngEx(renderer, dot, v, 0, 0, 5, 5, player1.swordpos.x, player1.sworddrawpos.y, 3, 3, 0, SDL_FLIP_NONE);

    #endif


}