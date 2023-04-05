#include "Game.h"
#include "Entity.h"
#include "Process.h"
#include "data.h"
Game::Game(Process& process) : _process(process)
{
	_moduleAddr = _process.getMainModuleAddr();
	std::cout << "game constr:";
	_process.printhProc();
	
	
}


bool Game::getLocalPlayer(Entity& aEnt)
{
	bool retVal = false;
	Entity ent(&_process);
	uintptr_t localPlayerAddr = NULL;
	retVal = _process.readMemory(_moduleAddr + addreses::playerBasePtrAddr, &localPlayerAddr, sizeof(localPlayerAddr));
	ent.setEntBaseAddr(localPlayerAddr);
	aEnt = ent;

	return retVal;
	
}

bool Game::getNextEnt(Entity& aEnt)
{

	static uint8_t iterator = 0;
	uintptr_t entityListAddr = 0;
	uintptr_t entityPtr = NULL;
	Entity ent(&_process);
	bool returnVal = false;
	_process.readMemory(_moduleAddr + addreses::entityListPtrAddr, &entityListAddr, sizeof(entityListAddr) );
	

	if (iterator < getNumPlayers())
	{

		_process.readMemory(entityListAddr + iterator * 4, &entityPtr, sizeof(entityPtr));
		ent.setEntBaseAddr(entityPtr);
		returnVal = true;
		aEnt = ent;
		
	}
	else
	{
		returnVal = false;
		iterator = 0;
	}
	
	iterator++;
	return returnVal;
}




uint8_t Game::getNumPlayers()
{
	uint16_t numPlayers = 0;
	_process.readMemory(_moduleAddr + addreses::numPlayersAddr, &numPlayers, sizeof(numPlayers));
	return numPlayers;
}


