#include "Rover.h"

Rover::Rover()
{
	CompletedMissions = 0;
	AssignedMission = nullptr;
	SentCheckupDay = 0;
	RoverID = 0;
}


Mission* Rover::getAssignedMission()
{
	return AssignedMission;
}

void Rover::setAssignedMission(Mission* AssMiss)
{
	AssignedMission = AssMiss;
	AssignedMission->setisAssigned(true);
}

void Rover::IncrementCompletedMissions()
{
	CompletedMissions++;
}

void Rover::ResetCompletedMissions()
{
	CompletedMissions = 0;
}

int Rover::getCompletedMissions()
{
	return CompletedMissions;
}

int Rover::getSentCheckupDay()
{
	return SentCheckupDay;
}

void Rover::setSentCheckupDay(int ChDay)
{
	SentCheckupDay = ChDay;
}

int Rover::getRoverID()
{
	return RoverID;
}

void Rover::setRoverID(int ID)
{
	RoverID = ID;
}

Rover::~Rover()
{}
