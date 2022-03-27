#pragma once
#include "LinkedQueue.h"
#include "Formulation_Event.h"
#include "P_Queue.h"
#include <string>
#include <windows.h>

class UI
{
private:
	LinkedQueue<Formulation_Event*>* EventList;

	int NumberOfPolarRovers, NumberOfEmergRovers;
	int SP, SE;
	int N;
	int CP, CE;
	int E;

public:
	UI();
	bool InputData();
	void OutputData(P_Queue<Mission*> CM, int PolarMissions, int EmergMissions, float AvgWaitDays, float AvgExecutionDays);
	LinkedQueue<Formulation_Event*>* getEventList();

	void Print(string Sentence);
	void Print(int Variable);
	int getOperationMode();
	int WaitKeyPress();
	void SilentMode();
	void WaitOneSecond();

	string getInFileName();
	void IncorrectFileName();

	int getTotalEvents();
	int getPolarSpeed();
	int getEmergSpeed();
	int getMissionsBeforeCheckup();
	int getEmergCheckupDuration();
	int getPolarCheckupDuration();
	int getNoOfPolarRovers();
	int getNoOfEmergRovers();

	~UI();
};

