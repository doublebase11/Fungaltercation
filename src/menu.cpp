#include "menu.h"
#define BUTTONFLYSPEED 40
#define PAUSEBUTTONYOFFSET 120
#define CSVIEWPORTSCALE 3
#define CSVIEWPORTXOFFSET 0
#define CSVIEWPORTYOFFSET 0
#define CREDITSCREENSCROLLSPEED 1

void initialpausehandler(player &player1, player &player2, button &titlescreen, button &characterselect, button &settings)
{
    if(player1.pausepressed)
    {
        Mix_VolumeMusic(20);
        player1.pausepressed = 0;
        player2.pausepressed = 0;
        characterselect.pos = {-214, 270-PAUSEBUTTONYOFFSET};
        //settings.pos = {960, 320-PAUSEBUTTONYOFFSET};
        titlescreen.pos = {960, 320-PAUSEBUTTONYOFFSET};
        //titlescreen.pos = {-214, 370-PAUSEBUTTONYOFFSET};
    } 
}    
  
int creditscreen(int &creditsscroll, int mousedown, SDL_Texture* creditscreentexture,  SDL_Renderer* renderer)
{
    int gaming = 4;
    if(creditsscroll < 4000 - 540)
    {
        creditsscroll += CREDITSCREENSCROLLSPEED;
    }
    drawPng(renderer, creditscreentexture, 0, creditsscroll, 960, 540, 0, 0);
    if(mousedown)
    {
        gaming = 2;
    }

    return gaming;
}

int titlescreen(button play, button credits, button quitbutton, int &creditsscroll, vector2i mouse, int mousedown, SDL_Texture* titlescreentexture,  SDL_Renderer* renderer)
{
    int gaming = 2;
    Mix_HaltChannel(-1);

    drawPng(renderer, titlescreentexture, 0, 0, 960, 540, 0, 0);
    play.pos.x = 480 - play.size.x/2;
    play.pos.y = 300;

    if(createButton(play, mouse, mousedown, renderer))
    {
        //Mix_Resume(-1);  
        gaming = 0;
    }
    credits.pos.x = 480 - credits.size.x/2;
    credits.pos.y = play.pos.y + play.size.y + 0;

    if(createButton(credits, mouse, mousedown, renderer))
    {
        creditsscroll = 0;
        gaming = 4;
    }

    quitbutton.pos.x = 480 - quitbutton.size.x/2;
    quitbutton.pos.y = credits.pos.y + credits.size.y + 0;
    if(createButton(quitbutton, mouse, mousedown, renderer))
    {
        creditsscroll = 0;
        gaming = 5;
    }

    return gaming;
}

int pausemenu(button &titlescreen, button &characterselect, button &settings, vector2i mouse, int mousedown,  SDL_Renderer* renderer)
{
    int gaming = 1;
    if(abs(characterselect.pos.x-373) < BUTTONFLYSPEED)
    {
        characterselect.pos.x = 373;
        //settings.pos.x = 373;
        titlescreen.pos.x = 373;
    }
    else
    {
        characterselect.pos.x+=BUTTONFLYSPEED;
        //settings.pos.x -= BUTTONFLYSPEED;
        titlescreen.pos.x-=BUTTONFLYSPEED;
    }
        if(createButton(characterselect, mouse, mousedown, renderer))
        {
            gaming = 0;
        }
        //if(createButton(settings, mouse, mousedown, renderer))
        //{
        //    gaming = 3;
        //}
        if(createButton(titlescreen, mouse, mousedown, renderer))
        {
            gaming = 2;
        }
    return gaming;
}

