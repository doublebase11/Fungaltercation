//this whole thing will be eventually rewritten
#include "input.h"
#define FASTFALLLIMIT -1

//Gamecube controller controls
#define DASHBUTTON 7
#define JUMPBUTTON 5
#define SPECIALBUTTON 4
#define PAUSEBUTTON 9
#define MOVEMENTAXISX 0
#define MOVEMENTAXISY 1
#define MOUSEAXISX 5
#define MOUSEAXISY 2

//Xbox controller controls
//#define DASHBUTTON 5
//#define JUMPBUTTON 1
//#define SPECIALBUTTON 4
//#define PAUSEBUTTON 7
//#define MOVEMENTAXISX 0
//#define MOVEMENTAXISY 1
//#define MOUSEAXISX 2
//#define MOUSEAXISY 3

void setupmiceinput(HANDLE &m1, HANDLE &m2, RAWINPUTDEVICELIST *&pRawInputDeviceList)
{
        // Register for mouse input
    RAWINPUTDEVICE Rid[2];     // Rid of *size* 2, not Rid[2] itself
    Rid[0].usUsagePage = 0x01; // Generic Desktop Controls
    Rid[0].usUsage = 0x02;     // Mouse
    Rid[0].dwFlags = 0;        // default value, tracks when app is in foreground (active)
    Rid[0].hwndTarget = nullptr; 

    Rid[1].usUsagePage = 0x01; //Generic Desktop Controls
    Rid[1].usUsage = 0x06;     // Keyboard
    Rid[1].dwFlags = 0;        // default value, tracks when app is in foreground (active)
    Rid[1].hwndTarget = nullptr; 

    if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) { //can it register mouse input? (Array of raw input devices, two device types, this last one is self-explanatory)
        DWORD error = GetLastError(); //gets the error code, likely the one for failed  input
        std::cerr << "Failed to register for raw input events! Error code: " << error << std::endl; //spits out the error
    }
    // Enumerate connected mice
    UINT nDevices;
    GetRawInputDeviceList(nullptr, &nDevices, sizeof(RAWINPUTDEVICELIST)); // nullptr here means all raw input devices connected (since each mouse has a different handle), &nDevices is a pointer to nDevices, after this function is called, it will contain the number of raw input devices, sizeof(RAWINPUTDEVICELIST) allows for the allocation of the right amount of memory
    pRawInputDeviceList = new RAWINPUTDEVICELIST[nDevices]; //creates pointer that points to an array of RAWINPUTDEVICELIST structures of size nDevices
    GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST)); //this populates the above array with information of connected raw input devices
    ////log << << "Connected mice:" << std::endl;
    int done = 0;
    int m1id = 0;
    int m2id = 0;
    for (UINT i = 0; i < nDevices; ++i) {
        if (pRawInputDeviceList[i].dwType == RIM_TYPEMOUSE) { // don't think I need to explain this, but it just checks if the current device type is a mouse
            ////log << << "Device " << i + 1 << ": " << pRawInputDeviceList[i].hDevice << std::endl; //prints mouse device handle out to console
            if(done == 0)
            {
                m1id = i;
                done++;
            }
            else if(done == 1)
            {
                m2id = i;
                done++;
            }
        }
    }
    m1 = pRawInputDeviceList[m1id].hDevice;
    m2 = pRawInputDeviceList[m2id].hDevice;
}

