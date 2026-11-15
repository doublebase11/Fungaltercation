#include "characterlist.h"

void createplayers(player &player1, player &player2, SDL_Renderer * renderer)
{


    player defaultplayer;
    defaultplayer.idleanimation = {6, 1, loadTexture(renderer, "animation/Small_guy_Idle.png"), {40, 43}};
    defaultplayer.walkanimation = {4, 1, loadTexture(renderer, "animation/Small_guy_Walk.png"), {40, 43}};
    defaultplayer.jumpanimation = {2, 1, loadTexture(renderer, "animation/Small_guy_Jump.png"), {40, 43}};
    defaultplayer.fallanimation = {2, 1, loadTexture(renderer, "animation/Small_guy_Fall.png"), {40, 43}};

    defaultplayer.dashparticles.particleanimation = {6, 1, loadTexture(renderer, "particles/dashparticles.png"), {24, 20}};  
    defaultplayer.terminalvelocity = 8;
    defaultplayer.jumpvelocity = 10;
    defaultplayer.fastfallspeed = 4;
    defaultplayer.acceleration = {1, 1};
    defaultplayer.attackradius = 20;
    defaultplayer.mass = 6;

    defaultplayer.relativebodyhitboxpos = {10, 21};
    defaultplayer.bodyhitbox = {{0, 0}, {18, 0}, {18, 19}, {0, 19}};
    defaultplayer.relativebody2hitboxpos = {10, 8};
    defaultplayer.body2hitbox = {{0, 0}, {18, 0}, {18, 32}, {0, 32}};
    defaultplayer.relativecaphitboxpos = {2, 1};
    defaultplayer.caphitbox = {{0, 13}, {18, 0}, {36, 15}, {2, 18}};
    defaultplayer.relativecap2hitboxpos = {14, 3}; //small one
    defaultplayer.cap2hitbox = {{0, 0}, {11, 0}, {11, 10}, {0, 10}};
    defaultplayer.relativecap3hitboxpos = {3, 12}; //big one
    defaultplayer.cap3hitbox = {{0, 0}, {34, 0}, {34, 8}, {0, 8}};
    defaultplayer.relativefeethitboxpos = {10, 41};
    defaultplayer.feethitbox = {{0, 0}, {18, 0}, {18, 1}, {0,1}};

    defaultplayer.upperarmtexture = loadTexture(renderer, "sprites/arm4.png");
    defaultplayer.upperarmrotationcentre = {3, defaultplayer.elbowlength};
    defaultplayer.forearmtexture = loadTexture(renderer, "sprites/arm3.png");
    defaultplayer.forearmrotationcentre = {3, defaultplayer.elbowlength};
    defaultplayer.jointtexture = loadTexture(renderer, "sprites/joint3.png");
    defaultplayer.elbowwidth = 6;

    defaultplayer.sporetexture = loadTexture(renderer, "special attacks/op.png");
    defaultplayer.specialmove = 2;

    defaultplayer.dashrechargeanimation = {45, 1, loadTexture(renderer, "animation/dashrechargeanimation.png"), {50, 14}};
    defaultplayer.dashrechargeyoffset = 15;
    defaultplayer.dashrechargexoffset = 2;

    defaultplayer.parryeffectanimation = {8, 1, loadTexture(renderer, "sprites/effects/parry.png"), {19, 19}};
    defaultplayer.hiteffectanimation = {8, 1, loadTexture(renderer, "sprites/effects/hit.png"), {7, 7}};

    defaultplayer.deathsfx[0] = Mix_LoadWAV("sfx/DeathP1.wav");
    defaultplayer.deathsfx[1] = Mix_LoadWAV("sfx/DeathP2.wav");
    defaultplayer.deathsfx[2] = Mix_LoadWAV("sfx/DeathP3.wav");
    defaultplayer.entrancesfx = Mix_LoadWAV("sfx/tableshake.wav");
    defaultplayer.hitsfx[0] = Mix_LoadWAV("sfx/Hit1.wav");
    defaultplayer.hitsfx[1] = Mix_LoadWAV("sfx/Hit2.wav");
    defaultplayer.hitsfx[2] = Mix_LoadWAV("sfx/Hit3.wav");
    defaultplayer.clanksfx[0] = Mix_LoadWAV("sfx/clank1.wav");
    defaultplayer.clanksfx[1] = Mix_LoadWAV("sfx/clank2.wav");
    defaultplayer.clanksfx[2] = Mix_LoadWAV("sfx/clank3.wav");
    defaultplayer.clanksfx[3] = Mix_LoadWAV("sfx/clank4.wav");
    defaultplayer.clanksfx[4] = Mix_LoadWAV("sfx/clank5.wav");
    defaultplayer.clanksfx[5] = Mix_LoadWAV("sfx/clank6.wav");
    defaultplayer.clanksfx[6] = Mix_LoadWAV("sfx/clank7.wav");

    player defaultplayer2;
    defaultplayer2.idleanimation = {6, 1, loadTexture(renderer, "animation/Big guy Idle.png"), {50, 49}};
    defaultplayer2.walkanimation = {4, 1, loadTexture(renderer, "animation/Big guy Walk.png"), {50, 49}};
    defaultplayer2.jumpanimation = {2, 1, loadTexture(renderer, "animation/Big guy Jump.png"), {50, 49}};
    defaultplayer2.fallanimation = {2, 1, loadTexture(renderer, "animation/Big guy Fall.png"), {50, 49}}; 


    defaultplayer2.dashparticles.particleanimation = {6, 1, loadTexture(renderer, "particles/dashparticles.png"), {24, 20}};   
    defaultplayer2.terminalvelocity = 7;
    defaultplayer2.jumpvelocity = 9;
    defaultplayer2.fastfallspeed = 4;
    defaultplayer2.acceleration = {0.85, 1};
    defaultplayer2.attackradius = 20;
    defaultplayer2.mass = 6.5;

    defaultplayer2.relativebodyhitboxpos = {16, 17};
    defaultplayer2.bodyhitbox = {{0, 0}, {17, 0}, {17, 26}, {0, 26}};
    defaultplayer2.relativebody2hitboxpos = {16, 6};
    defaultplayer2.body2hitbox = {{0, 0}, {16, 0}, {16, 37}, {0, 37}};
    
    defaultplayer2.relativecaphitboxpos = {6, 1};
    defaultplayer2.caphitbox = {{0, 11}, {18, 0}, {36, 10}, {31, 13}};
    defaultplayer2.relativefeethitboxpos = {15, 44};
    defaultplayer2.feethitbox = {{0, 0}, {18, 0}, {18, 4}, {0,4}};

    defaultplayer2.upperarmtexture = loadTexture(renderer, "sprites/arm1.png");
    defaultplayer2.upperarmrotationcentre = {3, defaultplayer.elbowlength};
    defaultplayer2.forearmtexture = loadTexture(renderer, "sprites/arm2.png");
    defaultplayer2.forearmrotationcentre = {3, defaultplayer.elbowlength};
    defaultplayer2.jointtexture = loadTexture(renderer, "sprites/joint4.png");
    defaultplayer2.elbowwidth = 7;

    defaultplayer2.sporetexture = loadTexture(renderer, "special attacks/op2.png");
    defaultplayer2.specialmove = 1;

    defaultplayer2.dashrechargeanimation = {45, 1, loadTexture(renderer, "animation/dashrechargeanimation.png"), {50, 14}};
    defaultplayer2.parryeffectanimation = defaultplayer.parryeffectanimation;
     defaultplayer2.hiteffectanimation = defaultplayer.hiteffectanimation;

    defaultplayer2.deathsfx[0] = Mix_LoadWAV("sfx/DeathM1.wav");
    defaultplayer2.deathsfx[1] = Mix_LoadWAV("sfx/DeathM2.wav");
    defaultplayer2.deathsfx[2] = Mix_LoadWAV("sfx/DeathM3.wav");
    defaultplayer2.entrancesfx = defaultplayer.entrancesfx;
    defaultplayer2.hitsfx[0] = Mix_LoadWAV("sfx/Hit1.wav");
    defaultplayer2.hitsfx[1] = Mix_LoadWAV("sfx/Hit2.wav");
    defaultplayer2.hitsfx[2] = Mix_LoadWAV("sfx/Hit3.wav");
    defaultplayer2.clanksfx[0] = Mix_LoadWAV("sfx/clank1.wav");
    defaultplayer2.clanksfx[1] = Mix_LoadWAV("sfx/clank2.wav");
    defaultplayer2.clanksfx[2] = Mix_LoadWAV("sfx/clank3.wav");
    defaultplayer2.clanksfx[3] = Mix_LoadWAV("sfx/clank4.wav");
    defaultplayer2.clanksfx[4] = Mix_LoadWAV("sfx/clank5.wav");
    defaultplayer2.clanksfx[5] = Mix_LoadWAV("sfx/clank6.wav");
    defaultplayer2.clanksfx[6] = Mix_LoadWAV("sfx/clank7.wav");

    player1 = defaultplayer;
    player2 = defaultplayer2;

    player1.character = 1;
    player2.character = 2;

}

void initplayers(player &player1, player &player2, player playerused1, player playerused2)
{
    player1 = playerused1;
    player2 = playerused2;

    player1.player = 1;
    player2.player = 2;

    player2.pos.x = 820 + XOFFSET;
    player2.flip = SDL_FLIP_HORIZONTAL;

    player1.swordpos = player1.pos;
    player2.swordpos = player2.pos;
}