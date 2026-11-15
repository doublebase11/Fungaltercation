#include "player.h"
int checkdead(int health)
{
    int dead = (health <= 0);
    return dead;
}

void dead(player &player1, player &player2)
{
    int playsound = 0; //which player sound effect to play
    int idleanimationsize = 0;
    int xpos = 0;

    if(checkdead(player1.health) && player1.dead == 0)
    {
        //log << << "player 2 wiiiiiiiiiiiiiiiiiiiiiiiiiiins" << std::endl;
        player1.dead = 1;
        player1.hitstuntimer = player1.GetTicks;
        player1.inhitstun = 1;

        playsound = player1.player;
        idleanimationsize = player1.idleanimation.size.x;
        xpos = player1.pos.x;

        player1.velocity = {0, 0};

        player1.specialmove = 1;
        player1.sporecountlimit = 500;
        player1.sporefirespeed = 125;
        player1.sporeattackduration = 950;
        player1.sporesdisappearingperframe = 0;
        player1.sporedissapearancethreshold = 70;
        player1.sporebasespeed = 1;
        player1.sporerandomizedspeed = 6;
        player1.sporespreadangle = 360;
        player1.sporespinmaxspeed = 5;
        player1.special = 1;
    }
    if(checkdead(player2.health) && player2.dead == 0)
    {
        //log << << "player 1 wiiiiiiiiiiiiiiiiiiiiiiiiiiins" << std::endl;
        player2.dead = 1;
        player2.timetospendinhitstun = 950;
        player2.hitstuntimer = player2.GetTicks;
        player2.inhitstun = 1;

        playsound = player2.player;
        idleanimationsize = player2.idleanimation.size.x;
        xpos = player2.pos.x;

        player2.velocity = {0, 0};

        player2.specialmove = 1;
        player2.sporecountlimit = 500;
        player2.sporefirespeed = 125;
        player2.sporeattackduration = 950;
        player2.sporesdisappearingperframe = 0;
        player2.sporedissapearancethreshold = 70;
        player2.sporebasespeed = 1;
        player2.sporerandomizedspeed = 6;
        player2.sporespreadangle = 360;
        player2.sporespinmaxspeed = 5;
        player2.special = 1;
    }
    if(playsound > 0) //deathsound
    {
        double pantotheright = (960 - idleanimationsize) - xpos;
        pantotheright = pantotheright/(960 - idleanimationsize);
        pantotheright*= 255; 
        if(pantotheright < 0)
        {
            pantotheright = 0;
        }
        Mix_SetPanning(7, pantotheright, 255 - pantotheright);
        if(playsound == 1)
        {
            SFX_player1death(player1);
        }    
        else
        {
            SFX_player2death(player2);
        }
    
    
    }     

    
}

void calculatePlayerCentre(player &player)
{
    player.centre = {(int)(player.pos.x + (player.idleanimation.size.x/2.0)), (int)(player.pos.y + (player.idleanimation.size.y/2.0))};
    ////log << player.centre.x << " " << player.centre.y << std::endl;
}

void hitstun(player &player1)
{
    if(player1.stunned == 0)
    {
        if((player1.GetTicks - player1.hitstuntimer) < player1.timetospendinhitstun)
        {
            player1.inhitstun = 1;
            player1.swordon = 0;
            player1.xmovementdirection = 0;
            ////log << << "in hitstun";
        }
        else
        {
            player1.inhitstun = 0;
        }
    }
}