void miceinput(int &m1x, int &m1y, int &m1leftdown, int &m1rightdown, int &m2x, int &m2y, int &m2leftdown, int &m2rightdown, HANDLE m1, HANDLE m2, int gaming, player &player1, player &player2)
{
    if(m1rightdown == 1)
    {
        m1rightdown = -1;
    }
    if(m2rightdown == 1)
    {
        m2rightdown = -1;
    }
    int mouse1tempx = m1x;
    int mouse1tempy = m1y;
    int mouse2tempx = m2x;
    int mouse2tempy = m2y;

            MSG rawMessage; //MSG is the variable type used by Windows messages
        while (PeekMessage(&rawMessage, NULL, 0, 0, PM_REMOVE)) { //PeekMessage populates the rawMessage var with the details of the message, NULL means for any window, double 0 for lowest and highest message value limits (basically any priority), PM_REMOVE removes it from the queue (Pearcey actually taught us something relevant to this?????)
            int flag = 0;
            if (rawMessage.message == WM_INPUT) { //self-explanatory (if the message type is an input)
                UINT dataSize;
                GetRawInputData(reinterpret_cast<HRAWINPUT>(rawMessage.lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

                if (dataSize > 0) { //does the variable actually have something in it
                    BYTE* rawData = new BYTE[dataSize]; //dynamic memory allocation, making an array [dataSize] bytes long (forgot to mention dataSize stores the size in bytes)
                    if (GetRawInputData(reinterpret_cast<HRAWINPUT>(rawMessage.lParam), RID_INPUT, rawData, &dataSize, sizeof(RAWINPUTHEADER)) == dataSize) { //basically error checking, if statement can be omitted if you want
                        RAWINPUT* rawInputData = reinterpret_cast<RAWINPUT*>(rawData); // more casting! this time to access the fields within the RAWINPUT structure, we have to change the data type

                        

                        if (rawInputData->header.hDevice == m1) { //wow! Was there something just like this above? I wonder...
                            flag = 1;
                            mouse1tempx += rawInputData->data.mouse.lLastX; // gets x movement from the data structure
                            mouse1tempy += rawInputData->data.mouse.lLastY; //same but with y

                            if (rawInputData->data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN) {
                                m1leftdown = 1;
                           }
                           if (rawInputData->data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN) {
                                if(m1rightdown == 0)
                                {
                                    m1rightdown = 1;                                   
                                }
                           }
                           if (rawInputData->data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_UP) {
                                m1leftdown = 0;
                           }
                           if (rawInputData->data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_UP) {
                                m1rightdown = 0;
                           }
                        }
                       else if (rawInputData->header.hDevice == m2) { //wow! Was there something just like this above? I wonder...
                           flag = 1; 
                           mouse2tempx += rawInputData->data.mouse.lLastX; // gets x movement from the data structure
                           mouse2tempy += rawInputData->data.mouse.lLastY; //same but with y

                           if (rawInputData->data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN) {
                                m2leftdown = 1;
                           }
                           if (rawInputData->data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN) {
                                if(m2rightdown == 0)
                                {
                                    m2rightdown = 1;
                                    
                                }
                           }
                           if (rawInputData->data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_UP) {
                                m2leftdown = 0;
                           }
                           if (rawInputData->data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_UP) {
                                m2rightdown = 0;
                           }
                                                 
                       }
                       else
                       {
                            TranslateMessage(&rawMessage);
                            DispatchMessage(&rawMessage);
                       }

                    }
                    if(flag)
                    {
                        delete[] rawData; //don't want memory leaks, do we???
                    }
                }



            }
            else
            {
                TranslateMessage(&rawMessage);
                DispatchMessage(&rawMessage);
            }

        }


    if(player1.pause == 1 || gaming != 1)
    {
        m1x = mouse1tempx;
        m1y = mouse1tempy;
        m2x = mouse2tempx;
        m2y = mouse2tempy;
    }
    else
    {
        int limit = 25;

        float m1movementmagnitude = hypot((mouse1tempx - m1x), (mouse1tempy - m1y));
        float m1xmove = (mouse1tempx - m1x);
        float m1ymove = (mouse1tempy - m1y);
        if(m1movementmagnitude > limit)
        {
            m1xmove = m1xmove/m1movementmagnitude;
            m1xmove = m1xmove*limit;
            m1ymove = m1ymove/m1movementmagnitude;
            m1ymove = m1ymove*limit;
        }
        float m2movementmagnitude = hypot((mouse2tempx - m2x), (mouse2tempy - m2y));
        float m2xmove = (mouse2tempx - m2x);
        float m2ymove = (mouse2tempy - m2y);
        if(m2movementmagnitude > limit)
        {
            m2xmove = m2xmove/m2movementmagnitude;
            m2xmove = m2xmove*limit;
            m2ymove = m2ymove/m2movementmagnitude;
            m2ymove = m2ymove*limit;
        }

        if(player1.parried == 1)
        {
            m1xmove = 0;
            m1ymove = 0;
        }
        if(player2.parried == 1)
        {
            m2xmove = 0;
            m2ymove = 0;
        }

        if(player1.specialmove == 1 && player1.special == 2)
        {
            m1x = m1x + m1xmove;
            m1y = m1y + m1ymove;
        }
        else
        {
            m1x = m1x + player1.sword.speed*m1xmove;
            m1y = m1y + player1.sword.speed*m1ymove;
        }

        if(player1.specialmove == 1 && player1.special == 2)
        {
            m2x = m2x + m2xmove;
            m2y = m2y + m2ymove;  
        }
        else
        {
            m2x = m2x + player2.sword.speed*m2xmove;
            m2y = m2y + player2.sword.speed*m2ymove;            
        }


    }

    
    //m1movementmagnitude = hypot(m1xmove, m1ymove);
    //if(m1movementmagnitude > 0)
    //{
    //    //log << << m1movementmagnitude << std::endl;
    //}

}

void miceclicks(int m1leftdown, int m1rightdown, int m2leftdown,int m2rightdown, player &player1, player &player2)
{
  
            if(m1rightdown == 1)
            {
                if(!player1.inhitstun && !player1.pause && player1.gamestart == 0)
                {
                    if(player1.specialmove == 1)
                    {
                        if((player1.special == 0)&& ((player1.GetTicks-player1.specialstarttime)) > player1.specialcooldown)
                        {
                            player1.special = 1;
                        }
                    }
                    else if (player1.specialmove == 2)
                    {
                        if((player1.special == 0)&& ((player1.GetTicks-player1.specialstarttime) > player1.specialcooldown))
                        {
                            player1.special = 1;
                            player1.charge = 1;
                        }
                        else if((player1.special == 0) && (player1.charge == 1))
                        {
                            player1.special = 1;
                            player1.charge = 2;
                        }
                    }  
                } 
            }  


        if(m2rightdown == 1) 
        {
            if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
            {   
                if(player2.specialmove == 1)
                {
                    if((player2.special == 0)&& ((player2.GetTicks-player2.specialstarttime)) > player2.specialcooldown)
                    {
                        player2.special = 1;
                    }
                }
                else if (player2.specialmove == 2)
                {
                    if((player2.special == 0)&& ((player2.GetTicks-player2.specialstarttime) > player2.specialcooldown))
                    {
                        player2.special = 1;
                        player2.charge = 1;
                    }
                    else if((player2.special == 0) && (player2.charge == 1))
                    {
                        player2.special = 1;
                        player2.charge = 2;
                    }
                } 
            }  
        }

}

void HandleP1Movement(SDL_Event &event, player &player1)
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_w)
        {
            if(!player1.inhitstun && !player1.pause && player1.gamestart == 0) 
            {
                if(player1.jump == 0)
                {
                    player1.jump = 1;                                                                  
                }
            }
        }
        if(event.key.keysym.sym == SDLK_s)
        {
            if(!player1.inhitstun && !player1.pause && player1.gamestart == 0)
            {
                if((player1.velocity.y < -FASTFALLLIMIT) && (player1.fastfalling == 0))
                {
                    player1.fastfalling = 1;
                }   
            }   
        }
        if(event.key.keysym.sym == SDLK_a)
        {
            if(!player1.inhitstun && !player1.pause && player1.gamestart == 0)
            {
                player1.xmovementdirection = -1;
                if((player1.GetTicks - player1.doubletapstart.y) < player1.doubletaptime && player1.doubletap.y == 0 && ((player1.GetTicks - player1.doubletapstarttime) > player1.doubletaptimelimit) && (player1.GetTicks - player1.tapstarttime.y) < player1.doubletaptime)
                {
                    player1.doubletap.y = 2;
                }
                else
                {
                    if(player1.tapstart.y == 0)
                    {
                        player1.tapstarttime.y = player1.GetTicks;
                    }
                    player1.tapstart.y = 1;
                    player1.doubletap.y = 1;
                }
                player1.doubletapstart.y = player1.GetTicks;
                player1.doubletapstart.x = 0;
            }
        }
        else if(event.key.keysym.sym == SDLK_d)
        {
            if(!player1.inhitstun && !player1.pause && player1.gamestart == 0)
            {
                player1.xmovementdirection = 1;
                if((player1.GetTicks - player1.doubletapstart.x) < player1.doubletaptime && player1.doubletap.x == 0 && ((player1.GetTicks - player1.doubletapstarttime) > player1.doubletaptimelimit) && (player1.GetTicks - player1.tapstarttime.x) < player1.doubletaptime)
                {
                    player1.doubletap.x = 2;
                }
                else
                {
                    if(player1.tapstart.x == 0)
                    {
                        player1.tapstarttime.x = player1.GetTicks;
                    }
                    player1.tapstart.x = 1;
                    player1.doubletap.x = 1;
                }
                player1.doubletapstart.x = player1.GetTicks;
                player1.doubletapstart.y = 0;
            }
        }  
    }

    if(event.type == SDL_KEYUP)
    {  
        if(event.key.keysym.sym == SDLK_w)
        {
            player1.jump = 0;
        }
        if(event.key.keysym.sym == SDLK_a)
        {
            if(player1.xmovementdirection == -1)
            {
                player1.xmovementdirection = 0;
            }
            player1.tapstart.y = 0;
            player1.doubletap.y = 0;
        }
        else if(event.key.keysym.sym == SDLK_d)
        {
            if(player1.xmovementdirection == 1)
            {
                player1.xmovementdirection = 0;
            }
            player1.tapstart.x = 0;
            player1.doubletap.x = 0;
        }   
    }
    
}

