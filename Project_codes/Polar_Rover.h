#pragma once
#include "Rover.h"

class Polar_Rover : public Rover
{
private:
	int PolarSpeed;
	int PolarCheckupDuration;
public:
	Polar_Rover();
	~Polar_Rover();

	virtual int getCheckupDuration();
	virtual void setCheckupDuration(int ChD);

	virtual int getSpeed();
	virtual void setSpeed(int v);

	virtual void CalculateExecutionDays();
};

