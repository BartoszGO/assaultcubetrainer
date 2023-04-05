#include "Entity.h"
#include "data.h"
#include "vecutils.h"


Entity::Entity()
{
	_process = NULL;
	_entBasePtr = NULL;

}

Entity::Entity(Process* process)
{
	_process = process;
	_entBasePtr = NULL;

}


int32_t Entity::getHealth()
{
	uint32_t health = 0;
	
	_process->readMemory(_entBasePtr + offsets::health, &health, sizeof(health));
	return health;
}

point3 Entity::getPos()
{
	point3 pos{};
	_process->readMemory(_entBasePtr + offsets::pos, &pos, sizeof(pos));
	return pos;
}

angle Entity::getAngles()
{
	angle angles{};
	_process->readMemory(_entBasePtr + offsets::pitch, &angles, sizeof(angles));
	return angles;
}

bool Entity::setAngles(angle angles)
{
	return _process->writeMemory(_entBasePtr + offsets::pitch, &angles, sizeof(angles));
}


void Entity::setEntBaseAddr(uintptr_t addr) 
{
	_entBasePtr = addr;
}

uintptr_t Entity::getEntBaseAddr()
{
	return _entBasePtr;
}



Entity& Entity::operator = (const Entity& entity)
{
	_entBasePtr = entity._entBasePtr;
	_process = entity._process;

	return *this;
}