void HandleP2Movement(SDL_Event &event, player &player2)
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_i)
        {
            if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
            {        
                if(player2.jump == 0)
                {
                    player2.jump = 1;                                                                  
                }
            }
        }
        if(event.key.keysym.sym == SDLK_k)
        {
            if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
            {   
                if((player2.velocity.y < -FASTFALLLIMIT) && (player2.fastfalling == 0))
                {
                    player2.fastfalling = 1;
                }      
            }
        }
        if(event.key.keysym.sym == SDLK_j)
        {
            if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
            {   
                player2.xmovementdirection = -1;
                if((player2.GetTicks - player2.doubletapstart.y) < player2.doubletaptime && player2.doubletap.y == 0 && ((player2.GetTicks - player2.doubletapstarttime) > player2.doubletaptimelimit) && (player2.GetTicks - player2.tapstarttime.y) < player2.doubletaptime)
                {
                    player2.doubletap.y = 2;
                }
                else
                {
                    if(player2.tapstart.y == 0)
                    {
                        player2.tapstarttime.y = player2.GetTicks;
                    }
                    player2.tapstart.y = 1;
                    player2.doubletap.y = 1;
                }
                player2.doubletapstart.y = player2.GetTicks;
                player2.doubletapstart.x = 0;
            }
        }
        else if(event.key.keysym.sym == SDLK_l)
        {
            if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
            {   
                player2.xmovementdirection = 1;
                if((player2.GetTicks - player2.doubletapstart.x) < player2.doubletaptime && player2.doubletap.x == 0 && ((player2.GetTicks - player2.doubletapstarttime) > player2.doubletaptimelimit) && (player2.GetTicks - player2.tapstarttime.x) < player2.doubletaptime)
                {
                    player2.doubletap.x = 2;
                }
                else
                {
                    if(player2.tapstart.x == 0)
                    {
                        player2.tapstarttime.x = player2.GetTicks;
                    }
                    player2.tapstart.x = 1;
                    player2.doubletap.x = 1;
                }
                player2.doubletapstart.x = player2.GetTicks;
                player2.doubletapstart.y = 0;
            }
        } 
        else if(event.key.keysym.sym == SDLK_p) 
        {
            if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
            {   
                if(player2.specialmove == 1)
                {
                    if((player2.special == 0)&& ((player2.GetTicks-player2.specialstarttime)) > player2.specialcooldown)
                    {
                        player2.special = 1;
                    }
                }
                else if (player2.specialmove == 2)
                {
                    if((player2.special == 0)&& ((player2.GetTicks-player2.specialstarttime) > player2.specialcooldown))
                    {
                        player2.special = 1;
                        player2.charge = 1;
                    }
                    else if((player2.special == 0) && (player2.charge == 1))
                    {
                        player2.special = 1;
                        player2.charge = 2;
                    }
                } 
            }  
        }
    }

    if(event.type == SDL_KEYUP)
    {
        if(event.key.keysym.sym == SDLK_i)
        {
            player2.jump = 0;
        }
        if(event.key.keysym.sym == SDLK_j)
        {
            if(player2.xmovementdirection == -1)
            {
                player2.xmovementdirection = 0;
            }
            player2.tapstart.y = 0;
            player2.doubletap.y = 0;
        }
        else if(event.key.keysym.sym == SDLK_l)
        {
            if(player2.xmovementdirection == 1)
            {
                player2.xmovementdirection = 0;
            }
            player2.tapstart.x = 0;
            player2.doubletap.x = 0;
        }  
    }
}