void drawstagepreview(SDL_Texture* grey2, stage s, int drawx, int drawy, double ratio, SDL_Renderer* renderer)
{
    drawPng(renderer, s.background5,  0, 0, 960, 800, 0 + drawx, 400 -s.height + drawy);
    drawPng(renderer, s.background4,  0, 0, 960, 800, 0 + drawx, 400 -s.height + drawy);
    drawPng(renderer, s.background3,  0, 0, 960, 800, 0 + drawx, 400 -s.height + drawy);
    drawPng(renderer, s.background2,  0, 0, 960, 800, 0 + drawx, 400 -s.height + drawy);
    drawPng(renderer, s.background1, 0, 0, 960, 800, 0 + drawx, 400 -s.height + drawy);  
    if(s.dynamic == 1)
    {
        drawPng(renderer, s.platforms, 0, 0, 960, 540, 0 + drawx, -20 + drawy);

    }
    else
    {
        drawPng(renderer, s.platforms, 0, 0, 960, 540, 0 + drawx, 0 + drawy);

    }
    if(s.dynamic == 1)
    {
        drawPng(renderer, s.watertexture, 0, 0, 541, 23, 223 + drawx, 409 + drawy);
    }
    drawPng(renderer, s.ground, 0, 0, 960, 540, 0 + drawx, 0 + drawy);
    drawPng(renderer, grey2, 0, 0, 960, 540, 0, 0);
}

void characterselectdrawplayers(player &player1, player &player2, player &defaultplayer, player &defaultplayer2, SDL_Renderer* renderer)
{
    viewport viewport;
    viewport.scale = CSVIEWPORTSCALE;
    UpdateAnimation(defaultplayer.idleanimation, SDL_GetTicks());
    UpdateAnimation(defaultplayer2.idleanimation, SDL_GetTicks());



    if(player1.character == 1)
    {
        //player1.drawpos.y = player1.pos.y - defaultplayer.idleanimation.size.y;
        animation animation = (defaultplayer.idleanimation);
        drawPngEx(renderer, animation.textures, viewport, ChooseSprite(animation), 0, animation.size.x, animation.size.y, player1.pos.x, player1.drawpos.y, animation.size.x/2, animation.size.y/2, 0, SDL_FLIP_NONE);
    }
    else
    {
       // player1.pos.y = player1.pos.y  - defaultplayer2.idleanimation.size.y;
         animation animation = (defaultplayer2.idleanimation);
         drawPngEx(renderer, animation.textures, viewport, ChooseSprite(animation), 0, animation.size.x, animation.size.y, player1.pos.x-5, player1.drawpos.y, animation.size.x/2, animation.size.y/2, 0, SDL_FLIP_NONE);
    }

    if(player2.character == 1)
    {
        //player2.drawpos.y = player2.pos.y - defaultplayer.idleanimation.size.y;
        animation animation = (defaultplayer.idleanimation);
        drawPngEx(renderer, animation.textures, viewport, ChooseSprite(animation), 0, animation.size.x, animation.size.y, player2.pos.x, player2.drawpos.y, animation.size.x/2, animation.size.y/2, 0, SDL_FLIP_HORIZONTAL);
    }
    else
    {
       // player2.drawpos.y = player2.pos.y - defaultplayer2.idleanimation.size.y;
         animation animation = (defaultplayer2.idleanimation);
         drawPngEx(renderer, animation.textures, viewport, ChooseSprite(animation), 0, animation.size.x, animation.size.y, player2.pos.x-5, player2.drawpos.y, animation.size.x/2, animation.size.y/2, 0, SDL_FLIP_HORIZONTAL);
    }



}

