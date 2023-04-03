#pragma once
#include<Windows.h>
#include "Process.h"
#include <iostream>

struct angle;
struct point3;

class Entity
{
public:
	Entity(Process process, bool isMainPlayer = false);
	~Entity();
	int32_t getHealth();
	point3 getPos();
	angle getAngles();
	
	void setEntBaseAddr(uintptr_t addr);

private:
	uintptr_t _entBasePtr;
	Process& _process;
	uintptr_t _mainModuleAddr;

	void getMainPlayerBaseAddr();


};

