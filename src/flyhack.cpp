#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "flyhack.h"
#include "vecutils.h"
#include "Entity.h"
#include "Game.h"

void movePlayer(Game game)
{
    float speed = 1;
    angle playerAngle{};
    vec3 pos{};
    vec3 newPos{};
    vec3 movementVector{};
    
    Entity player;
    game.getLocalPlayer(player);
    pos = player.getPos();
    playerAngle = player.getAngles();
    


    if (GetAsyncKeyState('W'))
    {
        movementVector.x = static_cast<float>(movementVector.x + 1.0f * cos(((playerAngle.pitch - 90.0f) * M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y + 1.0f * sin(((playerAngle.pitch - 90.0f) * M_PI) / 180));
        movementVector.z = static_cast<float>(calculateVec3BaseLength(movementVector) * (tan(((playerAngle.yaw) * M_PI / 180))));

    }
    if (GetAsyncKeyState('S'))
    {
        movementVector.x = static_cast<float>(movementVector.x - 1.0f * cos(((playerAngle.pitch - 90.0f) * M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y - 1.0f * sin(((playerAngle.pitch - 90.0f) * M_PI) / 180));
        movementVector.z = -1.0f * static_cast<float>(calculateVec3BaseLength(movementVector) * (tan(((playerAngle.yaw) * M_PI / 180))));

    }
    if (GetAsyncKeyState('D'))
    {
        movementVector.x = static_cast<float>(movementVector.x + 1.0f * cos(((playerAngle.pitch)*M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y + 1.0f * sin(((playerAngle.pitch)*M_PI) / 180));

    }
    if (GetAsyncKeyState('A'))
    {
        movementVector.x = static_cast<float>(movementVector.x - 1.0f * cos(((playerAngle.pitch)*M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y - 1.0f * sin(((playerAngle.pitch)*M_PI) / 180));

    }
    if (GetAsyncKeyState(VK_SPACE))
    {
        movementVector.z += 1.0f;

    }
    if (GetAsyncKeyState(VK_LCONTROL))
    {
        movementVector.z -= 1.0f;

    }
    

   

    (void)normaliseVector(movementVector);
    newPos.x = pos.x + movementVector.x * speed;
    newPos.y = pos.y + movementVector.y * speed;
    newPos.z = pos.z + movementVector.z * speed;



    player.setPos(newPos);
}