void characterselectdrawswords(int p1sword, int p2sword, sword sword1, sword sword2, sword sword3, sword sword4, player &player1, player &player2, player& defaultplayer, vector2i mouse, vector2i mouse2, SDL_Renderer* renderer)
{
    viewport viewport;
    viewport.scale = CSVIEWPORTSCALE;

    calculatePlayerCentre(player1);
    calculatePlayerCentre(player2);
   
        player1.swordpos =  FindCursorpos(mouse, player1.attackcentre, player1.centre, 20);
        player2.swordpos =  FindCursorpos(mouse2, player2.attackcentre, player2.centre, 20);

        player1.swordrotation = FindSwordRotation(player1.centre, player1.swordpos);
        player2.swordrotation = FindSwordRotation(player2.centre, player2.swordpos);  

        player1.sworddrawpos.y = player1.swordpos.y - player1.idleanimation.size.y;
        player2.sworddrawpos.y = player2.swordpos.y - player2.idleanimation.size.y;



    calculateSwordHitboxLocations(player1);
    calculateSwordHitboxLocations(player2);   
    drawPlayerArm(player1, renderer, viewport);
    drawPlayerArm(player2, renderer, viewport);
    
    
    ////log << << player1.centre.x << ", " << player1.centre.y << std::endl;

            if(p1sword == 1)
            {
                player1.sworddrawpos.y -= (sword1.size.y*1);
                drawPngEx(renderer, sword1.texture1, viewport, 0, 0, sword1.size.x, sword1.size.y,  player1.swordpos.x,player1.sworddrawpos.y, sword1.handle.x, sword1.handle.y, player1.swordrotation, SDL_FLIP_NONE);
            }
            else if(p1sword == 2)
            {
                player1.sworddrawpos.y -= (sword2.size.y*1);
                drawPngEx(renderer, sword2.texture1, viewport, 0, 0, sword2.size.x, sword2.size.y, player1.swordpos.x, player1.sworddrawpos.y, sword2.handle.x, sword2.handle.y, player1.swordrotation, SDL_FLIP_NONE);             
            }
            else if(p1sword == 3)
            {       
                player1.sworddrawpos.y -= (sword3.size.y*1);
                drawPngEx(renderer, sword3.texture1, viewport, 0, 0, sword3.size.x, sword3.size.y, player1.swordpos.x, player1.sworddrawpos.y, sword3.handle.x, sword3.handle.y, player1.swordrotation, SDL_FLIP_NONE);             
            }
            else
            {
                player1.sworddrawpos.y -= (sword4.size.y*1);
                drawPngEx(renderer, sword4.texture1, viewport, 0, 0, sword4.size.x, sword4.size.y, player1.swordpos.x, player1.sworddrawpos.y, sword4.handle.x, sword4.handle.y, player1.swordrotation, SDL_FLIP_NONE);
            }
                

            if(p2sword == 1)
            {
                player2.sworddrawpos.y -= (sword1.size.y*1);
                drawPngEx(renderer, sword1.texture1, viewport, 0, 0, sword1.size.x, sword1.size.y, player2.swordpos.x, player2.sworddrawpos.y, sword1.handle.x, sword1.handle.y, player2.swordrotation, SDL_FLIP_NONE);  
            }
            else if(p2sword == 2)
            {
                player2.sworddrawpos.y -= (sword2.size.y*1);
                drawPngEx(renderer, sword2.texture1, viewport, 0, 0, sword2.size.x, sword2.size.y, player2.swordpos.x, player2.sworddrawpos.y, sword2.handle.x, sword2.handle.y, player2.swordrotation, SDL_FLIP_NONE);                  
            }
            else if(p2sword == 3)
            {       
                player2.sworddrawpos.y -= (sword3.size.y*1);
                drawPngEx(renderer, sword3.texture1, viewport, 0, 0, sword3.size.x, sword3.size.y, player2.swordpos.x, player2.sworddrawpos.y, sword3.handle.x, sword3.handle.y, player2.swordrotation, SDL_FLIP_NONE); 
            }
            else
            {
                player2.sworddrawpos.y -= (sword4.size.y*1);
                drawPngEx(renderer, sword4.texture1, viewport, 0, 0, sword4.size.x, sword4.size.y, player2.swordpos.x, player2.sworddrawpos.y, sword4.handle.x, sword4.handle.y, player2.swordrotation, SDL_FLIP_NONE);                
            }


        
}

void swordselect(int &p1sword, int &p2sword, int &changed, button larrowbutton, button rarrowbutton, vector2i mouse, vector2i mouse2, int mousedown, int mouse2down, SDL_Renderer* renderer)
{
    larrowbutton.pos = {200, 200 + larrowbutton.size.y + 10};
    rarrowbutton.pos.y = 200 + larrowbutton.size.y + 10;
    rarrowbutton.pos.x = larrowbutton.pos.x + larrowbutton.size.x;
    if(createButton(larrowbutton, mouse, mousedown, renderer)) //PLAYER 1 SWORD SELECT
    {
        changed = 1;
        p1sword++;

        if(p1sword > 4)
        {
            p1sword = 1;
        }
    }
    if(createButton(rarrowbutton, mouse, mousedown, renderer))
    {
        changed = 1;
        p1sword--;

        if(p1sword < 1)
        {
            p1sword = 4;
        }
    }


    larrowbutton.pos.x = 660;
    rarrowbutton.pos.x = larrowbutton.pos.x + larrowbutton.size.x;
    if(createButton(larrowbutton, mouse2, mouse2down, renderer)) //PLAYER 2 SWORD SELECT
    {
        changed = 1;
        p2sword++;
        if(p2sword > 4)
        {
            p2sword = 1;
        }
    }
    if(createButton(rarrowbutton, mouse2, mouse2down, renderer)) //PLAYER 2 SWORD SELECT
    {
        changed = 1;
        p2sword--;
        if(p2sword < 1)
        {
            p2sword = 4;
        }
    }
}

