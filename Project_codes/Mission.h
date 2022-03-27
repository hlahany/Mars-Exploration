#pragma once
class Mission
{
protected:
	int FormulationDay;
	int MissionID;
	int TargetLocation;
	int MissionDuration;
	int Significance;
	int ExecutionDays;
	int WaitingDays;
	int CompletionDay;
	int AssignedDay;
	bool isAssigned;

public:
	Mission();

	int getFormulationDay();
	void setFormulationDay(int FD);

	int getMissionID();
	void setMissionID(int id);
	
	int getTargetLocation();
	void setTargetLocation(int TL);

	int getMissionDuration();
	void setMissinDuration(int MD);

	int getSignificance();
	void setSignificance(int s);

	int getExecutionDays();
	void setExecutionDays(int ED);

	int getWaitingDays();

	int getCompletionDay();

	int getAssignedDay();
	void setAssignedDay(int AD);

	void setisAssigned(bool Ass);
	bool getisAssigned();

	virtual ~Mission() = 0;
};