void stun(player &player1)
{
    if(player1.stunned == 1)
    {
        player1.inhitstun = 1;
        player1.xmovementdirection = 0; 
        player1.jump = 0;
        player1.velocity = {0, 0};
        player1.swordon = 0;
    }
    else
    {
        player1.swordon = 1;
    }

}
void move(player &player1,  player &player2, int frame, stage stage) // don't look inside
{
    float gravity = 0.40; //change this someone to make jumping nicer
    int originalxpos = player1.pos.x;
    int originalypos = player1.pos.y;


    player1.xchange = 0;
    player1.ychange = 0;
    float acceleration = (player1.acceleration.x - player1.sword.weight/100);
    if(acceleration < 0.73)
    {
        acceleration = 0.73;
    }
    if(player1.dashdirection.x == 1)
    {
        if(player1.velocity.x <= player1.moveagainthreshold)
        {
            player1.dashdirection.x = 0;
        }
    }

    if(player1.dashdirection.y == 1)
    {
        if(player1.velocity.x >= -player1.moveagainthreshold)
        {
            player1.dashdirection.y = 0;
        }
    }

    if(player1.doubletap.x == 2)
    {

        player1.doubletapinitial = 1;
        
        player1.velocity.x = player1.dashvelocity;

        player1.pos.x += player1.dashdistance;
        player1.doubletapstarttime = player1.GetTicks;
        player1.doubletap.x = 1;
        player1.showdashavailable = 0;
        player1.dashdirection.x = 1;
        
    }
    else if(player1.dashdirection.x == 0)
    {                             
        
        if (player1.xmovementdirection > 0) //if right is pressed(d)
        {
            if(player1.velocity.x <  player1.terminalvelocity)
            {
                player1.velocity.x += acceleration;
                if(player1.velocity.x > player1.terminalvelocity)
                {
                    if(player1.dashdirection.x == 0)
                    {
                        player1.velocity.x = player1.terminalvelocity;
                    }
                }

            }

        }        

    }
    if(player1.doubletap.y == 2)
    {

        player1.velocity.x = -player1.dashvelocity;
        
        player1.pos.x -= player1.dashdistance;
        player1.doubletapstarttime = player1.GetTicks;
        player1.doubletap.y = 1;
        player1.showdashavailable = 0;
        //dash(player1, frame);
        player1.dashdirection.y = 1;
        
    }
    else if(player1.dashdirection.y == 0)
    {
        if(player1.xmovementdirection < 0) //if left is pressed(a)
        {
            if(player1.velocity.x >  -(player1.terminalvelocity))
            {
                player1.velocity.x -= acceleration;
                if(player1.velocity.x < -player1.terminalvelocity)
                {
                    if(player1.dashdirection.y == 0)
                    {
                        player1.velocity.x = -player1.terminalvelocity;
                    }
                }       

            }
        }
    }   

    ////log << << ((collision(calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player1.caphitbox, player1.caphitboxpos, vector2f{0, 0}, 0))) && (player2.velocity.y < player1.velocity.y) && (player2.pos.y < player1.pos.y)) << std::endl;
    if(player1.jump == 1) //jump- pretty self explanatory
    {
        if(player1.velocity.y == 0 && !((collision(calculatevertices(player2.feethitbox, player2.feethitboxpos, vector2f{0, 0}, 0), calculatevertices(player1.caphitbox, player1.caphitboxpos, vector2f{0, 0}, 0))) && (player2.velocity.y < player1.velocity.y) && (player2.pos.y < player1.pos.y))) //placeholder until floor collision
        {
            //Mix_HaltChannel(player1.player);
            SFX_jump(player1);           
        }
        player1.jump = 0; //until this
    }

    if(player1.velocity.x > 0) //deceleration????
    {
        player1.velocity.x -= 0.7;
    }
    if(player1.velocity.x < 0)
    {
        player1.velocity.x += 0.7;
    }

    if(player1.velocity.x < 1 && player1.velocity.x > -1) //bodge to correct velocity to 0.
    {
        if(player1.xmovementdirection == 0)
        {
            player1.velocity.x = 0;
        }
    }

    if(player1.fastfalling == 1 && player1.velocity.y >  -(player1.terminalvelocity)) //fastfalling
    {   
        player1.velocity.y -= player1.fastfallspeed;
    }

    if(player1.velocity.y > 12)
    {
        player1.velocity.y = 12;
    }

    stun(player1);
    if(player1.dead)
    {
        player1.velocity = {0, 0};
    }
    player1.pos.x = player1.pos.x + player1.velocity.x; //these 2 lines are what actually move the player1. The rest calculates its velocities
    player1.pos.y = player1.pos.y - player1.velocity.y;

    calculatePlayerHitboxLocations(player1);
    calculatePlayerHitboxLocations(player2);
    player1.stagecollisionstate = stageCollisions(stage, player1);

    if(player1.stagecollisionstate.y)
    {
        capCollisions(player1, player2);
    }


    calculatePlayerHitboxLocations(player1);
    capCollisions(player1, player2); 

    player1.xchange = player1.pos.x - originalxpos;
    player1.ychange = player1.pos.y - originalypos;


    if(player1.pos.x < 0 + XOFFSET)
    {
        player1.pos.x = 0 + XOFFSET;
    }
    if(player1.pos.x > 920 + XOFFSET)
    {
        player1.pos.x = 920 + XOFFSET;
    }

    {
        player1.velocity.y -= gravity; //guravity
    }

    calculatePlayerHitboxLocations(player1);
    calculatePlayerHitboxLocations(player2);
    bodyCollisions(player1, player2);
    calculatePlayerHitboxLocations(player1);
    calculatePlayerHitboxLocations(player2);
    player1.stagecollisionstate = stageCollisions(stage, player1);


    if(player1.stagecollisionstate.y)
    {
        capCollisions(player1, player2);
    }

    player1.xchange = player1.pos.x - originalxpos;
    player1.ychange = player1.pos.y - originalypos;

    ////log << player1.velocity.y << " " << player1.GetTicks << std::endl; 
}



