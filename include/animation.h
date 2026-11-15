#pragma once
#include "maths.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

struct animation
{
    int maxframes = 1;
    int currentframe = 1;
    SDL_Texture* textures;
    vector2i size = {0, 0};
};

void UpdateAnimation(animation &animation, int GetTicks);

int ChooseSprite(animation animation);
