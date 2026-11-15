#pragma once
#include "animation.h"
#include <fstream>
#include <string>
#define YOFFSET 700
#define XOFFSET 200
#define FLOORMACRO 405 + YOFFSET
#define PI 3.14159265
//#define SWORDGROUNDCOLLISIONS

struct vector2f2
{
    vector2f v1;
    vector2f v2;
};

struct hitbox
{
    //v stands for vertex
    vector2f v1, v2, v3, v4;
};

struct axis
{
    float g; //g is gradient
    int horv; //horizontal or vertical? 0 for neither, -1 for horizontal, 1 for vertical
};

struct button
{
    SDL_Texture* offtexture;
    SDL_Texture* ontexture;   
    vector2i pos = {0, 0};
    vector2i size = {0, 0};
};

struct particle
{
    animation particleanimation;
    vector2i particlelocations[200];
    int chosenspriteindex[200];
    int particlestarttime[200];
    vector2f velocity[200] = {0, 0};
    vector2i pos[200] = {0, 0}; 
    int particleanimationchosen[200];
    int enabled[200];
    int maxparticles = 200;
    int particlespresent = 0;
    double lastparticletime = 0;
};

struct sword
{
    int sword = 1;
    double weight;
    double speed;
    int maxdamage;
    vector2i size; //sword size
    vector2i handle; //coordinates of the handle of the sword
    

    SDL_Texture* texture1; //sword textures - temprorary

    vector2f relativetiphitboxpos;
    vector2f tiphitboxpos;
    hitbox tiphitbox;

    vector2f relativebladehitboxpos;
    vector2f bladehitboxpos;
    hitbox bladehitbox;
};

struct spore
{
    vector2f velocity = {0, 0};
    vector2i pos = {0, 0}; 
    int rotationdirection = -1; //-1 for anticlockwise and 1 for clockwise
    int rotation = 0;
    int size = 0; 
};


struct player //someone please organise this - 169
{
    float mass = 0;
    int character;
    int player; //player1 or 2


    int GetTicks = 0;

    int health = 200;

    //particles
    particle walkparticles;
    particle dashparticles;

    //animations
    animation idleanimation;
    animation walkanimation;
    animation jumpanimation;
    animation fallanimation;

    //effects
    vector2f parryeffectpos = {0, 0};
    int startparryeffectanimation = 0;
    animation parryeffectanimation;

    vector2f hiteffectpos = {0, 0};
    int starthiteffectanimation = 0;
    animation hiteffectanimation;

    //player direction
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    
    //pos
    vector2i pos = {50 + XOFFSET, 500 + YOFFSET}; //pos of player 
    vector2i drawpos = {50 + XOFFSET, 200};
    vector2i cursor = {0, 0}; //Not the actual cursor(that's mouse) but where the cursor is relative to the player
    vector2i centre = {0, 0};

    //sword
    sword sword;
    vector2i swordpos = {50, 200};
    vector2i swordprevpos = {50, 200};
    vector2i sworddrawpos = {50, 200};
    double swordmomentum = 0;
    double swordprevrotation = 0;
    double swordrotation = 0;
    double cursorprevrotation = 0;
    double cursorrotation = 0;
    vector2i swordrelativepos = {0, 0};
    vector2i swordprevrelativepos = {0, 0};
    double swordrelativeposchange = 0;

    //normal attacking(swinging the sword)
    int swordon = 1;
    int attacking = 0;
    double attackpower = 0;
    int hit160 = 0;
    int hit80 = 0;
    double attackstarttime = 0;
    double attackduration = 0;
    double initialattackangle = 0;
    vector2i attackstart = {0, 0};

    //general special moves
    int specialmove = 1; //which specialmove?
    int special = 0;
    int specialstarttime = -12000;
    int specialcooldown = 5000;

    //spore attack(special move 1)
    spore s[500];
    int sporecountlimit = 150;
    int sporecount = 0;
    int sporefirespeed = 6;
    int sporeattackduration = 800;
    int sporehitstun = 333;
    int sporesdisappearingperframe = 6;
    int sporedissapearancethreshold = 70;
    int sporebasespeed = 3;
    int sporerandomizedspeed = 3;
    int sporespreadangle = 45;
    int sporespinmaxspeed = 3;
    int sporecollision = 0;
    SDL_Texture* sporetexture;

    //charge attack(special move 2)
    int charge = 0; //which charge 
    int chargestarttime = 0;
    vector2f chargedirection = {0, 0};
    vector2f initialchargevelocity = {0, 0};
    int chargehitboxactive = 0;
    int chargeduration = 380;
    int chargehitstun = 450;
    int chargedamage = 5;

    //parrying
    int parried = 0;
    float parryinitialrotation = 0;
    int parryrotationdistance = 0;
    int parrydirection = 0;
   
    //hitboxes
    vector2f relativebodyhitboxpos;
    vector2f bodyhitboxpos;
    hitbox bodyhitbox;

    vector2f relativebody2hitboxpos;
    vector2f body2hitboxpos;
    hitbox body2hitbox;

    vector2f relativecaphitboxpos;
    vector2f caphitboxpos;
    hitbox caphitbox;

    vector2f relativecap2hitboxpos;
    vector2f cap2hitboxpos;
    hitbox cap2hitbox;

    vector2f relativecap3hitboxpos;
    vector2f cap3hitboxpos;
    hitbox cap3hitbox;

    vector2f relativefeethitboxpos;
    vector2f feethitboxpos;
    hitbox feethitbox;

    //for dashing
    vector2i doubletap = {0, 0};       
    vector2i doubletapstart = {0, 0};
    vector2i tapstart = {0, 0};
    vector2i tapstarttime = {0, 0};
    int doubletaptime = 300;
    int dashdistance = 8;
    int doubletaptimelimit = 1000;
    int doubletapstarttime = 0;
    int doubletapinitial = 0;

