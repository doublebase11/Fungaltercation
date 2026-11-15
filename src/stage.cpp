#include "stage.h"
#define GROUNDPARTICLEFIRESPEED 3
#define GROUNDPARTICLERANDOMIZEDSPEED 3
#define GROUNDPARTICLEBASESPEED 3
#define GROUNDPARTICLESPREADANGLE 170

#define SPOREPARTICLERANDOMIZEDSPEED 3
#define SPOREPARTICLEBASESPEED 1
#define SPOREPARTICLESPREADANGLE 0
#define SPOREPARTICLEANGLE 90

#define LEAFPARTICLERANDOMIZEDSPEED 2
#define LEAFPARTICLEBASESPEED 1
#define LEAFPARTICLESPREADANGLE 0
#define LEAFPARTICLEANGLE 90

void drawStageLeafParticles(stage &s, int pause, int gameover,  SDL_Renderer* renderer, viewport &viewport)
{
    
    int leafspawnstartx = 0 + XOFFSET;
    int leafspawnendx = 960 + XOFFSET;

        //for(int i = 0; i < ; i ++)
        if(pause == 0)
        {
            if(s.leafparticles.particlespresent < s.leafparticles.maxparticles)
            {
              ////log << << "add" << std::endl;
              int postotake = 0;
              while(s.leafparticles.enabled[postotake] == 1)
              {
                postotake++;
              }
              s.leafparticles.enabled[postotake] = 1;

              float ratio = ((rand()%99));
                ratio += 1;
                ratio/=100;
    
              s.leafparticles.particlelocations[postotake] = {(int)(lerp(leafspawnstartx, leafspawnendx, ratio)), YOFFSET - 100};

              float addvelocity = (rand()%100);
              addvelocity = addvelocity/100;
              addvelocity = addvelocity*LEAFPARTICLERANDOMIZEDSPEED;
              float anglevariance = (rand()%100);
              anglevariance = anglevariance/100;
              anglevariance = anglevariance*LEAFPARTICLESPREADANGLE;
              if((rand()%2) == 0)
              {
                  anglevariance = -anglevariance;
              }
                double angler =  (anglevariance+LEAFPARTICLEANGLE)* 3.14159265;

              angler = angler/180; //converts player.swordrotation to radians
              s.leafparticles.velocity[postotake] = {0,-(sin(angler) *(LEAFPARTICLEBASESPEED+addvelocity))};
              //s.leafparticles.chosenspriteindex[postotake] =  (rand()%(s.leafparticles.maxparticles)) + 1;
              s.leafparticles.particleanimationchosen[postotake] = (rand()%3);
              s.leafparticles.chosenspriteindex[postotake] = 1;
              s.leafparticles.particlespresent++;

            }
        }

        ////log << << (s.leafparticles.particlelocations[1].x - XOFFSET) << ", " << (s.leafparticles.particlelocations[i].y - YOFFSET) << std::endl;

        for(int i = 0; i < s.leafparticles.maxparticles; i++)
        {
            //move leaf
            if(s.leafparticles.enabled[i] == 1)
            {
              if(pause == 0 && gameover == 0)
              {
                  //s.leafparticles.particlelocations[i].x +=  s.leafparticles.velocity[i].x;
                  s.leafparticles.particlelocations[i].y -=  s.leafparticles.velocity[i].y;
                  if((rand()%5) == 0)
                  {
                    s.leafparticles.chosenspriteindex[i]++;
                    if(s.leafparticles.chosenspriteindex[i] > 5)
                    {
                      s.leafparticles.chosenspriteindex[i] = 1;
                    }
                  }
              }  
  
              s.leafparticleanimations[s.leafparticles.particleanimationchosen[i]].currentframe = s.leafparticles.chosenspriteindex[i];
  
              int shouldntdrawparticle = (s.leafparticles.particlelocations[i].y > (YOFFSET + 420));
              if(shouldntdrawparticle)
              {
                
                
                s.leafparticles.particlespresent--;
                s.leafparticles.enabled[i] = 0;
              }
              else
              {
                
                  drawPngEx(renderer, s.leafparticleanimations[s.leafparticles.particleanimationchosen[i]].textures, viewport, ChooseSprite(s.leafparticleanimations[s.leafparticles.particleanimationchosen[i]]), 0, s.leafparticleanimations[s.leafparticles.particleanimationchosen[i]].size.x, s.leafparticleanimations[s.leafparticles.particleanimationchosen[i]].size.y, s.leafparticles.particlelocations[i].x, s.leafparticles.particlelocations[i].y, 0, 0, 0, SDL_FLIP_NONE);
              }
            }
        }
}

