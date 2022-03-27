#pragma once
#include "Event.h"
#include "Emerg_Mission.h"
#include "Polar_Mission.h"

class Formulation_Event :public Event
{
public:
	Formulation_Event();
	virtual void Execute(Mission* &M);
	virtual ~Formulation_Event();
};

