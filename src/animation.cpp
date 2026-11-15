#include "animation.h"

void UpdateAnimation(animation &animation, int GetTicks)
{
    if(((GetTicks/17) % animation.maxframes < 0.1) && ((GetTicks/17) % animation.maxframes > -0.1))
    {

        if(animation.currentframe == animation.maxframes)
        {
            animation.currentframe = 1;
        }
        else
        {
            animation.currentframe++;
        }

    }
}
 
int ChooseSprite(animation animation)
{
    return((animation.currentframe-1)*animation.size.x);
}

