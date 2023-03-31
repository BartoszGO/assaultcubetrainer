#include "aimhack.h"
#include <iostream>
#include "memproc.h"
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <WinUser.h>

#include "vecutils.h"


uintptr_t calculateMinDistanceEntity()
{
    uintptr_t entityPtr = NULL;
    uintptr_t minDistanceEntityPtr = NULL;


    char entityName[15];
    int16_t entityHealth = 0;
    int16_t health = 0;
    point3 playerPos{};
    point3 entityPos{};
    float distance = 0;
    float minDistance = FLT_MAX;

    readMemory(playerBasePtr + offsets.pos, &playerPos, sizeof(playerPos));

    for (uint8_t i = 1; i < numPlayers; i++)
    {

        readMemory(entityListPtr + i * 4, &entityPtr, sizeof(entityPtr));
        readMemory(entityPtr + offsets.pos, &entityPos, sizeof(entityPos));
        readMemory(entityPtr + offsets.health, &entityHealth, sizeof(entityHealth));

        distance = calculatePoint3Distance(playerPos, entityPos);
        if (minDistance > distance && entityHealth > 0)
        {
            minDistance = distance;
            minDistanceEntityPtr = entityPtr;

        }
    }
    return minDistanceEntityPtr;

}


void setPlayerAngleToEntity(uintptr_t entityPtr)
{
    float destinationPitch = 0;
    float destinationYaw = 0;
    point3 playerPos{};
    point3 entityPos{};
    readMemory(playerBasePtr + offsets.pos, &playerPos, sizeof(playerPos));
    readMemory(entityPtr + offsets.pos, &entityPos, sizeof(entityPos));

    destinationPitch = fmod(((atan2(playerPos.y - entityPos.y, playerPos.x - entityPos.x) * 180 / M_PI)) + 270.0f, 360.0f);
    destinationYaw = (atan2(calculateTriangleBase(playerPos, entityPos), playerPos.z - entityPos.z) * 180 / M_PI) - 90.0f;


    writeMemory(playerBasePtr + offsets.pitch, &destinationPitch, sizeof(destinationPitch));
    writeMemory(playerBasePtr + offsets.yaw, &destinationYaw, sizeof(destinationYaw));
}

void setPlayerAngleToMinDistanceEntity()
{
    uintptr_t minDstcEntityPtr = NULL;
    float playerPitch = 0, playerYaw = 0;

    minDstcEntityPtr = calculateMinDistanceEntity();
    if (NULL != minDstcEntityPtr)
    {
        setPlayerAngleToEntity(minDstcEntityPtr);
    }


}



uintptr_t getClosestEntityToCrosshair()
{
    float pitch = 0, yaw = 0, angleModifier = 0;
    float  xMovementSum = 0, yMovementSum = 0;
    float speed = 5;
    float thresholdDistance = 3.0f;

    vec3 pos{};
    vec3 newPos{};
    vec3 movementVector{};
    float distance = 0;
    float minDistance = FLT_MAX;
    float distanceTraveled = 0;
    uintptr_t entityPtr = NULL;
    uintptr_t minDistanceEntityPtr = NULL;
    vec3 entityPos{};
    int16_t entityHealth = 0;
    readMemory(playerBasePtr + offsets.pos, &newPos, sizeof(newPos));
    readMemory(playerBasePtr + offsets.pitch, &pitch, sizeof(pitch));
    readMemory(playerBasePtr + offsets.yaw, &yaw, sizeof(yaw));
    movementVector.x = static_cast<float>(movementVector.x + 1.0f * cos(((pitch - 90.0f) * M_PI) / 180));
    movementVector.y = static_cast<float>(movementVector.y + 1.0f * sin(((pitch - 90.0f) * M_PI) / 180));
    movementVector.z = static_cast<float>(calculateVec3BaseLength(movementVector) * (tan(((yaw)*M_PI / 180))));

    (void)normaliseVector(movementVector);
    movementVector.x *= speed;
    movementVector.y *= speed;
    movementVector.z *= speed;


    while (distanceTraveled < 300.0f)
    {




        newPos.x += movementVector.x;
        newPos.y += movementVector.y;
        newPos.z += movementVector.z;


        //std::cout << newPos.x <<": " << newPos.y<< ": " <<newPos.z << std::endl;
        distanceTraveled += calculateVec3Length(movementVector);
        //std::cout <<distanceTraveled << std::endl;

        for (uint8_t i = 1; i < numPlayers; i++)
        {
            readMemory(entityListPtr + i * 4, &entityPtr, sizeof(entityPtr));
            readMemory(entityPtr + offsets.pos, &entityPos, sizeof(entityPos));
            readMemory(entityPtr + offsets.health, &entityHealth, sizeof(entityHealth));

            distance = calculateVec3Distance(newPos, entityPos);

            if (minDistance > distance && entityHealth > 0 && distance < thresholdDistance)
            {
                minDistance = distance;
                minDistanceEntityPtr = entityPtr;


            }
        }

    }

    return minDistanceEntityPtr;




}
void setPlayerAngleToMinCrosshairDistanceEntity()
{
    uintptr_t minDstcEntityPtr = NULL;
    float playerPitch = 0, playerYaw = 0;

    minDstcEntityPtr = getClosestEntityToCrosshair();
    if (NULL != minDstcEntityPtr)
    {
        setPlayerAngleToEntity(minDstcEntityPtr);
    }


}