// haki.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "memproc.h"
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <WinUser.h>

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


float calculateVectorLength(vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

void normaliseVector(vec3& v)
{
    float length = calculateVectorLength(v);
    if (length)
    {
        v.x = v.x / length;
        v.y = v.y / length;
    }
}


void movePlayer(HANDLE hProc, Addreses addreses, Offsets offsets)
{
    uintptr_t playerBasePtr = NULL;
    float pitch, yaw, angleModifier;
    float  xMovementSum = 0, yMovementSum = 0;
    float speed = 0.2;
    vec3 pos{};
    vec3 newPos{};
    vec3 movementVector{};

    readMemory(hProc, addreses.playerBasePtrAddr, &playerBasePtr, sizeof(playerBasePtr));
    readMemory(hProc, playerBasePtr + offsets.pos, &pos, sizeof(pos));
    readMemory(hProc, playerBasePtr + offsets.pitch, &pitch, sizeof(pitch));
    readMemory(hProc, playerBasePtr + offsets.yaw, &yaw, sizeof(yaw));

    newPos.x = pos.x;
    newPos.y = pos.y;
    newPos.z = pos.z;

    if (GetAsyncKeyState('W'))
    {
        newPos.x = static_cast<float>(newPos.x + 0.4f * cos(((pitch - 90.0f) * M_PI) / 180));
        newPos.y = static_cast<float>(newPos.y + 0.4f * sin(((pitch - 90.0f) * M_PI) / 180));

    }
    if (GetAsyncKeyState('S'))
    {
        newPos.x = static_cast<float>(newPos.x - 0.4f * cos(((pitch - 90.0f) * M_PI) / 180));
        newPos.y = static_cast<float>(newPos.y - 0.4f * sin(((pitch - 90.0f) * M_PI) / 180));

    }
    if (GetAsyncKeyState('D'))
    {
        newPos.x = static_cast<float>(newPos.x + 0.4f * cos(((pitch) * M_PI) / 180));
        newPos.y = static_cast<float>(newPos.y + 0.4f * sin(((pitch) * M_PI) / 180));

    }
    if (GetAsyncKeyState('A'))
    {
        newPos.x = static_cast<float>(newPos.x - 0.4f * cos(((pitch) * M_PI) / 180));
        newPos.y = static_cast<float>(newPos.y - 0.4f * sin(((pitch) * M_PI) / 180));

    }

    movementVector.x = newPos.x - pos.x;
    movementVector.y = newPos.y - pos.y;
    (void)normaliseVector(movementVector);
    newPos.x = pos.x + movementVector.x * speed;
    newPos.y = pos.y + movementVector.y * speed;
  
    
    newPos.z = pos.z + yaw / 90;


    writeMemory(hProc, playerBasePtr + offsets.pos, &newPos, sizeof(newPos));
 }


void addModuleAddr(uintptr_t moduleAddr, Addreses& addrs)
{
    uintptr_t attributeAddr = NULL;
    uint8_t numAttr = sizeof(addrs) / sizeof(uintptr_t);
    for (uint8_t i = 0; i < numAttr; i++)
    {
        attributeAddr = (uintptr_t)(&addrs) + sizeof(uintptr_t) * i;
        *(uintptr_t*)attributeAddr = *(uintptr_t*)attributeAddr + moduleAddr;
    }
}


void printEachHealth(HANDLE hProc, Addreses addreses, Offsets offsets)
{
    uintptr_t entityListPtr = NULL;
    uint16_t numPlayers = 0;
    uintptr_t entityPtr = NULL;
    int16_t health = 0;
    readMemory(hProc, addreses.entityListPtrAddr, &entityListPtr, sizeof(entityListPtr));
    readMemory(hProc, addreses.numPlayersAddr, &numPlayers, sizeof(numPlayers));

    for (uint8_t i = 0; i < numPlayers; i++)
    {
        readMemory(hProc, entityListPtr + 4 * i, &entityPtr, sizeof(entityPtr));
        readMemory(hProc, entityPtr + offsets.health, &health, sizeof(health));
        std::cout << health << std::endl;
        

    }
    system("CLS");
  

}

float calculateVec3Distance(vec3 a, vec3 b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z)* (a.z - b.z));
}

