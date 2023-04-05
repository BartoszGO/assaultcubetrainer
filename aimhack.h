#pragma once
#include <Windows.h>
#include "aimhack.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include "vecutils.h"
#include "Process.h"
#include "Entity.h"
#include "Game.h"

Entity calculateMinDistanceEntity(Game game);
void setPlayerAngleToEntity(Process process, Game game, Entity entity);
void setPlayerAngleToMinDistanceEntity(Process process, Game game);
Entity getClosestEntityToCrosshair(Process process, Game game);
void setPlayerAngleToMinCrosshairDistanceEntity(Process process, Game game);
