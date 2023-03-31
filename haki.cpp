
#include <iostream>
#include "memproc.h"
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <WinUser.h>

#include "vecutils.h"






struct Offsets
{
    uintptr_t  health = 0xEC;
    uintptr_t  pitch = 0x34;
    uintptr_t  yaw = 0x38;
    uintptr_t  pos = 0x28;
    uintptr_t name = 0x205;
};


struct Addreses
{
    uintptr_t playerBasePtrAddr = 0x17E0A8;
    uintptr_t entityListPtrAddr = 0x18AC04;
    uintptr_t numPlayersAddr = 0x18AC0C;
};

struct ClientInfo
{
    DWORD ProcId = NULL;
    uintptr_t moduleAddr = NULL;
    HANDLE hProc = NULL;

};

struct GameInfo
{
    uintptr_t playerBasePtr = NULL;
    uintptr_t entityListPtr = NULL;
    uint16_t numPlayers = 0;
};




static const wchar_t* procName = L"ac_client.exe";
static Offsets offsets;
static Addreses addreses;




enum returnValues
{
    RET_OK,
    RET_NOT_OK,
};

bool writeMemory(uintptr_t addr, void* buffer, unsigned int size)
{
    return WriteProcessMemory(hProc, (LPVOID)addr, (LPCVOID)buffer, size, NULL);
}


bool readMemory(uintptr_t addr, void* buffer, unsigned int size)
{
    return ReadProcessMemory(hProc, (LPCVOID)addr, (LPVOID)buffer, size, NULL);
}




void initializeFileScopeVars()
{
    

    readMemory(addreses.playerBasePtrAddr, &playerBasePtr, sizeof(playerBasePtr));
    readMemory(addreses.entityListPtrAddr, &entityListPtr, sizeof(entityListPtr));
    readMemory(addreses.numPlayersAddr, &numPlayers, sizeof(numPlayers));
    

}




void movePlayer()
{
    float pitch = 0, yaw = 0, angleModifier = 0;
    float  xMovementSum = 0, yMovementSum = 0;
    float speed = 1;
    vec3 pos{};
    vec3 newPos{};
    vec3 movementVector{};

    readMemory(playerBasePtr + offsets.pos, &pos, sizeof(pos));
    readMemory(playerBasePtr + offsets.pitch, &pitch, sizeof(pitch));
    readMemory(playerBasePtr + offsets.yaw, &yaw, sizeof(yaw));

   

   if (GetAsyncKeyState('W'))
   {
       movementVector.x = static_cast<float>(movementVector.x + 1.0f * cos(((pitch - 90.0f) * M_PI) / 180));
       movementVector.y = static_cast<float>(movementVector.y + 1.0f * sin(((pitch - 90.0f) * M_PI) / 180));

   }
    if (GetAsyncKeyState('S'))
    {
        movementVector.x = static_cast<float>(movementVector.x -  1.0f * cos(((pitch - 90.0f) * M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y -  1.0f * sin(((pitch - 90.0f) * M_PI) / 180));

    }
    if (GetAsyncKeyState('D'))
    {
        movementVector.x = static_cast<float>(movementVector.x +  1.0f * cos(((pitch) * M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y +  1.0f * sin(((pitch) * M_PI) / 180));

    }
    if (GetAsyncKeyState('A'))
    {
       movementVector.x = static_cast<float>(movementVector.x -  1.0f * cos(((pitch) * M_PI) / 180));
       movementVector.y = static_cast<float>(movementVector.y -  1.0f * sin(((pitch) * M_PI) / 180));

    }

    movementVector.z = static_cast<float>(calculateVec3BaseLength(movementVector) * (tan(((yaw)*M_PI / 180))));
   
    (void)normaliseVector(movementVector);
    newPos.x = pos.x + movementVector.x * speed;
    newPos.y = pos.y + movementVector.y * speed;
    newPos.z = pos.z + movementVector.z * speed;

   

    writeMemory(playerBasePtr + offsets.pos, &newPos, sizeof(newPos));
 }


void addModuleAddr()
{
    uintptr_t attributeAddr = NULL;
    uint8_t numAttr = sizeof(addreses) / sizeof(uintptr_t);
    for (uint8_t i = 0; i < numAttr; i++)
    {
        attributeAddr = (uintptr_t)(&addreses) + sizeof(uintptr_t) * i;
        *(uintptr_t*)attributeAddr = *(uintptr_t*)attributeAddr + moduleAddr;
    }
}


void printEachHealth()
{

    uintptr_t entityPtr = NULL;
    int16_t health = 0;

    for (uint8_t i = 0; i < numPlayers; i++)
    {
        readMemory(entityListPtr + 4 * i, &entityPtr, sizeof(entityPtr));
        readMemory(entityPtr + offsets.health, &health, sizeof(health));
        

    }
    system("CLS");
  

}













int main()
{
    
    
    ProcId = GetProcessId(procName);
    if (NULL != ProcId)
    {
        std::cout << "Process ID retrieved: " << ProcId << std::endl;
        hProc = OpenProcess(PROCESS_ALL_ACCESS, false, ProcId);
        moduleAddr = GetModuleBaseAddress(ProcId, procName);
    }
    if (NULL != moduleAddr && NULL != hProc)
    {

        addModuleAddr();
        initializeFileScopeVars();
   
        while (1)

        {
            if (GetAsyncKeyState(VK_RBUTTON) < 0)
            {
                //movePlayer();
                //setPlayerAngleToMinEntity();
                setPlayerAngleToMinCrosshairDistanceEntity();
            }
           
            Sleep(10);
        }

        
    }


    std::cout << "Hello World!\n";
}