void HandleP2Mouseinput(SDL_Event &event, player &player2, vector2i &mouse2keyboarddirection)
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_LEFT)
        {
            mouse2keyboarddirection.x = -1;
        }
        if(event.key.keysym.sym == SDLK_RIGHT)
        {
           mouse2keyboarddirection.x = 1;
        }
        if(event.key.keysym.sym == SDLK_DOWN)
        {   
           mouse2keyboarddirection.y = -1;
        }
        if(event.key.keysym.sym == SDLK_UP)
        {
            mouse2keyboarddirection.y = 1; 
        }
    }

    if(event.type == SDL_KEYUP)
    {
        if(event.key.keysym.sym == SDLK_LEFT)
        {
            if(mouse2keyboarddirection.x == -1)
            {
                mouse2keyboarddirection.x = 0;
            }
        }
        if(event.key.keysym.sym == SDLK_RIGHT)
        {
            if(mouse2keyboarddirection.x == 1)
            {
                mouse2keyboarddirection.x = 0;
            }                  
        }
        if(event.key.keysym.sym == SDLK_DOWN)
        {   
            if(mouse2keyboarddirection.y == -1)
            {
                mouse2keyboarddirection.y = 0;
            }
        }
        if(event.key.keysym.sym == SDLK_UP)
        {
            if(mouse2keyboarddirection.y == 1)
            {
                mouse2keyboarddirection.y = 0;
            }
        }
    }  
}

