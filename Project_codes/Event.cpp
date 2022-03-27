#include "Event.h"


Event::Event()
{
	EventDay = 0;
	TypeOfMission = 0;
	MissionID = 0;
	TargetLocation = 0;
	MissionDuration = 0;
	Significance = 0;
}

int Event::getEventDay()
{
	return EventDay;
}

void Event::setEventDay(int ED)
{
	EventDay = ED;
}

char Event::getTypeOfMission()
{
	return TypeOfMission;
}

void Event::setTypeOfMission(int Type)
{
	TypeOfMission = Type;
}

int Event::getMissionID()
{
	return MissionID;
}

void Event::setMissionID(int id)
{
	MissionID = id;
}

int Event::getTargetLocation()
{
	return TargetLocation;
}

void Event::setTargetLocation(int TL)
{
	TargetLocation = TL;
}


int Event::getMissionDuration()
{
	return MissionDuration;
}

void Event::setMissinDuration(int MD)
{
	MissionDuration = MD;
}

int Event::getSignificance()
{
	return Significance;
}

void Event::setSignificance(int s)
{
	Significance = s;
}

Event::~Event()
{}