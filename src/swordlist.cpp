#include "swordlist.h"

void createSwords(sword &zwig, sword &bigsword, sword &boringsword, sword &dagger, SDL_Renderer * renderer)
{
    zwig.sword = 1;
    zwig.weight = 7;
    zwig.maxdamage = 22;
    zwig.speed = 0.15;
    zwig.size = {17, 69}; //sword size
    zwig.handle = {8, 65}; //coordinates of the handle of the sword
    zwig.texture1 = loadTexture(renderer, "sprites/zwigb.png"); //sword textures - temporary
    zwig.relativetiphitboxpos = {0, 0};
    zwig.tiphitbox = {{7, 0}, {9, 0}, {10, 4}, {6, 4}};
    zwig.relativebladehitboxpos = {0, 0};
    zwig.bladehitbox = {{6, 5}, {10, 5}, {10, 57}, {6, 57}};

    bigsword.sword = 2;
    bigsword.weight = 16;
    bigsword.maxdamage = 27;
    bigsword.speed = 0.07;
    bigsword.size = {19, 130}; //sword size
    bigsword.handle = {9, 126}; //coordinates of the handle of the sword
    bigsword.texture1 = loadTexture(renderer, "sprites/Big Sword.png"); //sword textures - temporary
    bigsword.relativetiphitboxpos = {2, 1};
    bigsword.tiphitbox = {{5, 0}, {7, 0}, {12, 17}, {0, 17}};
    bigsword.relativebladehitboxpos = {2, 20};
    bigsword.bladehitbox = {{0, 0}, {14, 0}, {14, 77}, {0, 77}};

    boringsword.sword = 3;
    boringsword.weight = 5;
    boringsword.speed = 0.18;
    boringsword.maxdamage = 22;
    boringsword.size = {13, 61}; //sword size
    boringsword.handle = {6, 58}; //coordinates of the handle of the sword
    boringsword.texture1 = loadTexture(renderer, "sprites/sword.png"); //sword textures - temporary
    boringsword.relativetiphitboxpos = {0, 0};
    boringsword.tiphitbox = {{5, 0}, {7, 0}, {8, 7}, {4, 7}};
    boringsword.relativebladehitboxpos = {0, 0};
    boringsword.bladehitbox = {{4, 8}, {8, 8}, {8, 46}, {4, 46}};

    dagger.sword = 4;
    dagger.weight = 1;
    dagger.speed = 0.6;
    dagger.maxdamage = 18;
    dagger.size = {11, 25}; //sword size
    dagger.handle = {5, 22}; //coordinates of the handle of the sword
    dagger.texture1 = loadTexture(renderer, "sprites/dagger.png"); //sword textures - temporary
    dagger.relativetiphitboxpos = {0, 0};
    dagger.tiphitbox = {{4, 0}, {6, 0}, {7, 4}, {3, 4}};
    dagger.relativebladehitboxpos = {0, 0};
    dagger.bladehitbox = {{3, 5}, {7, 5}, {7, 15}, {3, 15}};
}

void addSwords(player &player1, player &player2, sword sword1, sword sword2, SDL_Renderer * renderer)
{
    player1.sword = sword1;
    player2.sword = sword2;
}