void HandleP2ControllerMouse(SDL_Event &event, player &player2, vector2i &mouse2)
{
        if( event.type == SDL_JOYAXISMOTION )
        {

            if( event.jaxis.which == 0 )
            {                        
                if( event.jaxis.axis == MOUSEAXISX )
                {
                    //Left of dead zone
                    if( event.jaxis.value < -8000 )
                    {
                        mouse2.x += -45;
                    }
                    //Right of dead zone
                    else if( event.jaxis.value > 8000 )
                    {
                        mouse2.x +=  45;
                    }
                }
                if( event.jaxis.axis == MOUSEAXISY )
                {
                    //Below of dead zone
                    if( event.jaxis.value < -8000 )
                    {
                        mouse2.y += -45;
                    }
                    //Above of dead zone
                    else if( event.jaxis.value > 8000 )
                    {
                        mouse2.y +=  45;
                    }
                }
            }
        }  
}

void HandleP2ControllerMovement(SDL_Event &event, player &player2)
{
    if(event.type == SDL_JOYHATMOTION)
    {
        ////log << << (event.jhat.hat) << std::endl; 
        switch (event.jhat.value)
        {           
            case SDL_HAT_LEFTUP:
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {   
                    player2.xmovementdirection = -1;
                }
                break;
            case SDL_HAT_UP:
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {  
                    if(player2.jump == 0)
                    {
                        player2.jump = 1;                                                                  
                    }   
                }            
                break;
            case SDL_HAT_RIGHTUP:
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {  
                    player2.xmovementdirection = 1;
                }
                break;
            case SDL_HAT_LEFT:
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {  
                    player2.xmovementdirection = -1;
                }
                break;
            case SDL_HAT_RIGHT:
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {  
                    player2.xmovementdirection = 1;
                }
                break;
            case SDL_HAT_LEFTDOWN:
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {  
                    player2.xmovementdirection = -1;
                }
                break;
            case SDL_HAT_DOWN:
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {            
                    if((player2.velocity.y < -FASTFALLLIMIT) && (player2.fastfalling == 0))
                    {
                        player2.fastfalling = 1;
                    }    
                }             
                break;
            case SDL_HAT_RIGHTDOWN:
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {
                    player2.xmovementdirection = 1;
                }
                break;         
            case SDL_HAT_CENTERED:
                player2.xmovementdirection = 0;
            default:
                break;
        }
    }

    if( event.type == SDL_JOYAXISMOTION )
    {
        if( event.jaxis.which == 0 )
        {                                    
            if( event.jaxis.axis == MOVEMENTAXISX )
            {
                //Left of dead zone
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {
                    if( event.jaxis.value < -8000 )
                    {
                        player2.xmovementdirection = -1;
                    }
                    //Right of dead zone
                    else if( event.jaxis.value > 8000 )
                    {
                        player2.xmovementdirection = 1;
                    }
                    else
                    {
                        player2.xmovementdirection = 0;
                    }
                }
            }
            if( event.jaxis.axis == MOVEMENTAXISY )
            {
                //Below of dead zone
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {
                    if( event.jaxis.value < -8000 )
                    {
                    }
                    //Above of dead zone
                    else if( event.jaxis.value > 8000 )
                    {
                        if((player2.velocity.y < -FASTFALLLIMIT) && (player2.fastfalling == 0))
                        {
                            player2.fastfalling = 1;
                        }     
                    }
                }
            }
        }
    }
}

