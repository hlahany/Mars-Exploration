#pragma once
#include "Mission.h"

class Rover
{
protected:
	Mission* AssignedMission;
	int CompletedMissions;
	int SentCheckupDay;
	int RoverID;

public:
	Rover();

	virtual int getCheckupDuration() = 0;
	virtual void setCheckupDuration(int ChD) = 0;

	virtual int getSpeed() = 0;
	virtual void setSpeed(int v) = 0;

	int getRoverID();
	void setRoverID(int ID);

	virtual void IncrementCompletedMissions();
	virtual void ResetCompletedMissions();
	virtual int getCompletedMissions();

	int getSentCheckupDay();
	void setSentCheckupDay(int ChDay);

	Mission* getAssignedMission();
	void setAssignedMission(Mission* AssMiss);

	virtual void CalculateExecutionDays() = 0;

	virtual ~Rover();
};

