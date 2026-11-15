#include "button.h"

int createButton(button b, vector2i mouse,  int mousedown,  SDL_Renderer* renderer)
{
    int pressed = 0;
    
    if((mouse.x >= b.pos.x && mouse.x <= (b.pos.x + b.size.x))&&(mouse.y >= b.pos.y && mouse.y <= (b.pos.y + b.size.y)) && mousedown != 0)
    {
        drawPng(renderer, b.ontexture, 0, 0, b.size.x, b.size.y, b.pos.x, b.pos.y);
        if(mousedown == 1)
        {
            pressed = 0;
        }
        else if(mousedown == -1)
        {
            pressed = 1;
        }
    }
    else
    {
        drawPng(renderer, b.offtexture, 0, 0, b.size.x, b.size.y, b.pos.x, b.pos.y);
    }
    return pressed;
}