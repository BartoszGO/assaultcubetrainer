#include "aimhack.h"
#include <Windows.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "vecutils.h"
#include "Entity.h"
#include "Game.h"


Entity calculateMinDistanceEntity(Game game)
{

    Entity minDistanceEntity;


    float distance = 0;
    float minDistance = FLT_MAX;
    Entity player;
    Entity ent;

    game.getLocalPlayer(player);


    while(game.getNextEnt(ent))
    {
        distance = calculatePoint3Distance(player.getPos(), ent.getPos());
        if (minDistance > distance && ent.getHealth() > 0)
        {
            minDistance = distance;
            minDistanceEntity = ent;

        }

    }
    return minDistanceEntity;

}

void setPlayerAngleToEntity(Game game, Entity entity)
{
    float destinationPitch = 0;
    float destinationYaw = 0;
    point3 playerPos{};
    point3 entityPos{};
    Entity player;
    game.getLocalPlayer(player);
    playerPos = player.getPos();
    entityPos = entity.getPos();

    destinationPitch = fmod(((atan2(playerPos.y - entityPos.y, playerPos.x - entityPos.x) * 180 / M_PI)) + 270.0f, 360.0f);
    destinationYaw = (atan2(calculateTriangleBase(playerPos, entityPos) , playerPos.z - entityPos.z ) * 180 / M_PI) - 90.0f;

    player.setAngles({ destinationPitch,destinationYaw });
}

void setPlayerAngleToMinDistanceEntity(Game game)
{ 
    setPlayerAngleToEntity(game , calculateMinDistanceEntity(game));
}



Entity getClosestEntityToCrosshair(Game game)
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
    Entity player;
    Entity ent;
    Entity minDistanceEntity;
    
    game.getLocalPlayer(player);
    pos = player.getPos();

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


        distanceTraveled += calculateVec3Length(movementVector);
        while(game.getNextEnt(ent))
        {

            distance = calculatePoint3Distance(newPos, ent.getPos());

            if (minDistance > distance && ent.getHealth() > 0 && distance < thresholdDistance)
            {
                minDistance = distance;
                minDistanceEntity = ent;


            }
        }

    }

    return minDistanceEntity;




}
void setPlayerAngleToMinCrosshairDistanceEntity(Game game)
{
    setPlayerAngleToEntity(game, getClosestEntityToCrosshair(game));
}