void characterselect(player &player1, player &player2, int &changed, button larrowbutton, button rarrowbutton, vector2i mouse, vector2i mouse2, int mousedown, int mouse2down, SDL_Renderer* renderer)
{
    larrowbutton.pos = {200, 200};
    rarrowbutton.pos.y = 200;
    rarrowbutton.pos.x = larrowbutton.pos.x + larrowbutton.size.x;

    if(createButton(larrowbutton, mouse, mousedown, renderer)) //PLAYER 1 CHARACTER SELECT
    {
        changed = 1;
        if(player1.character == 1)
        {
            player1.character = 2;
        }
        else
        {
            player1.character = 1;
        }
    }
    if(createButton(rarrowbutton, mouse, mousedown, renderer)) //PLAYER 1 CHARACTER SELECT
    {
        changed = 1;
        if(player1.character == 1)
        {
            player1.character = 2;
        }
        else
        {
            player1.character = 1;
        }
    }

    larrowbutton.pos.x = 660;
    rarrowbutton.pos.x = larrowbutton.pos.x + larrowbutton.size.x;
    if(createButton(larrowbutton, mouse2, mouse2down, renderer)) //PLAYER 2 CHARACTER SELECT
    {
        changed = 1;
        if(player2.character == 1)
        {
            player2.character = 2;
        }
        else
        {
            player2.character = 1;
        }

    }
    if(createButton(rarrowbutton, mouse2, mouse2down, renderer)) //PLAYER 2 CHARACTER SELECT
    {
        changed = 1;
        if(player2.character == 1)
        {
            player2.character = 2;
        }
        else
        {
            player2.character = 1;
        }

    }
}