void UpdatePlayers(player &player1, player &player2, stage stage, vector2i mouse, vector2i mouse2, int frame, SDL_Renderer* renderer, viewport &viewport, std::ofstream &log)//THE ORDER HERE IS IMPORTANT DON'T CHANGE IT PLEASE    
{
    ////log << "update players" << std::endl;
    if((player1.pause == 0)&& !(player1.gameover || player2.gameover))
    {
        if(!(frame % (player1.dead + player2.dead + 1)) && !(player1.gameover || player2.gameover))
        {
            if(player1.gamestart == 1)
            {
                if(player1.pos.y < (400 + YOFFSET))
                {
                    player1.gamestart = 0;
                    Mix_HaltChannel(7);
                }
                else
                {
                    SFX_entrance(player1.entrancesfx);
                    player1.pos.y -= 2;
                    player1.velocity.y = 0;
                    player1.doubletapstarttime = player1.GetTicks - 980;
                    
                    
                }
            }
            if(player2.gamestart == 1)
            {
                if(player2.pos.y < (400 + YOFFSET))
                {
                    player2.gamestart = 0;
                }
                else
                {
                    player2.velocity.y = 0;
                    player2.pos.y -= 2;
                    player2.doubletapstarttime = player2.GetTicks - 980;
                }
            }


            player1.originaly = player1.pos.y;
            player1.originalx = player1.pos.x;
            player2.originaly = player2.pos.y;
            player2.originalx = player2.pos.x;

            player1.swordprevrelativepos = player1.swordrelativepos;
            player2.swordprevrelativepos = player2.swordrelativepos;

            player1.swordprevpos = player1.swordpos;
            player2.swordprevpos = player2.swordpos;

            player1.prevvelocity = player1.velocity;
            player2.prevvelocity = player2.velocity;

            hitstun(player1);
            hitstun(player2);

            move(player1, player2, frame, stage); //MOVE THE PLAYERHEORHOHTIOENOFG
            player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
            player1.drawpos.y = player1.pos.y - player1.idleanimation.size.y;
            calculatePlayerHitboxLocations(player1);
            calculatePlayerHitboxLocations(player2);
            capCollisions(player1, player2); 
            calculatePlayerHitboxLocations(player1);
            calculatePlayerHitboxLocations(player2);
            player1.stagecollisionstate = stageCollisions(stage, player1);
                if(player1.stagecollisionstate.y)
                {
                    capCollisions(player1, player2);
                }            
            move(player2, player1, frame, stage); //MOVE THE PLAYERHEORHOHTIOENOFG
            player2.sworddrawpos.y = player2.swordpos.y - player2.idleanimation.size.y;
            player2.drawpos.y = player2.pos.y - player2.idleanimation.size.y;
            calculatePlayerHitboxLocations(player1);
            calculatePlayerHitboxLocations(player2);
            capCollisions(player2, player2); 
            calculatePlayerHitboxLocations(player1);
            calculatePlayerHitboxLocations(player2);
            player2.stagecollisionstate = stageCollisions(stage, player2);

                if(player2.stagecollisionstate.y)
                {
                    capCollisions(player2, player1);
                }

            calculatePlayerHitboxLocations(player1);
            calculatePlayerHitboxLocations(player2);
            chargecollisions(player1, player2);        
            calculatePlayerHitboxLocations(player1);
            calculatePlayerHitboxLocations(player2);
            chargecollisions(player2, player1);        

            player1.ychange = player1.pos.y - player1.originaly;
            player1.xchange = player1.pos.x - player1.originalx;
            player2.ychange = player2.pos.y - player2.originaly;
            player2.xchange = player2.pos.x - player2.originalx;

            calculatePlayerCentre(player1);
            calculatePlayerCentre(player2);

            broadPlayerCollisions(player1, player2); // THE EXCEPTION

            player1.cursor = FindCursorpos(mouse, player1.attackcentre, player1.centre, player1.attackradius);  
            player2.cursor = FindCursorpos(mouse2, player2.attackcentre, player2.centre, player2.attackradius);  

            player1.swordprevrotation = player1.swordrotation;
            player2.swordprevrotation = player2.swordrotation;

            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
            player1.cursorrotation = FindSwordRotation(player1.centre, player1.cursor);
            movesword(player1); //moves the sword possibly
            player2.swordrotation = FindSwordRotation(player2.centre, player2.swordpos);
            player2.cursorrotation = FindSwordRotation(player2.centre, player2.cursor);
            movesword(player2); //moves the sword possibly

            player1.swordpos.x = (int)(FindSwordpos(player1, mouse).x); //who wrote this
            player1.swordpos.y = (int)(FindSwordpos(player1, mouse).y);
            player2.swordpos.x = (int)(FindSwordpos(player2, mouse2).x); //who wrote this
            player2.swordpos.y = (int)(FindSwordpos(player2, mouse2).y);

            player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
            player1.drawpos.y = player1.pos.y - player1.idleanimation.size.y;
            player2.sworddrawpos.y = player2.swordpos.y - player2.idleanimation.size.y;
            player2.drawpos.y = player2.pos.y - player2.idleanimation.size.y;

            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
            player1.cursorrotation = FindSwordRotation(player1.centre, player1.cursor);
            player2.swordrotation = FindSwordRotation(player2.centre, player2.swordpos);
            player2.cursorrotation = FindSwordRotation(player2.centre, player2.cursor);

            shootspores(player1);
            shootspores(player2);

            chargehit(player1, player2);
            chargehit(player2, player1);

            #ifdef SWORDGROUNDCOLLISIONS

            swordtogroundcollisions(player1, stage, mouse);
            swordtogroundcollisions(player2, stage, mouse2);

            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
            player1.cursorrotation = FindSwordRotation(player1.centre, player1.cursor);
            player2.swordrotation = FindSwordRotation(player2.centre, player2.swordpos);
            player2.cursorrotation = FindSwordRotation(player2.centre, player2.cursor);

            player1.swordrelativepos.x = player1.swordpos.x - player1.centre.x;
            player1.swordrelativepos.y = player1.swordpos.y - player1.centre.y;
            player2.swordrelativepos.x = player2.swordpos.x - player2.centre.x;
            player2.swordrelativepos.y = player2.swordpos.y - player2.centre.y;

            #endif
            broadPlayerCollisions(player1, player2); // THE EXCEPTION
            if(player1.attacking != 3)
            {
                swordnotattackingcollisions(player1, player2, mouse, log);
            }
            if(player2.attacking != 3)
            {
                swordnotattackingcollisions(player2, player1, mouse2, log);
            }

            if(findknockbackdistance(player1) >  findknockbackdistance(player2))
            {
                parry(player1, player2);
            }
            else if(findknockbackdistance(player1)  <  findknockbackdistance(player2))
            {
                parry(player2, player1);
            }
            else if(abs(FindSwordRotationChange(player1))*(player1.sword.weight) >  abs(FindSwordRotationChange(player2))*(player2.sword.weight) )
            {
                parry(player1, player2);
            }
            else if(abs(FindSwordRotationChange(player1))*(player1.sword.weight)  <  abs(FindSwordRotationChange(player2))*(player2.sword.weight) )
            {
                parry(player2, player1);
            }
            else if((hypot(player1.xchange, player1.ychange))*(player1.sword.weight)  > (hypot(player2.xchange, player2.ychange))*(player2.sword.weight) )
            {
                parry(player1, player2);
            }
            else if((hypot(player1.xchange, player1.ychange))*(player1.sword.weight)  < (hypot(player2.xchange, player2.ychange))*(player2.sword.weight) )
            {
                parry(player2, player1);
            }
            resolveparry(player1);
            resolveparry(player2);

            player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
            player1.cursorrotation = FindSwordRotation(player1.centre, player1.cursor);
            player2.swordrotation = FindSwordRotation(player2.centre, player2.swordpos);
            player2.cursorrotation = FindSwordRotation(player2.centre, player2.cursor);

            player1.swordrelativepos.x = player1.swordpos.x - player1.centre.x;
            player1.swordrelativepos.y = player1.swordpos.y - player1.centre.y;
            player2.swordrelativepos.x = player2.swordpos.x - player2.centre.x;
            player2.swordrelativepos.y = player2.swordpos.y - player2.centre.y;

            float p1swordposchangex = player1.swordrelativepos.x - player1.swordprevrelativepos.x;
            float p1swordposchangey = player1.swordrelativepos.y - player1.swordprevrelativepos.y;
            player1.swordrelativeposchange = sqrt((p1swordposchangex*p1swordposchangex) + (p1swordposchangey*p1swordposchangey));
            float p2swordposchangex = player2.swordrelativepos.x - player2.swordprevrelativepos.x;
            float p2swordposchangey = player2.swordrelativepos.y - player2.swordprevrelativepos.y;
            player2.swordrelativeposchange = sqrt((p2swordposchangex*p2swordposchangex) + (p2swordposchangey*p2swordposchangey));

            calculatePlayerCentre(player1);
            calculatePlayerCentre(player2);
            

            if(swordCollisions(player1, player2, log))
            {
                player1.starthiteffectanimation = 1;
                player1.hiteffectanimation.currentframe = 1;
                player1.hiteffectpos = calculateswordplayercollisionpoint(player1, player2);
                SFX_player2getshit(player2);
                player2.stagecollisionstate = stageCollisions(stage, player2);

                swordnotattackingcollisions(player1, player2, mouse, log);

            }
            if(swordCollisions(player2, player1, log))
            {
                player2.starthiteffectanimation = 1;
                player2.hiteffectanimation.currentframe = 1;
                player2.hiteffectpos = calculateswordplayercollisionpoint(player2, player1);
                SFX_player1getshit(player1);
                player1.stagecollisionstate = stageCollisions(stage, player2);
                swordnotattackingcollisions(player2, player1, mouse2, log);

            }

                if(player2.stagecollisionstate.y)
                {
                    capCollisions(player2, player1);
                }
                if(player1.stagecollisionstate.y)
                {
                    capCollisions(player1, player2);
                }
            
            waterCollisions(stage, player1, player2);
        }


    //sound effectsssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss


    SFX_player1land(player1);
    SFX_player2land(player2);
    SFX_player1walk(player1);
    SFX_player2walk(player2);

    dead(player1, player2);

    }


    player1.drawpos.y = player1.pos.y - player1.idleanimation.size.y;
    player2.drawpos.y = player2.pos.y - player2.idleanimation.size.y;
    calculatePlayerHitboxLocations(player1);
    calculatePlayerHitboxLocations(player2);

    DrawSword(player1, renderer, viewport);
    DrawSword(player2, renderer, viewport);

    calculateSwordHitboxLocations(player1);
    calculateSwordHitboxLocations(player2);
    DrawPlayer(player1, renderer, viewport);
    if(player1.character == player2.character)
    {
        SDL_SetTextureColorMod(player2.idleanimation.textures,128, 128, 128);
        SDL_SetTextureColorMod(player2.walkanimation.textures,128, 128, 128);
        SDL_SetTextureColorMod(player2.jumpanimation.textures,128, 128, 128);
        SDL_SetTextureColorMod(player2.fallanimation.textures,128, 128, 128);
        SDL_SetTextureColorMod(player2.upperarmtexture,128, 128, 128);
        SDL_SetTextureColorMod(player2.forearmtexture,128, 128, 128);
        SDL_SetTextureColorMod(player2.jointtexture,128, 128, 128);
        DrawPlayer(player2, renderer, viewport);
        SDL_SetTextureColorMod(player2.idleanimation.textures,255, 255, 255);
        SDL_SetTextureColorMod(player2.walkanimation.textures,255, 255, 255);
        SDL_SetTextureColorMod(player2.jumpanimation.textures,255, 255, 255);
        SDL_SetTextureColorMod(player2.fallanimation.textures,255, 255, 255);
        SDL_SetTextureColorMod(player2.upperarmtexture,255, 255, 255);
        SDL_SetTextureColorMod(player2.forearmtexture,255, 255, 255);
        SDL_SetTextureColorMod(player2.jointtexture,255, 255, 255);
    }
    else
    {
        DrawPlayer(player2, renderer, viewport);
    }

    parryeffect(player1, viewport, renderer);
    parryeffect(player2, viewport, renderer);
    hiteffect(player1, viewport, renderer);
    hiteffect(player2, viewport, renderer);
    
    drawspores(player1, renderer, viewport);
    sporecollisions(player1, player2);

    drawspores(player2, renderer, viewport);
    sporecollisions(player2, player1);


    drawGroundParticles(stage, player1, renderer, viewport);
    drawGroundParticles(stage, player2, renderer, viewport);
      





}

