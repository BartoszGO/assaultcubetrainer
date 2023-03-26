// haki.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "memproc.h"
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <WinUser.h>


enum returnValues
{
    RET_OK,
    RET_NOT_OK,
};

bool writeMemory(HANDLE handle, uintptr_t addr, void* buffer, unsigned int size)
{
    return WriteProcessMemory(handle, (LPVOID)addr, (LPCVOID)buffer, size, NULL);
}


bool readMemory(HANDLE handle, uintptr_t addr, void* buffer, unsigned int size)
{
    return ReadProcessMemory(handle, (LPCVOID)addr, (LPVOID)buffer, size, NULL);
}


struct vec3
{
    float x, y, z;
};

void movePlayer(HANDLE hProc, uintptr_t positionAddr, uintptr_t pitchAddr, uintptr_t yawAddr)
{
    float pitch, yaw, angleModifier;
    vec3 pos;
    vec3 newPos{};
    readMemory(hProc, positionAddr, &pos, sizeof(pos));
    readMemory(hProc, pitchAddr, &pitch, sizeof(pitch));
    readMemory(hProc, yawAddr, &yaw, sizeof(yaw));

    newPos.x = pos.x;
    newPos.y = pos.y;
    newPos.z = pos.z;

    if (GetAsyncKeyState('W'))
    {
        newPos.x = static_cast<float>(pos.x + 0.4f * cos(((pitch - 90.0f) * M_PI) / 180));
        newPos.y = static_cast<float>(pos.y + 0.4f * sin(((pitch - 90.0f) * M_PI) / 180));

    }
    if (GetAsyncKeyState('S'))
    {
        newPos.x = static_cast<float>(pos.x - 0.4f * cos(((pitch - 90.0f) * M_PI) / 180));
        newPos.y = static_cast<float>(pos.y - 0.4f * sin(((pitch - 90.0f) * M_PI) / 180));

    }
    if (GetAsyncKeyState('D'))
    {
        newPos.x = static_cast<float>(pos.x + 0.4f * cos(((pitch) * M_PI) / 180));
        newPos.y = static_cast<float>(pos.y + 0.4f * sin(((pitch) * M_PI) / 180));

    }
    if (GetAsyncKeyState('A'))
    {
        newPos.x = static_cast<float>(pos.x - 0.4f * cos(((pitch) * M_PI) / 180));
        newPos.y = static_cast<float>(pos.y - 0.4f * sin(((pitch) * M_PI) / 180));

    }

    



    
   
    newPos.z = pos.z+ yaw / 90;

    writeMemory(hProc, positionAddr, &newPos, sizeof(newPos));
 }


int main()
{
    DWORD ProcId = NULL;
    uintptr_t moduleAddr = NULL;
    const wchar_t* procName = L"ac_client.exe";
    HANDLE hProc = NULL;
    int health = 2000;
    uintptr_t healthAddr = NULL;
    uintptr_t posAddr = NULL;
    uintptr_t pitchAddr = NULL;
    uintptr_t yawAddr = NULL;
    uintptr_t playerBasePtrAddr = 0x17E0A8;
    std::vector<unsigned int> healthOffsets{ 0xEC };
    std::vector<unsigned int> pitchOffsets{ 0x34 };
    std::vector<unsigned int> yawOffsets{ 0x38 };
    std::vector<unsigned int> posOffsets{ 0x28 };

    uintptr_t temp = NULL;


    ProcId = GetProcessId(procName);
    if (NULL != ProcId)
    {
        std::cout << "Process ID retrieved: " << ProcId << std::endl;
        hProc = OpenProcess(PROCESS_ALL_ACCESS, false, ProcId);
        moduleAddr = GetModuleBaseAddress(ProcId, procName);
    }
    if (NULL != moduleAddr && NULL != hProc)
    {
        
        healthAddr = FindDynamicAddr2(hProc, moduleAddr + playerBasePtrAddr, healthOffsets);
        pitchAddr = FindDynamicAddr2(hProc, moduleAddr + playerBasePtrAddr, pitchOffsets);
        yawAddr = FindDynamicAddr2(hProc, moduleAddr + playerBasePtrAddr, yawOffsets);
        posAddr = FindDynamicAddr2(hProc, moduleAddr + playerBasePtrAddr, posOffsets);
        writeMemory(hProc, healthAddr, &health, sizeof(health));

        while (1)

        {
            movePlayer(hProc, posAddr, pitchAddr, yawAddr);
            Sleep(1);
        }
    }


   


  
    std::cout << "Hello World!\n";
}

