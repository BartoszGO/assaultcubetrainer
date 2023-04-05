#pragma once
#include<Windows.h>
#include "Process.h"
#include <iostream>

#include "vecutils.h"
class Entity
{
public:
	Entity();
	Entity(Process* process);
	int32_t getHealth();
	point3 getPos();
	angle getAngles();
	bool setAngles(angle angles);
	
	void setEntBaseAddr(uintptr_t addr);
	uintptr_t getEntBaseAddr();


	Entity& operator= (const Entity& entity);


private:
	uintptr_t _entBasePtr;
	Process* _process;


};

