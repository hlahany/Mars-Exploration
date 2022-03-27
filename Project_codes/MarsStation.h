#pragma once
#include "LinkedQueue.h"
#include "Formulation_Event.h"
#include "Emerg_Mission.h"
#include "Polar_Mission.h"
#include "P_Queue.h"

#include "Polar_Rover.h"
#include "Emerg_Rover.h"
#include "UI.h"

class MarsStation
{
private:
	LinkedQueue<Formulation_Event*>* Event;
	P_Queue <Emerg_Mission*> WaitingEmergMission;
	LinkedQueue <Polar_Mission*> WaitingPolarMission;
	LinkedQueue <Emerg_Rover*> AvailableEmergRover;
	LinkedQueue <Polar_Rover*> AvailablePolarRover;
	P_Queue<Rover*> InExecutionRovers;
	LinkedQueue <Emerg_Rover*> InCheckupEmergRover;
	LinkedQueue <Polar_Rover*> InCheckupPolarRover;
	P_Queue<Mission*> CompletedMissions;

	int CurrentDay;
	UI UserInterface;
	int NumberOfPolarMissions;
	int NumberOfEmergMissions;

	int WaitMissionCount;
	int InExecuteMissionCount;
	int AvailableRoverCount;
	int InCheckupRoverCount;
	int CompletedMissionCount;

public:
	MarsStation(UI UsIn);
	~MarsStation();

	void FillLists();
	void Execute();
	void AssignWaitingMissions();

	void ExecuteRover(Rover* R);
	void MoveRovers();
	void CheckupRoversOut();

	void ModeofOperation();
	float CalcAvgExecution();
	float CalcAvgWait();

	P_Queue<Mission*> getCompletedMissions();
	int getNumberOfPolarMissions();
	int getNumberOfEmergMissions();

	void UpdateStatisticsforDay();
	void PrintWaitingMissions();
	void PrintInExecutionMissions();
	void PrintAvailableRovers();
	void PrintInCheckupRovers();
	void PrintCompletedMissions();

	void ResetWaitMissionCount();
	void ResetInExecuteMissionCount();
	void ResetAvailableRoverCount();
	void ResetInCheckupRoverCount();
};