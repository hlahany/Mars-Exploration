#include "Polar_Rover.h"
#include <cmath>

Polar_Rover::Polar_Rover()
{
	PolarSpeed = 0;
	PolarCheckupDuration = 0;
}

int Polar_Rover::getCheckupDuration()
{
	return PolarCheckupDuration;
}

void Polar_Rover::setCheckupDuration(int ChD)
{
	PolarCheckupDuration = ChD;
}


int Polar_Rover::getSpeed()
{
	return PolarSpeed;
}
	
void Polar_Rover::setSpeed(int v)
{
	PolarSpeed = v;
}

void Polar_Rover::CalculateExecutionDays()
{
	float TimeToLocation = 2.0 * AssignedMission->getTargetLocation() / PolarSpeed / 25.0;
	int ED = AssignedMission->getMissionDuration() + ceil(TimeToLocation);
	AssignedMission->setExecutionDays(ED);
}

Polar_Rover::~Polar_Rover()
{
}