void drawStageSporeParticles(stage &s, int pause, int gameover,  SDL_Renderer* renderer, viewport &viewport)
{
    
    int sporespawnstartx = 54 + XOFFSET;
    int sporespawnendx = 890 + XOFFSET;

        for(int i = 0; i < 2; i ++)
        {
            if(s.sporeparticles.particlespresent < s.sporeparticles.maxparticles)
            {
              ////log << << "add" << std::endl;
              int postotake = 0;
              while(s.sporeparticles.enabled[postotake] == 1)
              {
                postotake++;
              }
              s.sporeparticles.enabled[postotake] = 1;

              float ratio = ((rand()%99));
                ratio += 1;
                ratio/=100;
    
              s.sporeparticles.particlelocations[postotake] = {(int)(lerp(sporespawnstartx, sporespawnendx, ratio)), 850 + YOFFSET};

              float addvelocity = (rand()%100);
              addvelocity = addvelocity/100;
              addvelocity = addvelocity*SPOREPARTICLERANDOMIZEDSPEED;
              float anglevariance = (rand()%100);
              anglevariance = anglevariance/100;
              anglevariance = anglevariance*SPOREPARTICLESPREADANGLE;
              if((rand()%2) == 0)
              {
                  anglevariance = -anglevariance;
              }
                double angler =  (anglevariance+SPOREPARTICLEANGLE)* 3.14159265;

              angler = angler/180; //converts player.swordrotation to radians
              s.sporeparticles.velocity[postotake] = {0,(sin(angler) *(SPOREPARTICLEBASESPEED+addvelocity))};
              s.sporeparticles.chosenspriteindex[postotake] =  (rand()%(s.sporeparticles.maxparticles)) + 1;
              s.sporeparticles.particlespresent++;

            }
        }

        ////log << << (s.sporeparticles.particlelocations[1].x - XOFFSET) << ", " << (s.sporeparticles.particlelocations[i].y - YOFFSET) << std::endl;

        for(int i = 0; i < s.sporeparticles.maxparticles; i++)
        {
            //move spore
            if(s.sporeparticles.enabled[i] == 1)
            {
              if(pause == 0 && gameover == 0)
              {
                  //s.sporeparticles.particlelocations[i].x +=  s.sporeparticles.velocity[i].x;
                  s.sporeparticles.particlelocations[i].y -=  s.sporeparticles.velocity[i].y;
              }  
  
              s.sporeparticles.particleanimation.currentframe = s.sporeparticles.chosenspriteindex[i];
  
              int shouldntdrawparticle = (s.sporeparticles.particlelocations[i].y < (YOFFSET - 30));
              //shouldntdrawparticle = 0;
              if(shouldntdrawparticle)
              {
                
                
                s.sporeparticles.particlespresent--;
                s.sporeparticles.enabled[i] = 0;
              }
              else
              {
                
                  drawPngEx(renderer, s.sporeparticles.particleanimation.textures, viewport, ChooseSprite(s.sporeparticles.particleanimation), 0, s.sporeparticles.particleanimation.size.x, s.sporeparticles.particleanimation.size.y, s.sporeparticles.particlelocations[i].x, s.sporeparticles.particlelocations[i].y, 0, 0, 0, SDL_FLIP_NONE);
              }
            }
        }
}

