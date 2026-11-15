#include "gfx.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);
    if(texture == NULL)
    {
        //log << << "failed to load texture:" << SDL_GetError() << std::endl;
    }
    else
    {
        ////log << << "texture loaded? " << filePath <<  std::endl;
    }
    return texture;
}

//  x and y are the coordinates of the top left of the image,
//  w and h the width and height, 
//  drawx and drawy the coordinates where the image is drawn
void drawPng(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, int drawx, int drawy) 
{
    SDL_Rect srcrect;
    SDL_Rect dstrect;

    srcrect.x = x;
    srcrect.y = y;
    srcrect.w = w;
    srcrect.h = h;
    dstrect.x = drawx * (1280/960);
    dstrect.y = drawy * (1280/960);
    dstrect.w = w * (1280/960);
    dstrect.h = h * (1280/960);
    SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}

void drawPngScale2(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, int drawx, int drawy, double scalefactor) 
{
    SDL_Rect srcrect;
    SDL_Rect dstrect;

    srcrect.x = x;
    srcrect.y = y;
    srcrect.w = w;
    srcrect.h = h;
    dstrect.x = drawx * (1280/960) * scalefactor;
    dstrect.y = drawy * (1280/960) * scalefactor;
    dstrect.w = w * (1280/960) * scalefactor;
    dstrect.h = h * (1280/960) * scalefactor;
    SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
}


void drawPngEx(SDL_Renderer* renderer, SDL_Texture* texture, viewport viewport, int x, int y, float w, float h, int drawx, int drawy, int centrex, int centrey, double rotationangle, SDL_RendererFlip flip = SDL_FLIP_NONE) //draws png Ex. x and y are the coordinates of the top left of the image, w and h the width and height, drawx and drawy the coordinates where the image is drawn, centrex and centrey the centre of rotation(possibly), 
{
    if((viewport.pos.x + (960/viewport.scale)) > 960 + XOFFSET)
    {
      viewport.pos.x -= (viewport.pos.x + (960/viewport.scale)) -960;
      viewport.pos.x += XOFFSET;
    }
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Point centre;

    srcrect.x = x;
    srcrect.y = y;
    srcrect.w = w;
    srcrect.h = h;
    dstrect.x = ((drawx * (1280/960)*viewport.scale) + (viewport.pos.x * (1280/960)*-viewport.scale)) * (1280/960);
    dstrect.y = ((drawy * (1280/960)*viewport.scale) + (viewport.pos.y * (1280/960)*-viewport.scale)) * (1280/960);
    dstrect.w = w*viewport.scale * (1280/960);
    dstrect.h = h*viewport.scale * (1280/960);

    centre.x = centrex*viewport.scale * (1280/960);
    centre.y = centrey*viewport.scale * (1280/960);

    SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, rotationangle, &centre, flip);
}

void drawPngExScaleonly(SDL_Renderer* renderer, SDL_Texture* texture, viewport viewport, int x, int y, float w, float h, int drawx, int drawy, int centrex, int centrey, double rotationangle, SDL_RendererFlip flip = SDL_FLIP_NONE) //draws png Ex. x and y are the coordinates of the top left of the image, w and h the width and height, drawx and drawy the coordinates where the image is drawn, centrex and centrey the centre of rotation(possibly), 
{
    if((viewport.pos.x + (960/viewport.scale)) > 960)
    {
      viewport.pos.x -= (viewport.pos.x + (960/viewport.scale)) -960;
      
    }
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Point centre;

    srcrect.x = x;
    srcrect.y = y;
    srcrect.w = w;
    srcrect.h = h;
    dstrect.x = (drawx) * (1280/960);
    dstrect.y = (drawy) * (1280/960);
    dstrect.w = w*viewport.scale * (1280/960);
    dstrect.h = h*viewport.scale * (1280/960);

    centre.x = centrex*viewport.scale * (1280/960);
    centre.y = centrey*viewport.scale * (1280/960);

    SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, rotationangle, &centre, flip);
}

void drawpartcircle(int centrex, int centrey, float radius, double ratio, SDL_Texture* dot, viewport v, SDL_Renderer* renderer)
{
    float pointtodrawto = radius*2;
    pointtodrawto *= ratio;
    pointtodrawto -= radius;
    for(float i = -radius; i < pointtodrawto; i++)
    {
        float y= i+1;
        float x = 2*sqrt(radius*radius - y*y);
       drawPngEx(renderer, dot, v, 0, 0, x, 1, centrex-(0.5*x), centrey-i, 0, 0, 0);
    }
    

}