uintptr_t calculateMinDistanceEntity(HANDLE hProc, Addreses addreses, Offsets offsets)
{
    uintptr_t playerBasePtr = NULL;
    uintptr_t entityListPtr = NULL;
    uintptr_t entityPtr = NULL;
    uintptr_t minDistanceEntityPtr = NULL;
    
    
    char entityName[15];
    int16_t entityHealth = 0;
    int16_t health = 0;
    uint16_t numPlayers = 0;
    vec3 playerPos{};
    vec3 entityPos{};
    float distance = 0;
    float minDistance = FLT_MAX;

    readMemory(hProc, addreses.playerBasePtrAddr, &playerBasePtr, sizeof(playerBasePtr));
    readMemory(hProc, addreses.entityListPtrAddr, &entityListPtr, sizeof(entityListPtr));
    readMemory(hProc, addreses.numPlayersAddr, &numPlayers, sizeof(numPlayers));
    readMemory(hProc, playerBasePtr + offsets.pos, &playerPos, sizeof(playerPos));

    for (uint8_t i = 1; i < numPlayers; i++)
    {

        readMemory(hProc, entityListPtr + i * 4 , &entityPtr, sizeof(entityPtr));
        readMemory(hProc, entityPtr + offsets.pos, &entityPos, sizeof(entityPos));
        readMemory(hProc, entityPtr + offsets.health, &entityHealth, sizeof(entityHealth));
        readMemory(hProc, entityPtr + offsets.name, &entityName, sizeof(entityName)/sizeof(entityName[0]));

        distance = calculateVec3Distance(playerPos, entityPos);
        if (minDistance > distance && entityHealth > 0)
        {
            minDistance = distance;
            minDistanceEntityPtr = entityPtr;
        }
    }
    return minDistanceEntityPtr;

}



void setPlayerAngleToMinEntity(HANDLE hProc, Addreses addreses, Offsets offsets)
{
    uintptr_t minDstcEntityPtr = NULL;
    uintptr_t playerBasePtr = NULL;


    float playerPitch = 0, playerYaw = 0;
    float destinationPitch = 0;
    float destinationYaw = 0;
    vec3 playerPos{};
    vec3 entityPos{};


    minDstcEntityPtr = calculateMinDistanceEntity(hProc, addreses, offsets);
    

    if (NULL != minDstcEntityPtr)
    {

        readMemory(hProc, addreses.playerBasePtrAddr, &playerBasePtr, sizeof(playerBasePtr));
        readMemory(hProc, playerBasePtr + offsets.pos, &playerPos, sizeof(playerPos));
        readMemory(hProc, minDstcEntityPtr + offsets.pos, &entityPos, sizeof(entityPos));
        //readMemory(hProc, playerBasePtr + offsets.pitch, &playerPitch, sizeof(playerPitch));
        //readMemory(hProc, playerBasePtr + offsets.yaw, &playerYaw, sizeof(playerYaw));

        destinationPitch = -1 * (atan2(playerPos.x - entityPos.x, playerPos.y - entityPos.y) * 180/M_PI) ;
        destinationYaw =  (atan2(calculateVec3Distance(playerPos,entityPos),playerPos.z - entityPos.z) * 180 / M_PI) - 90.0f;
        std::cout << "pitch: " << destinationPitch << " yaw:" << destinationYaw << std::endl;
        writeMemory(hProc, playerBasePtr + offsets.pitch, &destinationPitch, sizeof(destinationPitch));
        writeMemory(hProc, playerBasePtr + offsets.yaw, &destinationYaw, sizeof(destinationYaw));
    }


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
    uintptr_t playerBasePtr = NULL;
    Offsets offsets;
    Addreses addreses;

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

        addModuleAddr(moduleAddr, addreses);
       
   
        while (1)

        {
            

            setPlayerAngleToMinEntity(hProc, addreses, offsets);
           
            Sleep(10);
        }

        
    }


    std::cout << "Hello World!\n";
}

