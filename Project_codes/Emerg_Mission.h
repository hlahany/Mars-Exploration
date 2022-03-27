#pragma once
#include "Mission.h"
class Emerg_Mission :public Mission
{
	int Priority;
public:
	Emerg_Mission();
	int getPriority();
	virtual ~Emerg_Mission();
};