void drawGroundParticles(stage s, player &player, SDL_Renderer* renderer, viewport &viewport)
{
    if(player.pause == 0)
    {
        for(int i = 1; i < (GROUNDPARTICLEFIRESPEED +1); i++)
        {
            if(player.groundparticles.particlespresent < player.groundparticles.maxparticles && player.gamestart == 1) //create new spore
            {
                ////log << << "add" << std::endl;
                int particlexstart = (rand()%player.idleanimation.size.x);    
                player.groundparticles.pos[player.groundparticles.particlespresent] = {(int)(particlexstart + player.pos.x), (int)(401 + YOFFSET)};
                float addvelocity = (rand()%100);
                addvelocity = addvelocity/100;
                addvelocity = addvelocity*GROUNDPARTICLERANDOMIZEDSPEED;
                float anglevariance = (rand()%100);
                anglevariance = anglevariance/100;
                anglevariance = anglevariance*GROUNDPARTICLESPREADANGLE;
                if(player.GetTicks%2 == 0)
                {
                    anglevariance = -anglevariance;
                }
                double angler =  (anglevariance+90)* 3.14159265;
                angler = angler/180; //converts player.swordrotation to radians
                player.groundparticles.velocity[player.groundparticles.particlespresent] = {(-cos(angler)*(GROUNDPARTICLEBASESPEED+addvelocity)),(sin(angler) *(GROUNDPARTICLEBASESPEED+addvelocity))};
                player.groundparticles.chosenspriteindex[player.groundparticles.particlespresent] =  (rand()%6) + 1;
                player.groundparticles.particlespresent++;
            }
        }
    }
        
        for(int i = 0; i < player.groundparticles.particlespresent; i++)
        {
            //move spore
            if(player.pause == 0)
            {
                if(abs( player.groundparticles.velocity[i].x) < 0.1)
                {
                     player.groundparticles.velocity[i].x =  player.groundparticles.velocity[i].x/10;
                }
                if(abs( player.groundparticles.velocity[i].y) < 0.1)
                {
                     player.groundparticles.velocity[i].y = 0;
                }
                player.groundparticles.pos[i].x +=  player.groundparticles.velocity[i].x;
                player.groundparticles.pos[i].y -=  player.groundparticles.velocity[i].y;
                ////log << << player.sporevelocity.x << " " << player.sporevelocity.y << std::endl;
                if( player.groundparticles.velocity[i].x > 0) //deceleration????
                {
                     player.groundparticles.velocity[i].x -= 0.1;
                }
                if( player.groundparticles.velocity[i].x < 0)
                {
                     player.groundparticles.velocity[i].x += 0.1;
                }
                if( player.groundparticles.velocity[i].y > 0) //deceleration????
                {
                     player.groundparticles.velocity[i].y -= 0.1;
                }
                if( player.groundparticles.velocity[i].y < 0)
                {
                     player.groundparticles.velocity[i].y += 0.1;
                } 
            }  

            player.groundparticles.particleanimation.currentframe = player.groundparticles.chosenspriteindex[i];

            int shouldntdrawparticle = (player.groundparticles.pos[i].y < (370 + YOFFSET)) || (hypot(player.groundparticles.velocity[i].x, player.groundparticles.velocity[i].y) < 0.2);
            if(!shouldntdrawparticle)
            {
                drawPngEx(renderer, player.groundparticles.particleanimation.textures, viewport, ChooseSprite(player.groundparticles.particleanimation), 0, 6, 6, player.groundparticles.pos[i].x, player.groundparticles.pos[i].y, 0, 0, 0, SDL_FLIP_NONE);
            }
        }

        //if(player.groundparticles.particlespresent == GROUNDPARTICLEFIRESPEED)
        //{
        //    player.groundparticles.particlespresent = 0;
        //}


    ////log << << player.groundparticles.particlespresent << std ::endl;
}

void waterCollisions(stage s, player &player1, player &player2)
{
    player1.watercollision = 0;
    player2.watercollision = 0;

    if(s.dynamic == 1)
    {  
        float speedthreshhold = 1;
        float speedreduction = 0.9;
        if(player1.pos.y > (410+YOFFSET))
        {
            player1.watercollision = 1;
            ////log << << player1.pos.y << std::endl;
            if(abs(player1.velocity.x) > speedthreshhold)
            {
                player1.velocity.x*=speedreduction;
            }
        }
        if(player2.pos.y > (410+YOFFSET))
        {
            player2.watercollision = 1;
            if(abs(player2.velocity.x) > speedthreshhold)
            {
                player2.velocity.x*=speedreduction;
            }
        }
    }
}

