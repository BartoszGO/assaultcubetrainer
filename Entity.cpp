#include "Entity.h"
#include "data.h"
#include "vecutils.h"


Entity::Entity(Process process, bool isMainPlayer = false): _process(process)
{
	
	_entBasePtr = NULL;
	_mainModuleAddr = _process.getMainModuleAddr();
	if (isMainPlayer)
	{
		getMainPlayerBaseAddr();
	}


}

int32_t Entity::getHealth()
{
	uint32_t health = 0;
	
	_process.readMemory(_entBasePtr + offsets::health, &health, sizeof(health));
	return health;
}

point3 Entity::getPos()
{
	point3 pos{};
	_process.readMemory(_entBasePtr + offsets::pos, &pos, sizeof(pos));
	return pos;
}

angle Entity::getAngles()
{
	angle angles{};
	_process.readMemory(_entBasePtr + offsets::pitch, &angles, sizeof(angles));
	return angles;
}

void Entity::getMainPlayerBaseAddr()
{
	uintptr_t temp = 0;
	_process.readMemory(_mainModuleAddr + addreses::playerBasePtrAddr, &temp, sizeof(temp));
	_entBasePtr = temp;
}

void Entity::setEntBaseAddr(uintptr_t addr) 
{
	_entBasePtr = addr;

}




