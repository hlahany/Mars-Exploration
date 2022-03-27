#include "Mission.h"

Mission::Mission()
{
	FormulationDay = 0;
	MissionID = 0;
	TargetLocation = 0;
	MissionDuration = 0;
	Significance = 0;
	ExecutionDays = 0;
	WaitingDays = 0;
	CompletionDay = 0;
	AssignedDay = 0;
	isAssigned = false;
}

int Mission::getFormulationDay()
{
	return FormulationDay;
}

void Mission::setFormulationDay(int FD)
{
	FormulationDay = FD;
}

int Mission::getMissionID()
{
	return MissionID;
}

void Mission::setMissionID(int id)
{
	MissionID = id;
}


int Mission::getTargetLocation()
{
	return TargetLocation;
}

void Mission::setTargetLocation(int TL)
{
	TargetLocation = TL;
}


int Mission::getMissionDuration()
{
	return MissionDuration;
}

void Mission::setMissinDuration(int MD)
{
	MissionDuration = MD;
}

int Mission::getSignificance()
{
	return Significance;
}

void Mission::setSignificance(int s)
{
	Significance = s;
}

void Mission::setExecutionDays(int ED)
{
	ExecutionDays = ED;
}

int Mission::getExecutionDays()
{
	return ExecutionDays;
}

int Mission::getWaitingDays()
{
	WaitingDays = AssignedDay - FormulationDay;
	return WaitingDays;
}

int Mission::getCompletionDay()
{
	CompletionDay = AssignedDay + WaitingDays + ExecutionDays;
	return CompletionDay;
}

int Mission::getAssignedDay()
{
	return AssignedDay;
}

void Mission::setAssignedDay(int AD)
{
	AssignedDay = AD;
}

void Mission::setisAssigned(bool Ass)
{
	isAssigned = Ass;
}

bool Mission::getisAssigned()
{
	return isAssigned;
}

Mission::~Mission()
{}