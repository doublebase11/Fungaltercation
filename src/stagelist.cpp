#include "stagelist.h"

void createstages(stage &grass, stage &sewer, SDL_Renderer * renderer)
{

    sewer.stage = 2;
    sewer.dynamic = 1;
    sewer.ycameraoffset = 25;

    sewer.background1 = loadTexture(renderer, "stages/darkandevilstage/Background1.png");
    sewer.background2 = loadTexture(renderer, "stages/darkandevilstage/Background2.png");
    sewer.background3 = loadTexture(renderer, "stages/darkandevilstage/Background3.png");
    //sewer.background4 = loadTexture(renderer, "stages/darkandevilstage/foreground.png");
    //sewer.background5 = loadTexture(renderer, "stages/darkandevilstage/foreground.png");

    sewer.platforms = loadTexture(renderer, "stages/darkandevilstage/platforms.png");
    sewer.ground = loadTexture(renderer, "stages/darkandevilstage/ground.png");
    sewer.foreground = loadTexture(renderer, "stages/darkandevilstage/foreground.png" );
    sewer.watertexture = loadTexture(renderer, "stages/darkandevilstage/water.png" );

    sewer.height = 800-30; 
    sewer.hitboxnumber = 9;

    sewer.h[0] = {{0, 0}, {229, 0}, {229, 141}, {0, 141}};
    sewer.h[1] = {{0, 0}, {502, 0}, {502, 123}, {0, 123}};
    sewer.h[2] = {{0, 0}, {288, 0}, {288, 141}, {0, 141}};

    sewer.h[3] = {{0, 0}, {151, 0}, {151, 9}, {0, 9}};
    sewer.h[4] = {{0, 0}, {105, 0}, {105, 8}, {0, 8}};
    sewer.h[5] = {{0, 0}, {37, 0}, {37, 8}, {0, 8}};

    sewer.h[6] = {{0, 0}, {128, 0}, {128, 9}, {0, 9}};
    sewer.h[7] = {{0, 0}, {105, 0}, {105, 8}, {0, 8}};
    sewer.h[8] = {{0, 0}, {57, 0}, {57, 8}, {0, 8}};
    
    sewer.hpos[0] = {0 + XOFFSET, 399 + YOFFSET };
    sewer.hpos[1] = {229 + XOFFSET,416 + YOFFSET};
    sewer.hpos[2] = {731 + XOFFSET,399 + YOFFSET};

    sewer.hpos[3] = {285 + XOFFSET,295 + YOFFSET- 19};
    sewer.hpos[4] = {296 + XOFFSET,304 + YOFFSET- 19};
    sewer.hpos[5] = {343 + XOFFSET,312 + YOFFSET- 19};

    sewer.hpos[6] = {564 + XOFFSET, 323 + YOFFSET- 19};
    sewer.hpos[7] = {575 + XOFFSET, 332 + YOFFSET- 19};
    sewer.hpos[8] = {602 + XOFFSET, 340 + YOFFSET- 19};

    sewer.groundparticles.particleanimation = {6, 0, loadTexture(renderer, "particles/stone.png"), {6, 6}};
    sewer.groundparticles.maxparticles = 200;
    sewer.walkparticles.particleanimation = {4, 1, loadTexture(renderer, "particles/stonewalk.png"), {40, 5}};  
    
    sewer.jumpsfx[0] = Mix_LoadWAV("sfx/StoneJump1.wav");
    sewer.jumpsfx[1] = Mix_LoadWAV("sfx/StoneJump2.wav");
    sewer.landsfx[0] = Mix_LoadWAV("sfx/StoneLand1.wav");
    sewer.landsfx[1] = Mix_LoadWAV("sfx/StoneLand2.wav");
    sewer.landsfx[2] = Mix_LoadWAV("sfx/StoneLand3.wav");

    sewer.walksfx[0] = Mix_LoadWAV("sfx/StoneStep1.wav");
    sewer.walksfx[1] = Mix_LoadWAV("sfx/StoneStep2.wav");
    sewer.walksfx[2] = Mix_LoadWAV("sfx/StoneStep3.wav");
    sewer.walksfx[3] = Mix_LoadWAV("sfx/StoneStep4.wav");
    sewer.walksfx[4] = Mix_LoadWAV("sfx/StoneStep5.wav");
    sewer.walksfx[5] = Mix_LoadWAV("sfx/StoneStep6.wav");

    sewer.waterjumpsfx[0] = Mix_LoadWAV("sfx/wetjump1.wav");
    sewer.waterjumpsfx[1] = Mix_LoadWAV("sfx/wetjump2.wav");
    sewer.waterlandsfx[0] = Mix_LoadWAV("sfx/wetland1.wav");
    sewer.waterlandsfx[1] = Mix_LoadWAV("sfx/wetland2.wav");
    sewer.waterlandsfx[2] = Mix_LoadWAV("sfx/wetland3.wav");

    sewer.waterwalksfx[0] = Mix_LoadWAV("sfx/wetstep1.wav");
    sewer.waterwalksfx[1] = Mix_LoadWAV("sfx/wetstep2.wav");
    sewer.waterwalksfx[2] = Mix_LoadWAV("sfx/wetstep3.wav");
    sewer.waterwalksfx[3] = Mix_LoadWAV("sfx/wetstep4.wav");
    sewer.waterwalksfx[4] = Mix_LoadWAV("sfx/wetstep5.wav");
    sewer.waterwalksfx[5] = Mix_LoadWAV("sfx/wetstep6.wav");

    sewer.fastwalksfx[0] = Mix_LoadWAV("sfx/StoneFastSteps1.wav");
    sewer.fastwalksfx[1] = Mix_LoadWAV("sfx/StoneFastSteps2.wav");
    sewer.fastwalksfx[2] = Mix_LoadWAV("sfx/StoneFastSteps3.wav");
    sewer.fastwalksfx[3] = Mix_LoadWAV("sfx/StoneFastSteps4.wav");
    sewer.fastwalksfx[4] = Mix_LoadWAV("sfx/StoneFastSteps5.wav");
    sewer.fastwalksfx[5] = Mix_LoadWAV("sfx/StoneFastSteps6.wav");
    //grass
    
    grass.stage = 1;
    grass.dynamic = 0;

    grass.background1 = loadTexture(renderer, "stages/green/background1.png");
    grass.background2 = loadTexture(renderer, "stages/green/background2.png");
    grass.background3 = loadTexture(renderer, "stages/green/background3.png");
    grass.background4 = loadTexture(renderer, "stages/green/background4.png");
    grass.background4 = loadTexture(renderer, "stages/green/background5.png");

    grass.platforms = loadTexture(renderer, "stages/green/platforms.png" );
    grass.ground = loadTexture(renderer, "stages/green/ground.png");
    grass.foreground = loadTexture(renderer, "stages/green/foreground.png" );

    grass.height = 800-58;

    grass.h[0] = {{0, 0}, {1960, 0}, {1960, 100}, {0, 100}};
    grass.h[1] = {{0, 0}, {210, 0}, {210, 19}, {0, 19}};
    grass.h[2] = {{0, 0}, {184, 0}, {184, 6}, {0, 6}};
    grass.h[3] = {{0, 0}, {94, 0}, {94, 3}, {0, 3}};
    grass.h[4] = {{0, 0}, {109, 0}, {109, 19}, {0, 19}};
    grass.h[5] = {{0, 0}, {84, 0}, {84, 5}, {0, 5}};
    grass.h[6] = {{0, 0}, {76, 0}, {76, 19}, {0, 19}};
    grass.h[7] = {{0, 0}, {76, 0}, {76, 19}, {0, 19}};
    

    grass.hpos[0] = {-1000 + XOFFSET, 400 + YOFFSET};
    grass.hpos[1] = {336 + XOFFSET,199 + YOFFSET};
    grass.hpos[2] = {349 + XOFFSET,217 + YOFFSET};
    grass.hpos[3] = {415 + XOFFSET,222 + YOFFSET};
    grass.hpos[4] = {603 + XOFFSET,247 + YOFFSET};
    grass.hpos[5] = {615 + XOFFSET,265 + YOFFSET};
    grass.hpos[6] = {798 + XOFFSET, 286 + YOFFSET};
    grass.hpos[7] = {164 + XOFFSET,271 + YOFFSET};

    grass.groundparticles.particleanimation = {6, 0, loadTexture(renderer, "particles/dirt.png"), {6, 6}};
    grass.groundparticles.maxparticles = 200;
    grass.walkparticles.particleanimation = {6, 1, loadTexture(renderer, "particles/grasswalk.png"), {3, 5}};  
    grass.walkparticles.maxparticles = 100;
    grass.walkparticles.particleanimation = {6, 1, loadTexture(renderer, "particles/grasswalk.png"), {3, 5}};  
    grass.walkparticles.maxparticles = 100;
    grass.sporeparticles.particleanimation = {7, 1, loadTexture(renderer, "particles/spores.png"), {5, 5}};  
    grass.leafparticleanimations[0] = {10, 1, loadTexture(renderer, "particles/leaf1.png"), {4, 5}};  
    grass.leafparticleanimations[1] = {10, 1, loadTexture(renderer, "particles/leaf2.png"), {4, 5}};  
    grass.leafparticleanimations[2] = {10, 1, loadTexture(renderer, "particles/leaf3.png"), {5, 5}};  
    grass.leafparticleanimations[3] = {10, 1, loadTexture(renderer, "particles/leaf4.png"), {5, 5}};  
    grass.leafparticles.maxparticles = 75;


    grass.jumpsfx[0] = Mix_LoadWAV("sfx/GrassJump2.wav");
    grass.jumpsfx[1] = Mix_LoadWAV("sfx/GrassJump3.wav");

    grass.landsfx[0] = Mix_LoadWAV("sfx/GrassLand1.wav");
    grass.landsfx[1] = Mix_LoadWAV("sfx/GrassLand2.wav");
    grass.landsfx[2] = Mix_LoadWAV("sfx/GrassLand3.wav");

    grass.walksfx[0] = Mix_LoadWAV("sfx/GrassStep1.wav");
    grass.walksfx[1] = Mix_LoadWAV("sfx/GrassStep2.wav");
    grass.walksfx[2] = Mix_LoadWAV("sfx/GrassStep3.wav");
    grass.walksfx[3] = Mix_LoadWAV("sfx/GrassStep4.wav");
    grass.walksfx[4] = Mix_LoadWAV("sfx/GrassStep5.wav");
    grass.walksfx[5] = Mix_LoadWAV("sfx/GrassStep6.wav");

    grass.walksfx[0] = Mix_LoadWAV("sfx/GrassFastSteps1.wav");
    grass.walksfx[1] = Mix_LoadWAV("sfx/GrassFastSteps2.wav");
    grass.walksfx[2] = Mix_LoadWAV("sfx/GrassFastSteps3.wav");
    grass.walksfx[3] = Mix_LoadWAV("sfx/GrassFastSteps4.wav");
    grass.walksfx[4] = Mix_LoadWAV("sfx/GrassFastSteps5.wav");
    grass.walksfx[5] = Mix_LoadWAV("sfx/GrassFastSteps6.wav");


}

