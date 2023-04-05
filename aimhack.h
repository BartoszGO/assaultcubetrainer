#pragma once

#include "Entity.h"
#include "Game.h"

Entity calculateMinDistanceEntity(Game game);
void setPlayerAngleToEntity(Game game, Entity entity);
void setPlayerAngleToMinDistanceEntity(Game game);
Entity getClosestEntityToCrosshair(Game game);
void setPlayerAngleToMinCrosshairDistanceEntity(Game game);