void drawStageWater(stage s, SDL_Renderer* renderer, viewport v)
{
    if(s.dynamic == 1)
    {
        drawPngEx(renderer, s.watertexture, v, 0, 0, 541, 23, 223 + XOFFSET, 409 + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
    }
}

viewport parallaxscroll(viewport v, float magnitude)
{
    viewport vnew = v;
    int vnewcentrex = lerp(XOFFSET + 480, v.pos.x + (v.size.x/2), magnitude);
    vnew.pos.x = vnewcentrex - (v.size.x/2);
    return vnew;
}

void drawStageBackground(stage &s, int pause, int gameover,   SDL_Renderer* renderer, viewport v)
{

    viewport v2 = parallaxscroll(v, 1.2);
    viewport v3 = parallaxscroll(v, 1);
    viewport v4 = parallaxscroll(v, 1);
    viewport v5 = parallaxscroll(v, 1);




    drawPngEx(renderer, s.background5, v, 0, 0, 960, 800, 0 + XOFFSET, 400 -s.height + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
    drawPngEx(renderer, s.background4, v, 0, 0, 960, 800, 0 + XOFFSET, 400 -s.height + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, s.background4, v, 0, 0, 960, 800, -960 + XOFFSET, 400 -s.height + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
    drawPngEx(renderer, s.background3, v, 0, 0, 960, 800, 0 + XOFFSET, 400 -s.height + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
    //drawPngEx(renderer, s.background3, v, 0, 0, 960, 800, -960 + XOFFSET, 400 -s.height + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
    if(s.stage == 1)
    {
        drawStageSporeParticles(s, pause, gameover,  renderer, v);
    }
    drawPngEx(renderer, s.background2, v, 0, 0, 960, 800, 0 + XOFFSET, 400 -s.height + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
    if(s.stage == 1)
    {
        drawStageLeafParticles(s, pause, gameover,  renderer, v);
    }
    drawPngEx(renderer, s.background1, v, 0, 0, 960, 800, 0 + XOFFSET, 400 -s.height + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);

    

    
}

void drawStagePlatforms(stage s, SDL_Renderer* renderer, viewport v)
{
    if(s.dynamic == 1)
    {
        drawPngEx(renderer, s.platforms, v, 0, 0, 960, 540, 0 + XOFFSET, -20 + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);

    }
    else
    {
        drawPngEx(renderer, s.platforms, v, 0, 0, 960, 540, 0 + XOFFSET, 0 + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);

    }
    
}

void drawStageGround(stage s, SDL_Renderer* renderer, viewport v)
{
    drawPngEx(renderer, s.ground, v, 0, 0, 960, 540, 0 + XOFFSET, 0 + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
    drawPngEx(renderer, s.ground, v, 0, 0, 960, 540, -960 + XOFFSET, 0 + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
}


void drawStageForeground(stage s, SDL_Renderer* renderer, viewport v)
{
    drawPngEx(renderer, s.foreground, v, 0, 0, 960, 540, 0 + XOFFSET, 0 + YOFFSET, 0, 0, 0, SDL_FLIP_NONE);
}

void calculateplatformcentres(stage &s)
{
    for(int i = 0; i < (s.hitboxnumber); i++) //loops through each platform
    {
        s.platformcentres[i] = { s.hpos[i].x + ((s.h[i].v3.x)/2), s.hpos[i].y + ((s.h[i].v3.y)/2)};
    }
    for(int i = 0; i < (s.hitboxnumber); i++) //loops through each platform
    {
        //log << << s.platformcentres[i].x << " " << s.platformcentres[i].y << std::endl;
    }
}

void initstage(stage &s, viewport &v)
{
    //calculateplatformcentres(s);
    //v.ycameraoffset = s.ycameraoffset;

}
