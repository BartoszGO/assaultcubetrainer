
#include <iostream>
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "vecutils.h"
#include "Process.h"
#include "Game.h"
#include "aimhack.h"
#include "flyhack.h"

#include "buttonconfig.h"


int main()
{
    
    Process process;
    Game game(process);
    bool isFlyingActive = false;
    while (true)
    {

        while (GetAsyncKeyState(AIMBOT_BTN) < 0)
        {
            setPlayerAngleToMinDistanceEntity(game);
        }

        if (GetAsyncKeyState(FLYHACK_BTN)) 
        {
            isFlyingActive? std::cout << "Flying is active!" << std::endl : std::cout << "Flying is not active!" << std::endl;
            
            isFlyingActive = !isFlyingActive;
        }


        if (isFlyingActive)
        {
            movePlayer(game);
        }

        Sleep(10);
    }

    return 1;
        
}

