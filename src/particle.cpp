#include "particle.h"
#define WALKPARTICLEFIRESPEED 10
#define WALKPARTICLERANDOMIZEDSPEED 0
#define WALKPARTICLEBASESPEED 5
#define WALKPARTICLESPREADANGLE 15
#define WALKPARTICLEDECELSPEED 0.2
#define WALKPARTICLEANGLE 20


void drawWalkParticles(player &player, SDL_Renderer* renderer, viewport viewport)
{

    for(int i = 1; i < (WALKPARTICLEFIRESPEED +1); i++)
    {
      if((player.velocity.x != 0) && (player.velocity.y == 0) && (player.dashdirection.x == 0) && (player.dashdirection.y == 0))
      {
        if(player.walkparticles.particlespresent < player.walkparticles.maxparticles)
        {
          ////log << << "add" << std::endl;
          int postotake = 0;
          while(player.walkparticles.enabled[postotake] == 1)
          {
            postotake++;
          }
          player.walkparticles.enabled[postotake] = 1;
          //player.walkparticles.particlelocations[postotake] = vector2i{player.pos.x, player.pos.y-player.walkparticles.particleanimation.size.y};
          //player.walkparticles.particlestarttime[postotake] = player.GetTicks;

          int particlexstart = (rand()%player.idleanimation.size.x);    
          player.walkparticles.particlelocations[postotake] = {(int)(player.pos.x + particlexstart), player.pos.y};
          float addvelocity = (rand()%100);
          addvelocity = addvelocity/100;
          addvelocity = addvelocity*WALKPARTICLERANDOMIZEDSPEED;
          float anglevariance = (rand()%100);
          anglevariance = anglevariance/100;
          anglevariance = anglevariance*WALKPARTICLESPREADANGLE;
          if(player.GetTicks%2 == 0)
          {
              anglevariance = -anglevariance;
          }
          double angler = 0;
          if(player.flip == SDL_FLIP_HORIZONTAL)
          {
            angler =  (anglevariance+180-WALKPARTICLEANGLE)* 3.14159265;
          }
          else
          {
            angler =  (anglevariance+WALKPARTICLEANGLE)* 3.14159265;
          }
          angler = angler/180; //converts player.swordrotation to radians
          player.walkparticles.velocity[postotake] = {(-cos(angler)*(WALKPARTICLEBASESPEED+addvelocity)),(sin(angler) *(WALKPARTICLEBASESPEED+addvelocity))};
          player.walkparticles.chosenspriteindex[postotake] =  (rand()%(player.walkparticles.maxparticles)) + 1;
          player.walkparticles.particlespresent++;

        }

      }
    }


        for(int i = 0; i < player.walkparticles.maxparticles; i++)
        {
            //move spore
            if(player.walkparticles.enabled[i] == 1)
            {
              if(player.pause == 0)
              {
                  if(abs(player.walkparticles.velocity[i].x) < WALKPARTICLEDECELSPEED )
                  {
                       player.walkparticles.velocity[i].x =  player.walkparticles.velocity[i].x/10;
                  }
                  if(abs(player.walkparticles.velocity[i].y) < WALKPARTICLEDECELSPEED )
                  {
                       player.walkparticles.velocity[i].y = 0;
                  }
                  player.walkparticles.particlelocations[i].x +=  player.walkparticles.velocity[i].x;
                  player.walkparticles.particlelocations[i].y -=  player.walkparticles.velocity[i].y;



                  if( player.walkparticles.velocity[i].x > 0) //deceleration????
                  {
                       player.walkparticles.velocity[i].x -= WALKPARTICLEDECELSPEED ;
                  }
                  if( player.walkparticles.velocity[i].x < 0)
                  {
                       player.walkparticles.velocity[i].x += WALKPARTICLEDECELSPEED ;
                  }
                  if( player.walkparticles.velocity[i].y > 0) //deceleration????
                  {
                       player.walkparticles.velocity[i].y -= WALKPARTICLEDECELSPEED ;
                  }
                  if( player.walkparticles.velocity[i].y < 0)
                  {
                       player.walkparticles.velocity[i].y += WALKPARTICLEDECELSPEED ;
                  } 
              }  
  
              player.walkparticles.particleanimation.currentframe = player.walkparticles.chosenspriteindex[i];
  
              int shouldntdrawparticle = (hypot(player.walkparticles.velocity[i].x, player.walkparticles.velocity[i].y) < 1);
              //shouldntdrawparticle = 0;
              if(shouldntdrawparticle)
              {
                player.walkparticles.particlespresent--;
                player.walkparticles.enabled[i] = 0;
              }
              else
              {
                ////log << << (player.walkparticles.particlelocations[i].x - XOFFSET) << ", " << (player.walkparticles.particlelocations[i].y - YOFFSET) << std::endl;
                  drawPngEx(renderer, player.walkparticles.particleanimation.textures, viewport, ChooseSprite(player.walkparticles.particleanimation), 0, player.walkparticles.particleanimation.size.x, player.walkparticles.particleanimation.size.y, player.walkparticles.particlelocations[i].x, player.walkparticles.particlelocations[i].y, 0, 0, 0, SDL_FLIP_NONE);
              }
            }
        }

}

void drawDashparticles(player &player, SDL_Renderer* renderer, viewport viewport)
{

      player.drawpos.y = player.pos.y - player.idleanimation.size.y;

    for(int i = 0; i < player.dashparticles.maxparticles; i++)
    {
      if(player.dashparticles.enabled[i] == 1)
      {
        if(((player.GetTicks - player.dashparticles.particlestarttime[i]) > 300))
        {
          if((std::rand() % 2))
          {
            player.dashparticles.enabled[i] = 0;
            player.dashparticles.particlespresent--;
          }
        }
      }
    }

    if((player.velocity.y == 0) && ((player.dashdirection.x == 1) || (player.dashdirection.y == 1)))
    {
      if(player.dashparticles.particlespresent < player.dashparticles.maxparticles)
      {
        int postotake = 0;
        while(player.dashparticles.enabled[postotake] == 1)
        {
          postotake++;
        }
        player.dashparticles.enabled[postotake] = 1;
        if(player.flip == SDL_FLIP_HORIZONTAL)
        {
        player.dashparticles.particlelocations[postotake] = vector2i{(int)(player.pos.x+player.relativefeethitboxpos.x+player.feethitbox.v2.x), player.pos.y-player.dashparticles.particleanimation.size.y};
        }
        else
        {
        player.dashparticles.particlelocations[postotake] = vector2i{player.pos.x, player.pos.y-player.dashparticles.particleanimation.size.y};
        }

        player.dashparticles.particlestarttime[postotake] = player.GetTicks;
        player.dashparticles.particlespresent++;

      }

    }


     
    for(int i = 0; i < player.dashparticles.maxparticles; i++)
    {
      
      if(player.dashparticles.enabled[i] == 1)
      {
        if(std::rand() % 2)
        {
          if(player.dashparticles.particleanimation.currentframe == player.dashparticles.particleanimation.maxframes)
          {
              player.dashparticles.particleanimation.currentframe = 1;
          }
          else
          {
              player.dashparticles.particleanimation.currentframe++;
          }
        }
        drawPngEx(renderer, player.dashparticles.particleanimation.textures, viewport, ChooseSprite(player.dashparticles.particleanimation), 0, player.dashparticles.particleanimation.size.x, player.dashparticles.particleanimation.size.y, player.dashparticles.particlelocations[i].x, player.dashparticles.particlelocations[i].y, player.dashparticles.particleanimation.size.x/2, player.walkparticles.particleanimation.size.y/2, 0, player.flip);
      }
    } 

}