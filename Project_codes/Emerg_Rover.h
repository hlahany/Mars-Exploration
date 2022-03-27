#pragma once
#include "Rover.h"

class Emerg_Rover : public Rover
{
	int EmergSpeed;
	int EmergCheckupDuration;
public:

	Emerg_Rover();
	~Emerg_Rover();

	virtual int getCheckupDuration();
	virtual void setCheckupDuration(int ChD);

	virtual int getSpeed();
	virtual void setSpeed(int v);

	virtual void CalculateExecutionDays();
};