    int dashvelocity = 20;
    float moveagainthreshold = 1;

    vector2i dashdirection = {0, 0};
    int showdashavailable = 0;
    animation dashrechargeanimation;
    int dashrechargeyoffset = 15;
    int dashrechargexoffset = 15;
    
    //general movement
    int xmovementdirection = 0; //-1 means the player is holding left(a), 1 means right(d)
    int fastfalling = 0;

    int terminalvelocity = 14; //change this someone to make moving nicer    

    int jump = 0;
    int jumpvelocity = 10;
    
    double fastfallspeed = 4;
    
    vector2f acceleration = {1, 1}; //must be above 1 
    vector2f velocity = {0, 0};
    vector2f prevvelocity = {0, -0.1};
    vector2f extravelocity = {0, 0};

    int xchange = 0;
    int ychange = 0;
    int extraychange = 0;
    int extraxchange = 0;

    double originalx;
    double originaly;

    //collisionstates - stores what the player has collided with
    vector2i stagecollisionstate = {0, 0};
    int capcollided = 0;
    int bodycollided = 0;
    int broadcollision = 1;
    int watercollision = 0;

    vector2i attackcentre = {300,50};
    int attackradius = 20;

    //arm
    vector2f elbowpos;
    double upperarmangle = 0;
    double forearmangle = 0;
    SDL_Texture* upperarmtexture;
    SDL_Texture* forearmtexture;   
    SDL_Texture* jointtexture;
    vector2i upperarmrotationcentre;
    vector2i forearmrotationcentre;
    int elbowlength = 15;
    int elbowwidth = 0;

    //pause
    int pause = 0;
    int pausexmovementdirection = 1;
    vector2i pausemousecoords = {0, 0};

    //hitting and hitstun
    int timehit = 0;
    int timebetweenhits = 150;
    int inhitstun = 0;
    int hitstuntimer = 0;
    int timetospendinhitstun = 0;

    //player states
    int stunned = 0;
    
    int dead = 0;
    int turn = 1;
    int gamestart = 1;
    int gameover = 0;
    int switchcharacter = 1;
    int changedcharacter = 0;
    float swordfallspeed = 1;
    int pausepressed = 0;

    int swordprevdirection = 0;

    //STAGE PARTICLES
    particle groundparticles;

    //SOUND EFFECTS
    Mix_Chunk* deathsfx[3];
    Mix_Chunk* entrancesfx;
    Mix_Chunk* jumpsfx[2];
    Mix_Chunk* landsfx[3];
    Mix_Chunk* walksfx[6];
    Mix_Chunk* waterjumpsfx[2];
    Mix_Chunk* waterlandsfx[3];
    Mix_Chunk* waterwalksfx[6];
    Mix_Chunk* fastwalksfx[6];
    Mix_Chunk* hitsfx[3];
    Mix_Chunk* clanksfx[7];

};

struct viewport
{
    vector2i pos =  {0, 0};
    vector2f size = {960, 540};
    double scale = 1;
    int state = 0; //AHAHAHAHAHAHAHAAHA

    //custom options
    int onoff = 1; //-1 for disabled,  1 for enabled
    int floorlock = 1;
    float cameraspeed = 0.66*0.033;  // 0 < cameraspeed <= 1, 1 is the fastest
    float camerafasterspeed = 0.66*0.066;
    int posbehindplayertotheleft = 100;
    int posabovehighestplayer = 150;
    int pospastplayertotheright = 100;

    //set by the stage
    int ycameraoffset = 0;
};

struct stage
{
    int stage = 1;
    int dynamic = 0;
    int ycameraoffset = 0;

    SDL_Texture* background1;
    SDL_Texture* background2;
    SDL_Texture* background3;
    SDL_Texture* background4;
    SDL_Texture* background5;
    SDL_Texture* platforms;
    SDL_Texture* ground;
    SDL_Texture* foreground;
    SDL_Texture* watertexture;

    int height = 540;
    int hitboxnumber = 8;


    hitbox h[9] = {{{0, 0}, {1960, 0}, {1960, 100}, {0, 100}}, {{0, 0}, {67, 0}, {67, 15}, {0, 15}}, {{0, 0}, {223, 0}, {223, 15}, {0, 15}}, {{0, 0}, {127, 0}, {127, 15}, {0, 15}}, {{0, 0}, {95, 0}, {95, 15}, {0, 15}}, {{0, 0}, {32, 0}, {32, 15}, {0, 15}}, {{0, 0}, {47, 0}, {47, 15}, {0, 15}}, {{0, 0}, {143, 0}, {143, 15}, {0, 15}}};
    vector2f hpos[9] = {{-1000 + XOFFSET, 400 + YOFFSET} , {171 + XOFFSET, 287 + YOFFSET}, {331 + XOFFSET, 193 + YOFFSET}, {379 + XOFFSET, 209 + YOFFSET}, {617 + XOFFSET, 245 + YOFFSET}, {649 + XOFFSET, 261 + YOFFSET}, {813 + XOFFSET, 306 + YOFFSET}, {133 + XOFFSET, 271 + YOFFSET}};
    vector2f platformcentres[9] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    //STAGE PARTICLES
    particle groundparticles;
    particle walkparticles;
    particle sporeparticles;
    particle leafparticles;
    animation leafparticleanimations[4];

    //SOUND EFFECTS
    Mix_Chunk* jumpsfx[2];
    Mix_Chunk* landsfx[3];
    Mix_Chunk* walksfx[6];
    Mix_Chunk* waterjumpsfx[2];
    Mix_Chunk* waterlandsfx[3];
    Mix_Chunk* waterwalksfx[6];
    Mix_Chunk* fastwalksfx[6];

};