void HandleP2ControllerButtons(SDL_Event &event, player &player2)
{
    if(event.type == SDL_JOYBUTTONDOWN)
    {
        //buttondown = 1;
        ////log << << event.jbutton.button << std::endl;
        if(event.jbutton.button > 0)
        {
            int e = event.jbutton.button;
            //log << << e << std::endl;
            if(e == JUMPBUTTON) //JUMP
            {
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {
                    if(player2.jump == 0)
                    {
                        player2.jump = 1;                                                                  
                    }  
                } 
            }
            if(e == SPECIALBUTTON) //SPECIAL MOVE
            {
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {
                    if(player2.specialmove == 1)
                    {
                        if((player2.special == 0)&& ((player2.GetTicks-player2.specialstarttime)) > player2.specialcooldown)
                        {
                            player2.special = 1;
                        }
                    }
                    else if (player2.specialmove == 2)
                    {
                        if((player2.special == 0)&& ((player2.GetTicks-player2.specialstarttime) > player2.specialcooldown))
                        {
                            player2.special = 1;
                            player2.charge = 1;
                        }
                        else if((player2.special == 0) && (player2.charge == 1))
                        {
                            player2.special = 1;
                            player2.charge = 2;
                        }
                    }  
                } 
            }
            if(e == DASHBUTTON)//DASH
            {
                if(!player2.inhitstun && !player2.pause && player2.gamestart == 0)
                {
                    if(((player2.GetTicks - player2.doubletapstarttime) > player2.doubletaptimelimit))
                    {
                        if(player2.flip == SDL_FLIP_NONE)
                        {
                            player2.doubletap.x = 2;
                        }
                        else if(player2.flip == SDL_FLIP_HORIZONTAL)
                        {
                            player2.doubletap.y = 2;
                        }
                    }
                }
            }
        }

    }
}