void assignsoundeffectstoplayers(stage s, player &player1, player &player2)
{
    player1.jumpsfx[0] = s.jumpsfx[0];
    player1.jumpsfx[1] = s.jumpsfx[1];
    player2.jumpsfx[0] = s.jumpsfx[0];
    player2.jumpsfx[1] = s.jumpsfx[1];

    player1.landsfx[0] = s.landsfx[0];
    player1.landsfx[1] = s.landsfx[1];
    player1.landsfx[2] = s.landsfx[2];   
    player2.landsfx[0] = s.landsfx[0];
    player2.landsfx[1] = s.landsfx[1];
    player2.landsfx[2] = s.landsfx[2];   

    player1.walksfx[0] = s.walksfx[0];
    player1.walksfx[1] = s.walksfx[1];
    player1.walksfx[2] = s.walksfx[2];
    player1.walksfx[3] = s.walksfx[3];
    player1.walksfx[4] = s.walksfx[4];
    player1.walksfx[5] = s.walksfx[5];
    player2.walksfx[0] = s.walksfx[0];
    player2.walksfx[1] = s.walksfx[1];
    player2.walksfx[2] = s.walksfx[2];
    player2.walksfx[3] = s.walksfx[3];
    player2.walksfx[4] = s.walksfx[4];
    player2.walksfx[5] = s.walksfx[5];

    if(s.dynamic == 1)
    {
        player1.waterjumpsfx[0] = s.waterjumpsfx[0];
        player1.waterjumpsfx[1] = s.waterjumpsfx[1];
        player2.waterjumpsfx[0] = s.waterjumpsfx[0];
        player2.waterjumpsfx[1] = s.waterjumpsfx[1];

        player1.waterlandsfx[0] = s.waterlandsfx[0];
        player1.waterlandsfx[1] = s.waterlandsfx[1];
        player1.waterlandsfx[2] = s.waterlandsfx[2];   
        player2.waterlandsfx[0] = s.waterlandsfx[0];
        player2.waterlandsfx[1] = s.waterlandsfx[1];
        player2.waterlandsfx[2] = s.waterlandsfx[2];   

        player1.waterwalksfx[0] = s.waterwalksfx[0];
        player1.waterwalksfx[1] = s.waterwalksfx[1];
        player1.waterwalksfx[2] = s.waterwalksfx[2];
        player1.waterwalksfx[3] = s.waterwalksfx[3];
        player1.waterwalksfx[4] = s.waterwalksfx[4];
        player1.waterwalksfx[5] = s.waterwalksfx[5];
        player2.waterwalksfx[0] = s.waterwalksfx[0];
        player2.waterwalksfx[1] = s.waterwalksfx[1];
        player2.waterwalksfx[2] = s.waterwalksfx[2];
        player2.waterwalksfx[3] = s.waterwalksfx[3];
        player2.waterwalksfx[4] = s.waterwalksfx[4];
        player2.waterwalksfx[5] = s.waterwalksfx[5];       
    }

    player1.fastwalksfx[0] = s.fastwalksfx[0];
    player1.fastwalksfx[1] = s.fastwalksfx[1];
    player1.fastwalksfx[2] = s.fastwalksfx[2];
    player1.fastwalksfx[3] = s.fastwalksfx[3];
    player1.fastwalksfx[4] = s.fastwalksfx[4];
    player1.fastwalksfx[5] = s.fastwalksfx[5];
    player2.fastwalksfx[0] = s.fastwalksfx[0];
    player2.fastwalksfx[1] = s.fastwalksfx[1];
    player2.fastwalksfx[2] = s.fastwalksfx[2];
    player2.fastwalksfx[3] = s.fastwalksfx[3];
    player2.fastwalksfx[4] = s.fastwalksfx[4];
    player2.fastwalksfx[5] = s.fastwalksfx[5];
}

void assignparticlestoplayers(stage s, player &player1, player &player2)
{
    player1.groundparticles = s.groundparticles;
    player2.groundparticles = s.groundparticles;
    player1.walkparticles = s.walkparticles;
    player2.walkparticles = s.walkparticles;
}