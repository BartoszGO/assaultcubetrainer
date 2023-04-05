/*
#include "vecutils.h"


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
        movementVector.x = static_cast<float>(movementVector.x - 1.0f * cos(((pitch - 90.0f) * M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y - 1.0f * sin(((pitch - 90.0f) * M_PI) / 180));

    }
    if (GetAsyncKeyState('D'))
    {
        movementVector.x = static_cast<float>(movementVector.x + 1.0f * cos(((pitch)*M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y + 1.0f * sin(((pitch)*M_PI) / 180));

    }
    if (GetAsyncKeyState('A'))
    {
        movementVector.x = static_cast<float>(movementVector.x - 1.0f * cos(((pitch)*M_PI) / 180));
        movementVector.y = static_cast<float>(movementVector.y - 1.0f * sin(((pitch)*M_PI) / 180));

    }

    movementVector.z = static_cast<float>(calculateVec3BaseLength(movementVector) * (tan(((yaw)*M_PI / 180))));

    (void)normaliseVector(movementVector);
    newPos.x = pos.x + movementVector.x * speed;
    newPos.y = pos.y + movementVector.y * speed;
    newPos.z = pos.z + movementVector.z * speed;



    writeMemory(playerBasePtr + offsets.pos, &newPos, sizeof(newPos));
}


*/