void HandleP2ControllerInput(SDL_Event &event, player &player2, vector2i &mouse2)
{
    HandleP2ControllerMouse(event, player2, mouse2);
    HandleP2ControllerMovement(event, player2);
    HandleP2ControllerButtons(event, player2);
}

void HandleP1Input(SDL_Event &event, player &player1)
{
    HandleP1Movement(event, player1);
}

void HandleP2Input(SDL_Event &event, player &player2, vector2i &mouse2keyboarddirection)
{
    HandleP2Movement(event, player2);
    HandleP2Mouseinput(event, player2, mouse2keyboarddirection);

}

void HandlePauseInput(SDL_Event &event, player &player1, player &player2, int &gaming, vector2i &mouse, vector2i &mouse2, int &pausetime, int &totalpausetime, HANDLE &m1, HANDLE &m2, RAWINPUTDEVICELIST *&pRawInputDeviceList)
{
    if((event.type == SDL_KEYDOWN) || (event.type == SDL_JOYBUTTONDOWN))
    {
        if(event.key.keysym.sym == SDLK_ESCAPE || (event.jbutton.button == PAUSEBUTTON))
        {
            setupmiceinput(m1, m2, pRawInputDeviceList);
            if(gaming == 3)
            {
                gaming = 1;
            }
            else
            {
                if(player1.pause == 0)
                {
                    player1.pause = 1;  
                    player2.pause = 1;   
                    player1.pausepressed = 1;
                    player2.pausepressed = 1;
                    player1.pausemousecoords = mouse;
                    player2.pausemousecoords = mouse2;
                    player1.pausexmovementdirection = player1.xmovementdirection;    
                    player2.pausexmovementdirection = player2.xmovementdirection;   
                    Mix_Pause(-1);  
                    pausetime = SDL_GetTicks();                                                       
                }
                else
                {
                    Mix_VolumeMusic(60);
                    mouse = player1.pausemousecoords;
                    mouse2 = player2.pausemousecoords;
                    player1.pause = 0;
                    player2.pause = 0;
                    Mix_Resume(-1);  
                    totalpausetime += (SDL_GetTicks() - pausetime);
                }
            }
        }
    }
}

void HandleInput(SDL_Event &event, int &quit, int &gaming, int &mousedown, vector2i &mouse, vector2i &mouse2, vector2i &mouse2keyboarddirection, SDL_Joystick* gGameController, player &player1, player &player2,  int &pausetime, int &totalpausetime, HANDLE &m1, HANDLE &m2, RAWINPUTDEVICELIST *&pRawInputDeviceList, viewport &viewport, SDL_Window * window)
{
    int p1inhitstun = player1.inhitstun;
    int p2inhitstun = player2.inhitstun;
    float fastfalllimit = -1;
    int buttondown = 0;
    

    while(SDL_PollEvent(&event) !=0 )
    {
        if(event.type == SDL_QUIT)
        {
            Mix_CloseAudio();
            Mix_Quit();
            SDL_JoystickClose( gGameController );
            gGameController = NULL;
            SDL_DestroyWindow(window);
            quit = 1;
        }


        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            buttondown = 1;
            
 
        } 

        
            HandlePauseInput(event, player1, player2, gaming, mouse, mouse2, pausetime, totalpausetime, m1, m2, pRawInputDeviceList);
            HandleP1Input(event, player1);
            HandleP2Input(event, player2, mouse2keyboarddirection);  
            HandleP2ControllerInput(event, player2, mouse2);

    }


}

void lockCursor(vector2i &mouse)
{
    if(mouse.x > 960)
    {
        mouse.x = 960;
    }
    if(mouse.x < 0)
    {
        mouse.x = 0;
    }
    if(mouse.y > 540)
    {
        mouse.y = 540;
    }
    if(mouse.y < 0)
    {
        mouse.y = 0;
    }
}

