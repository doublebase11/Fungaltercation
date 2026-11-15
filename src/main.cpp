#include "input.h"
#include "characterlist.h"
#include "stagelist.h"
#include "menu.h"
#include <time.h>

player defaultplayer;
player defaultplayer2;

sword zwig;
sword bigsword;
sword boringsword;
sword dagger;

stage grass;
stage sewer;

player player1;
player player2;

button ccbutton;
button quitbutton;
button larrowbutton;
button rarrowbutton;
button titlescreenbutton;
button characterselectbutton;
button settingsbutton;
button playbutton;
button creditsbutton;
button playbutton2;

viewport v;
viewport v2;
viewport v3;

HANDLE m1;
HANDLE m2;
RAWINPUTDEVICELIST *pRawInputDeviceList;

int main(int argv, char ** args)
{
    //create log
    std::ofstream log;
    log.open("log.txt");
    //log << "start" << std::endl;

    srand(time(0));
    setupmiceinput(m1, m2, pRawInputDeviceList);

    v.pos.x =  XOFFSET;

    const int JOYSTICK_DEAD_ZONE = 8000;
    int quit = 0;
    int frame = 0;
    int gaming = 2;
    int mousedown = 0;
    int mouse2down = 0;

    int deathscreenx = -760; 
    int creditsscroll = 0;

    //mouse
    int m1leftdown = 0;
    int m1rightdown = 0;
    int m2leftdown = 0;
    int m2rightdown = 0;
    //

    vector2i mouse2keyboarddirection = {0, 0};

    int pausetime = 0;
    int totalpausetime = 0;
    int logoxpos = -94;

    vector2i mouse = {0, 0}; //mouse coordinates
    vector2i mouse2 = {0, 0}; //mouse 2 coordinate

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    Mix_Volume(-1, 60);
    Mix_VolumeMusic(50);

    SDL_Window * window = SDL_CreateWindow("Fungaltercation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_SHOWN);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Texture* load = loadTexture(renderer, "sprites/load.png");
    drawPng(renderer, load, 0, 0, 960, 540, 0, 0);
    

    Mix_Music* titlescreenmusic = Mix_LoadMUS( "music/titlescreen.wav" );
    Mix_Music* creditscreenmusic = Mix_LoadMUS( "music/credits.wav" );
    Mix_Music* gamemusic = Mix_LoadMUS( "music/Don't mess with a Fun Guy.wav" );
    Mix_Music* characterselectmusic = Mix_LoadMUS( "music/A Fun Guy Like Me.wav" );

    SDL_Texture* pausedot = loadTexture(renderer, "sprites/reddot.png");
    SDL_Texture* greendot = loadTexture(renderer, "sprites/greendot.png");
    SDL_Texture* reddot = loadTexture(renderer, "sprites/realreddot.png");
    SDL_Texture* healthbar = loadTexture(renderer, "sprites/healthbar3.png");
    SDL_Texture* hollowspecialmovebar = loadTexture(renderer, "sprites/hollowspecialmovebar.png");
    SDL_Texture* deathscreen = loadTexture(renderer, "sprites/winner.png");
    SDL_Texture* deathscreen2 = loadTexture(renderer, "sprites/winner2.png");   
    SDL_Texture* p1cursor = loadTexture(renderer, "sprites/p1cursor.png"); 
    SDL_Texture* p2cursor = loadTexture(renderer, "sprites/p2cursor.png"); 
    SDL_Texture* grey = loadTexture(renderer, "sprites/grey.png"); 
    SDL_Texture* grey2 = loadTexture(renderer, "sprites/grey2.png"); 
    SDL_Texture* titlescreentexture = loadTexture(renderer, "sprites/titlescreen.png"); 
    SDL_Texture* creditscreentexture = loadTexture(renderer, "sprites/credits.png"); 
    SDL_Texture* logo = loadTexture(renderer, "sprites/logo.png"); 
    createplayers(defaultplayer, defaultplayer2, renderer);
    createSwords(zwig, bigsword, boringsword, dagger, renderer);
    createstages(grass, sewer, renderer);

    stage currentstage = grass;

    SDL_Joystick* gGameController = SDL_JoystickOpen(0);
    if( gGameController == NULL )
    {
        //printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
    }
    
    if (gGameController) {
        //printf("Opened Joystick 0\n");
        //printf("Name: %s\n", SDL_JoystickNameForIndex(3));
        //printf("Number of Axes: %d\n", SDL_JoystickNumAxes(gGameController));
        //printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(gGameController));
        //printf("Number of Balls: %d\n", SDL_JoystickNumBalls(gGameController));
    }



    SDL_Event event;

    SDL_SetRelativeMouseMode(SDL_TRUE);

    initplayers(player1, player2, defaultplayer, defaultplayer);
    addSwords(player1, player2, zwig, zwig, renderer);
    assignsoundeffectstoplayers(currentstage, player1, player2);
    assignparticlestoplayers(currentstage, player1, player2);
    SetYCameraOffset(currentstage, v);

    //buttons
    creditsbutton.offtexture = loadTexture(renderer, "sprites/buttons/creditsoff.png");
    creditsbutton.ontexture = loadTexture(renderer, "sprites/buttons/creditson.png");
    creditsbutton.size = {214, 40};
    creditsbutton.pos = {200, 200};

    playbutton2.offtexture = loadTexture(renderer, "sprites/buttons/playoff2.png");
    playbutton2.ontexture = loadTexture(renderer, "sprites/buttons/playon2.png");
    playbutton2.size = {449, 90};
    playbutton2.pos = {200, 200};

    ccbutton.offtexture = loadTexture(renderer, "sprites/buttons/stageoff.png");
    ccbutton.ontexture = loadTexture(renderer, "sprites/buttons/stageon.png");
    ccbutton.size = {214, 40};
    ccbutton.pos = {200, 200};

    playbutton.offtexture = loadTexture(renderer, "sprites/buttons/playoff.png");
    playbutton.ontexture = loadTexture(renderer, "sprites/buttons/playon.png");
    playbutton.size = {214, 50};
    playbutton.pos = {200, 200};

    quitbutton.offtexture = loadTexture(renderer, "sprites/buttons/quitoff.png");
    quitbutton.ontexture = loadTexture(renderer, "sprites/buttons/quiton.png");
    quitbutton.size = {214, 50};
    quitbutton.pos = {200, 200};

    larrowbutton.offtexture = loadTexture(renderer, "sprites/buttons/larrowoff.png");
    larrowbutton.ontexture = loadTexture(renderer, "sprites/buttons/larrowon.png");
    larrowbutton.size = {47, 56};
    larrowbutton.pos = {200, 200};

    rarrowbutton.offtexture = loadTexture(renderer, "sprites/buttons/rarrowoff.png");
    rarrowbutton.ontexture = loadTexture(renderer, "sprites/buttons/rarrowon.png");
    rarrowbutton.size = {47, 56};
    rarrowbutton.pos = {200, 200};

    titlescreenbutton.offtexture = loadTexture(renderer, "sprites/buttons/mmoff.png");
    titlescreenbutton.ontexture = loadTexture(renderer, "sprites/buttons/mmon.png");
    titlescreenbutton.size = {214, 40};
    titlescreenbutton.pos = {0, 200};

    settingsbutton.offtexture = loadTexture(renderer, "sprites/buttons/settingsoff.png");
    settingsbutton.ontexture = loadTexture(renderer, "sprites/buttons/settingson.png");
    settingsbutton.size = {214, 40};
    settingsbutton.pos = {0, 223};

    characterselectbutton.offtexture = loadTexture(renderer, "sprites/buttons/characterselectoff.png");
    characterselectbutton.ontexture = loadTexture(renderer, "sprites/buttons/characterselecton.png");
    characterselectbutton.size = {214, 40};
    characterselectbutton.pos = {0, 246};
    //

    vector2i cursor = {0, 0};
    SDL_SetRenderDrawColor(renderer,255,255,255, 255);
    
    while(quit == 0)
    {
        SDL_RenderClear(renderer);      
        miceinput(mouse.x, mouse.y, m1leftdown, m1rightdown, mouse2.x, mouse2.y, m2leftdown, m2rightdown, m1, m2, gaming, player1, player2);
        if(logoxpos == -94)
        {         
            miceclicks(m1leftdown, m1rightdown, m2leftdown, m2rightdown, player1, player2);
        }
        else
        {
            
            if(abs(logoxpos+94) < 100)
            {
                logoxpos = -94;
            }
            else
            {
                logoxpos +=100;
            }

        }

            if(mousedown == -1)
            {
                mousedown = 0;
            }    
            if(!m1leftdown)
            {
                if(mousedown == 1)
                {
                    mousedown = -1;
                }
            }
            else if(m1leftdown)
            {
                if (mousedown < 1)
                {
                  mousedown = 1;
                }
            }

            if(mouse2down == -1)
            {
                mouse2down = 0;
            }    
            if(!m2leftdown)
            {
                if(mouse2down == 1)
                {
                    mouse2down = -1;
                }
            }
            else if(m2leftdown)
            {
                if (mouse2down < 1)
                {
                  mouse2down = 1;
                }
            }   

        HandleInput(event, quit, gaming, mousedown, mouse, mouse2, mouse2keyboarddirection, gGameController, player1, player2, pausetime, totalpausetime, m1, m2, pRawInputDeviceList, v, window);  
        
        mouse2.x += 3*mouse2keyboarddirection.x;
        mouse2.y -= 3*mouse2keyboarddirection.y;
        
        if(player1.pause == 0)
        {
            player1.GetTicks = SDL_GetTicks() - totalpausetime;
            player2.GetTicks = SDL_GetTicks() - totalpausetime;
        }
 

        if(gaming == 1)
        {
            if(checkdeathscreen(player1, player2))
            {
                deathscreenx = -760;
            }
            
            if(!player1.pause)
            {
                SDL_SetRelativeMouseMode(SDL_TRUE);
            }
            if(player1.gameover && (m1leftdown || m2leftdown))
            {
                if(gaming == 1)
                {
                    gaming = 0;
                    Mix_HaltMusic();
                    Mix_VolumeMusic(50);

                    Mix_PlayMusic(characterselectmusic, -1 );
                }

            }

            
            game(player1, player2, currentstage, mouse, mouse2, renderer, v, v2, v3, pausedot, reddot, greendot, hollowspecialmovebar, healthbar, frame, log); //we game 
            if(player1.pause == 0)
            {
                if(player1.dead)
                {
                    showdeathscreen(player1.gameover, deathscreenx, renderer, deathscreen2);
                }
                else if(player2.dead)
                {
                    showdeathscreen(player1.gameover, deathscreenx, renderer, deathscreen);
                }
            }
            

            if(player1.pause)
            {

                drawPng(renderer, grey, 0, 0, 960, 540, 0, 0);
        
                lockCursor(mouse);
                initialpausehandler(player1, player2, titlescreenbutton, characterselectbutton, settingsbutton);
                gaming = pausemenu(titlescreenbutton, characterselectbutton, settingsbutton, mouse, mousedown, renderer);  
                if(gaming == 2)
                {
                    Mix_HaltMusic();
                    Mix_VolumeMusic(50);
                }
                else if(gaming == 0)
                {
                    Mix_HaltMusic();
                    Mix_VolumeMusic(50);

                    Mix_PlayMusic(characterselectmusic, -1 );
            
                }
                drawPng(renderer, p1cursor, 0, 0, 9, 9, mouse.x, mouse.y);
            }
            else
            {
                SDL_WarpMouseInWindow(window, 480, 270);
            }
        } 
        
        else if(gaming == 0) //character select
        {
            lockCursor(mouse);
            lockCursor(mouse2);
            player1.pause = 0;
            player2.pause = 0; 
            
            gaming = (characterselect(grey2, player1, player2, defaultplayer, defaultplayer2, zwig, bigsword, boringsword, dagger, currentstage, grass, sewer, mouse, mouse2, mousedown, mouse2down, ccbutton, playbutton, larrowbutton, rarrowbutton, renderer, v));
            if(gaming == 1)
            {
                Mix_Resume(-1);  
                viewport m;
                m.pos.x =  XOFFSET;
                v = m;
                player1.player = 1;
                player2.player = 2;
                SetYCameraOffset(currentstage, v);
                Mix_HaltMusic();
                if( Mix_PlayingMusic() == 0 )
                {
                    Mix_PlayMusic( gamemusic, -1 );
                }

                }
                drawPng(renderer, p1cursor, 0, 0, 9, 9, mouse.x, mouse.y);
                drawPng(renderer, p2cursor, 0, 0, 9, 9, mouse2.x, mouse2.y);
            
        }
        else if(gaming == 2) //title screen
        {
            if( Mix_PlayingMusic() == 0 )
            {
                Mix_PlayMusic( titlescreenmusic, -1 );
            }

            lockCursor(mouse);
            lockCursor(mouse2);
            player1.pause = 0;
            player2.pause = 0;  
            gaming = titlescreen(playbutton2, creditsbutton, quitbutton, creditsscroll, mouse, mousedown, titlescreentexture, renderer);
            drawPng(renderer, logo, 0, 0, 1200, 320, logoxpos, 0);
            //std::cout <<   -102 + mouse.x << std::endl;
            drawPng(renderer, p1cursor, 0, 0, 9, 9, mouse.x, mouse.y);
            if(gaming == 4)
            {
                Mix_HaltMusic();
                if( Mix_PlayingMusic() == 0 )
                {
                    Mix_PlayMusic( creditscreenmusic, 0);
                }
            }
            if(gaming == 0)
            {
                Mix_HaltMusic();
                Mix_PlayMusic(characterselectmusic, -1 );
            }



        }
        else if(gaming == 3) //settings
        {
            lockCursor(mouse);
            lockCursor(mouse2);
            gaming = settingsmenu(ccbutton, mouse, mousedown, renderer, m1, m2, pRawInputDeviceList);
            drawPng(renderer, p1cursor, 0, 0, 9, 9, mouse.x, mouse.y);
            drawPng(renderer, p2cursor, 0, 0, 9, 9, mouse2.x, mouse2.y);
        }
        else if(gaming == 4)
        {

            mouse = {50, 50};
            gaming = creditscreen(creditsscroll, mousedown, creditscreentexture, renderer);
            if(gaming == 2)
            {
                Mix_HaltMusic();
            }
        }
        else if(gaming == 5)
        {
            quit = 1;
        }



        if(player1.changedcharacter == 1) //reset button
        {
            //log << << "reset" << std::endl;
            Mix_Resume(-1);  
            initplayers(player1, player2, defaultplayer, defaultplayer2);
            addSwords(player1, player2, zwig, zwig, renderer);
            //initstage(currentstage);
            assignsoundeffectstoplayers(currentstage, player1, player2);
            assignparticlestoplayers(currentstage, player1, player2);
            viewport m;
            m.pos.x =  XOFFSET;
            v = m;
            SetYCameraOffset(currentstage, v);
            player1.changedcharacter = 0;
        }
        


        SDL_RenderPresent(renderer);
        frame++;
    }

    Mix_FreeMusic(titlescreenmusic);
    Mix_FreeMusic(gamemusic);   
    Mix_CloseAudio();
    Mix_Quit();
    SDL_JoystickClose( gGameController );
    gGameController = NULL;
    SDL_DestroyWindow(window);
    

    log.close();

    SDL_Quit();
    return 0;
}