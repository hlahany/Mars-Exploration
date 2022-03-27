#include "Emerg_Rover.h"
#include <cmath>


Emerg_Rover::Emerg_Rover()
{
	EmergSpeed = 0;
	EmergCheckupDuration = 0;
}

int Emerg_Rover::getCheckupDuration()
{
	return EmergCheckupDuration;
}

void Emerg_Rover::setCheckupDuration(int ChD)
{
	EmergCheckupDuration = ChD;
}


int Emerg_Rover::getSpeed()
{
	return EmergSpeed;
}
	
void Emerg_Rover::setSpeed(int v)
{
	EmergSpeed = v;
}

void Emerg_Rover::CalculateExecutionDays()
{
	float TimeToLocation = 2.0 * AssignedMission->getTargetLocation() / EmergSpeed / 25.0;
	int ED = AssignedMission->getMissionDuration() + ceil(TimeToLocation);
	AssignedMission->setExecutionDays(ED);
}


Emerg_Rover::~Emerg_Rover()
{
}
