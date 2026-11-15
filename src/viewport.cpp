#include "viewport.h"
//the worst code

//but im so happy it works

void CalculateViewportpos(viewport &viewport, player player1, player player2)
{
    //viewport.pos = {0, 0};
    float minspeed = 0.1;
    float maxspeed = 1;

    //float cameraspeed = (-(1-minspeed)/2.5294)*(viewport.scale -1 ) + maxspeed;
    float cameraspeed = viewport.cameraspeed;  // 0 < cameraspeed <= 1, 1 is the fastest
    float camerafasterspeed = viewport.camerafasterspeed;
    ////log << << cameraspeed << " " << viewport.scale << std::endl;
    int floor = 415 + YOFFSET + viewport.ycameraoffset;
    double xpos = viewport.pos.x;

    
    if(player1.pos.x < player2.pos.x)
    { 
        if(player1.pos.x < viewport.pos.x)
        {
            cameraspeed = camerafasterspeed;
        }
        viewport.pos.x = viewport.pos.x + ((player1.pos.x - viewport.pos.x) - viewport.posbehindplayertotheleft);

    }

    else
    {
        if(player2.pos.x < viewport.pos.x)
        {
            cameraspeed = camerafasterspeed;
        }
        viewport.pos.x = viewport.pos.x + ((player2.pos.x - viewport.pos.x) - viewport.posbehindplayertotheleft);

    }

    ////log << << cameraspeed << std::endl;

    if(viewport.pos.x <  XOFFSET)
    {
        viewport.pos.x =  XOFFSET;
    }
    

    viewport.pos.y = 0;

    if((viewport.pos.y + viewport.size.y) < (floor) && viewport.floorlock)
    {

        viewport.pos.y = ((floor) - viewport.size.y);
    }    
    if(viewport.pos.y < 0)
    {
        viewport.pos.y = viewport.pos.y*-1;
    }

   
   
        //aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
    if(player1.drawpos.y - viewport.posabovehighestplayer < viewport.pos.y || player2.drawpos.y - viewport.posabovehighestplayer < viewport.pos.y)
    {
        if(player1.drawpos.y < player2.drawpos.y)
        {
            while(player1.drawpos.y - viewport.posabovehighestplayer < viewport.pos.y)
            {
                viewport.pos.y -= 1;
            }
        }
        else
        {
             while(player2.drawpos.y - viewport.posabovehighestplayer < viewport.pos.y)
            {
                viewport.pos.y -= 1;                              
            }           
        }

        
    }

    viewport.pos.x = xpos + (cameraspeed *(viewport.pos.x - xpos));
    viewport.pos.y = viewport.pos.y;
    viewport.size.x = (int)(viewport.size.x);
    viewport.size.y = (int)(viewport.size.y); 

    
    //viewport.scale = 960/viewport.size.x;
}

void CalculateViewportSize(viewport &viewport, player player1, player player2)
{
    double xpos = viewport.pos.x;

    if(player1.pos.x < player2.pos.x)
    {
        viewport.size.x = (player2.pos.x + viewport.pospastplayertotheright) - xpos;
    }
    else
    {

       viewport.size.x = (player1.pos.x + viewport.pospastplayertotheright) - xpos;
    
    }
    if(viewport.size.x > 960)
    {
        viewport.size.x = 960;
    }   
    viewport.size.y = (float)9/16 * viewport.size.x;



    viewport.size.x = (int)(viewport.size.x);
    viewport.size.y = (int)(viewport.size.y); 
    
    ////log << << ypos << " " << xpos << " " << player1.pos.x << " " << player1.drawpos.y << " " << viewport.size.y << " " << viewport.size.x << std::endl;


}

void CalculateScale(viewport &viewport)
{
    viewport.scale = 960/viewport.size.x;
    ////log << << "ssssoooo" << std::endl;
    ////log << << viewport.scale << std::endl;
}

void CorrectViewport(viewport &viewport, player player1, player player2)
{
    if(((player1.drawpos.y < player2.drawpos.y) && (viewport.state == 0)) || viewport.state == 1)
    {
        CalculateViewportSize(viewport, player1, player2);
        ////log << << (player2.drawpos.y + 50) - (viewport.pos.y + viewport.size.y) << std::endl;
        if(viewport.pos.y + viewport.size.y < (FLOORMACRO+viewport.ycameraoffset) && viewport.floorlock)
        {
           viewport.size.y += (FLOORMACRO+viewport.ycameraoffset) - (viewport.pos.y + viewport.size.y);
           viewport.scale = 540/viewport.size.y;
           viewport.state = 1;

        }
        else
        {                            
            CalculateScale(viewport); 
            viewport.state = 0;
        }
        
        
                
    }   
    else if((1) || viewport.state == -1)
    {
    
        CalculateViewportSize(viewport, player1, player2);
        ////log << << (player2.drawpos.y + 50) - (viewport.pos.y + viewport.size.y) << std::endl;
        if((viewport.pos.y + viewport.size.y < FLOORMACRO+viewport.ycameraoffset) && viewport.floorlock)
        {
           viewport.size.y += (FLOORMACRO+viewport.ycameraoffset) - (viewport.pos.y + viewport.size.y);
           viewport.scale = 540/viewport.size.y;
           viewport.state = -1;
        }
        else
        {                            
            CalculateScale(viewport); 
            viewport.state = 0;
        }
       
    }
    else
    {
        CalculateViewportSize(viewport, player1, player2);
        CalculateScale(viewport); 
        viewport.state = 0;
    }



}

void LockViewportToLowestPlayer(viewport &viewport, player player1, player player2)
{
    if((viewport.pos.y + viewport.size.y) < player1.pos.y)
    {
        viewport.pos.y += (player1.pos.y - viewport.pos.y);
    }
    else if((viewport.pos.y + viewport.size.y) < player2.pos.y)
    {
        viewport.pos.y += (player2.pos.y - viewport.pos.y);
    }
}

void SetYCameraOffset(stage &s, viewport &v)
{
    v.ycameraoffset = s.ycameraoffset;
}

void UpdateViewport(viewport &viewport, player player1, player player2, stage s)
{
   
   if(viewport.onoff == 1)
   {

        CalculateViewportpos(viewport, player1, player2); 
        CorrectViewport(viewport, player1, player2);
        CalculateViewportSize(viewport, player1, player2);
        if(viewport.scale < 1)
        {
        	viewport.scale  = 1;
            viewport.size.x = 960;	
            viewport.size.y = 540;	
        }
        if(viewport.pos.y < (400 -s.height + YOFFSET))
        {
            viewport.pos.y = (400 -s.height + YOFFSET);
        }

   }
   else
   {
        viewport.pos = {0 + XOFFSET, YOFFSET};
        viewport.size = {960, 540};
        viewport.scale = 1;
   }
    
}


