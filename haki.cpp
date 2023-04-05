
#include <iostream>
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "vecutils.h"
#include "Process.h"
#include "Game.h"
#include "aimhack.h"




int main()
{
    const wchar_t* procName = L"ac_client.exe";
    Process process(procName, procName);
    Game game(process);
    while (true)
    {

        while (GetAsyncKeyState(VK_RBUTTON) < 0)
        {
            setPlayerAngleToMinDistanceEntity(process, game);
        }

        Sleep(10);
    }

    return 1;
        
}