int characterselect(SDL_Texture* grey2, player &player1, player &player2, player &defaultplayer, player &defaultplayer2, sword sword1, sword sword2, sword sword3, sword sword4, stage &currentstage, stage stage1, stage stage2, vector2i mouse, vector2i mouse2, int mousedown, int mouse2down, button ccbutton, button playbutton, button larrowbutton, button rarrowbutton, SDL_Renderer* renderer, viewport &v)
{
    ////log << << mousedown << std::endl;
    Mix_HaltChannel(-1);
    viewport viewport;
    drawstagepreview(grey2, currentstage, 0, 100, 0.3, renderer);
    //viewport.scale = 3;
    int changed = 0;

    if(player1.dead || player2.dead)
    {
        changed = 1;
    }

    int p1sword = player1.sword.sword;
    int p2sword = player2.sword.sword;
    


    player1.pos.x = 62;
    player1.pos.y = 67;
    player2.pos.x = 215;
    player2.pos.y = 67;


    //log << << player1.pos.x << " " << player1.pos.y << " | " << player2.pos.x << " " << player2.pos.y << std::endl;
    if(player1.character == 1)
    {
        player1.drawpos.y = player1.pos.y - defaultplayer.idleanimation.size.y;
    }
    else
    {
        player1.drawpos.y = player1.pos.y - defaultplayer2.idleanimation.size.y;
    }

    if(player2.character == 1)
    {
        player2.drawpos.y = player2.pos.y - defaultplayer.idleanimation.size.y;
    }
    else
    {
        player2.drawpos.y = player2.pos.y - defaultplayer2.idleanimation.size.y;
    }

    characterselectdrawswords(p1sword, p2sword, sword1, sword2, sword3, sword4, player1, player2, defaultplayer, mouse, mouse2, renderer);
    characterselectdrawplayers(player1, player2, defaultplayer, defaultplayer2, renderer);
    characterselect(player1, player2, changed, larrowbutton, rarrowbutton, mouse, mouse2, mousedown, mouse2down, renderer);
    swordselect(p1sword, p2sword, changed, larrowbutton, rarrowbutton, mouse, mouse2, mousedown, mouse2down, renderer);


    

    
    ////log << << currentstage.stage << std::endl;

    button ccbutton3 = ccbutton;
    //ccbutton3.offtexture = currentstage.background1;
    ccbutton3.pos.x = 480 - ccbutton3.size.x/2;
    ccbutton3.pos.y = 200;
    if(createButton(ccbutton3, mouse, mousedown, renderer)) //STAGE SWITCHING BUTTON
    {
        changed = 1;
        if(currentstage.stage == 1)
        {
            currentstage.stage = 2;
            ////log << << "2" << std::endl;
        }
        else
        {
            currentstage.stage = 1;
            ////log << << "1" << std::endl;
        }        
    }





        //SWITCH EVERYTHING
        int play = 0;
        playbutton.pos.x = 480 - playbutton.size.x/2;
        playbutton.pos.y = ccbutton3.pos.y + ccbutton3.size.y + 10;
        //playbutton.pos.y = 200 + larrowbutton.size.y + 10;
        play = createButton(playbutton, mouse, mousedown, renderer);
        if(play)
        {
            changed = 1;
        }
        vector2i p1prevattackcentre= player1.attackcentre;
        vector2i p2prevattackcentre = player2.attackcentre;
        vector2i p1prevswordlocation = player1.swordpos;
        vector2i p1prevdrawswordlocation = player1.sworddrawpos;
        vector2i p2prevswordlocation = player2.swordpos;
        vector2i p2prevdrawswordlocation = player2.sworddrawpos;
        double p1prevswordrotation = player1.swordrotation;
        double p2prevswordrotation = player2.swordrotation;

        if(changed == 1)
        {
            

            if(currentstage.stage == 1)
            {
                currentstage = stage1;
            }
            else
            {
                currentstage = stage2;
            }

            if(player2.character == 1)
            {
                player2 = defaultplayer;
            }
            else
            {
                player2 = defaultplayer2;
            }
            if(player1.character == 1)
            {
                player1 = defaultplayer;
            }
            else
            {
                player1 = defaultplayer2;
            }
            
            //sword switching
            if(p1sword == 1)
            {
                player1.sword = sword1;
            }
            else if(p1sword == 2)
            {
                player1.sword = sword2;
            }
            else if(p1sword == 3)
            {       
                player1.sword = sword3;
            }
            else
            {
                player1.sword = sword4;
            }
                

            if(p2sword == 1)
            {
                player2.sword = sword1;
            }
            else if(p2sword == 2)
            {
                player2.sword = sword2;
            }
            else if(p2sword == 3)
            {       
                player2.sword = sword3;
            }
            else
            {
                player2.sword = sword4;
            }

            player2.pos.x = 820 + XOFFSET;
            player2.flip = SDL_FLIP_HORIZONTAL;

                 player1.attackcentre = p1prevattackcentre;
                 player2.attackcentre = p2prevattackcentre;
            //player1.swordpos = p1prevswordlocation;
            //player1.sworddrawpos = p1prevdrawswordlocation ;
            //player2.swordpos = p2prevswordlocation ;
            //player2.sworddrawpos = p2prevdrawswordlocation;
            // player1.swordrotation = p1prevswordrotation;
            //player2.swordrotation = p2prevswordrotation ;

            //set sound effects and particles depending on the stage
            assignsoundeffectstoplayers(currentstage, player1, player2);
            assignparticlestoplayers(currentstage, player1, player2);
            Mix_Resume(-1); 

        }       



        return play;

}

int settingsmenu(button ccbutton, vector2i mouse, int mousedown,  SDL_Renderer* renderer, HANDLE &m1, HANDLE &m2, RAWINPUTDEVICELIST *&pRawInputDeviceList)
{
    int gaming = 3;
    if(createButton(ccbutton, mouse, mousedown, renderer))
    {
        setupmiceinput(m1, m2, pRawInputDeviceList);
    }

    ccbutton.pos.x = 800;
    if(createButton(ccbutton, mouse, mousedown, renderer))
    {
        Mix_Resume(-1);  
        gaming = 1;
    }
    return gaming;
}