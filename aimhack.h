#pragma once
#include <Windows.h>
uintptr_t calculateMinDistanceEntity();
void setPlayerAngleToEntity(uintptr_t entityPtr);
void setPlayerAngleToMinDistanceEntity();
uintptr_t getClosestEntityToCrosshair();
void setPlayerAngleToMinCrosshairDistanceEntity();
