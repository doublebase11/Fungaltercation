#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include "gamestructs.h"




SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath);

void drawPng(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, int drawx, int drawy); //x and y are the coordinates of the top left of the image, w and h the width and height, drawx and drawy the coordinates where the image is drawn

void drawPngScale2(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, int drawx, int drawy, double scalefactor); 

void drawPngEx(SDL_Renderer* renderer, SDL_Texture* texture, viewport viewport, int x, int y, float w, float h, int drawx, int drawy, int centrex, int centrey, double rotationangle, SDL_RendererFlip flip); //draws png Ex. x and y are the coordinates of the top left of the image, w and h the width and height, drawx and drawy the coordinates where the image is drawn, centrex and centrey the centre of rotation(possibly), 

void drawPngExScaleonly(SDL_Renderer* renderer, SDL_Texture* texture, viewport viewport, int x, int y, float w, float h, int drawx, int drawy, int centrex, int centrey, double rotationangle, SDL_RendererFlip flip); //draws png Ex. x and y are the coordinates of the top left of the image, w and h the width and height, drawx and drawy the coordinates where the image is drawn, centrex and centrey the centre of rotation(possibly), 

void drawpartcircle(int centrex, int centrey, float radius, double ratio, SDL_Texture* dot, viewport v, SDL_Renderer* renderer);