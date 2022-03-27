#pragma once

class Mission;

class Event
{
protected:
	int EventDay;
	char TypeOfMission;
	int MissionID;
	int TargetLocation;
	int MissionDuration;
	int Significance;

public:
	Event();

	int getEventDay();
	void setEventDay(int ED);

	char getTypeOfMission();
	void setTypeOfMission(int Type);

	int getMissionID();
	void setMissionID(int id);

	int getTargetLocation();
	void setTargetLocation(int TL);

	int getMissionDuration();
	void setMissinDuration(int MD);

	int getSignificance();
	void setSignificance(int s);

	virtual void Execute(Mission* &M) = 0;

	virtual ~Event() = 0;
};

