#pragma once
#include <iostream>
#include "Process.h"
#include "Game.h"
#include "Entity.h"

class Game
{
public:
	Game(Process& process);
	uint8_t getNumPlayers();
	bool getLocalPlayer(Entity& aEnt);
	bool getNextEnt(Entity& aEnt);
	Process getProcess();

	Process& _process;
private:
	uintptr_t _moduleAddr;
};

