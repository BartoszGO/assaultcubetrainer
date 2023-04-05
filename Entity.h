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
	bool setPos(point3 pos);
	angle getAngles();
	bool setAngles(angle angles);
	
	void setEntBaseAddr(uintptr_t addr);
	uintptr_t getEntBaseAddr();


private:
	uintptr_t _entBasePtr;
	Process* _process;


};

