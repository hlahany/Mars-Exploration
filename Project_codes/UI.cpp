#include "UI.h"
#include <fstream>
#include <iostream>
using namespace std;


UI::UI()
{
	NumberOfPolarRovers = 0, NumberOfEmergRovers = 0;
	SP = 0, SE = 0;
	N = 0;
	CP = 0, CE = 0;
	E = 0;
	EventList = new LinkedQueue<Formulation_Event*>;
}

bool UI::InputData()
{
	ifstream inputFile(getInFileName());
	if (inputFile.is_open())
	{
		inputFile >> NumberOfPolarRovers >> NumberOfEmergRovers;
		inputFile >> SP >> SE >> N >> CP >> CE;

		inputFile >> E;

		for (int i = 0; i < E; i++)
		{
			char TypeOfEvent;
			inputFile >> TypeOfEvent;
			if (TypeOfEvent == 'F')
			{
				char TYP;
				int ED, ID, TLOC, MDUR, SIG;
				inputFile >> TYP >> ED >> ID >> TLOC >> MDUR >> SIG;
				Formulation_Event* x = new Formulation_Event;
				x->setEventDay(ED);
				x->setMissionID(ID);
				x->setTypeOfMission(TYP);
				x->setTargetLocation(TLOC);
				x->setMissinDuration(MDUR);
				x->setSignificance(SIG);
				EventList->enqueue(x);
			}
		}
		inputFile.close();
		return true;
	}
	else
	{
		IncorrectFileName();
		return false;
	}
}

void UI::OutputData(P_Queue<Mission*> CM, int PolarMissions, int EmergMissions, float AvgWaitDays, float AvgExecutionDays)
{
	Mission* M = nullptr;
	ofstream outputfile("OutputFile.txt");
	if (outputfile.is_open())
	{
		outputfile << "CD    ID    FD    WD    ED" << endl;
		while (CM.dequeue(M))
		{
			outputfile << M->getCompletionDay() << "      ";
			outputfile << M->getMissionID() << "      ";
			outputfile << M->getFormulationDay() << "        ";
			outputfile << M->getWaitingDays() << "        ";
			outputfile << M->getExecutionDays() << "      ";
			outputfile << endl;
		}
		outputfile << "………………………………………………" << endl;
		outputfile << "………………………………………………" << endl;
		outputfile << "Missions: " << E << " [P: " << PolarMissions << "," << " E: " << EmergMissions << "]" << endl;
		outputfile << "Rovers: " << NumberOfEmergRovers + NumberOfPolarRovers << " [P: " << NumberOfPolarRovers << "," << " E: " << NumberOfEmergRovers << "]" << endl;
		outputfile << "Avg Wait = " << AvgWaitDays << ", ";
		outputfile << "Avg Exec = " << AvgExecutionDays;
	}
}

LinkedQueue<Formulation_Event*>* UI::getEventList()
{
	return EventList;
}

void UI::Print(string Sentence)
{
	cout << Sentence;
}

void UI::Print(int Variable)
{
	cout << Variable;
}

int UI::getOperationMode()
{
	cout << "Choose the program mode : 1 for Interactive Mode, 2 for Step - By - Step Mode, 3 for Silent Mode" << endl;
	int x;
	cin >> x;
	return x;
}

int UI::WaitKeyPress()
{
	return cin.get();
}

void UI::SilentMode()
{
	cout << "Silent Mode" << endl;
	cout << "SImulation starts..." << endl;
	cout << "Simulation ends, Output file created" << endl;
}

void UI::WaitOneSecond()
{
	Sleep(1000);
}

string UI::getInFileName()
{
	string name;
	cout << "Please enter Input File name: ";
	cin >> name;
	return name;
}

void UI::IncorrectFileName()
{
	cout << "File not found." << endl;
}

int UI::getTotalEvents()
{
	return E;
}

int UI::getPolarSpeed()
{
	return SP;
}

int UI::getEmergSpeed()
{
	return SE;
}

int UI::getMissionsBeforeCheckup()
{
	return N;
}

int UI::getEmergCheckupDuration()
{
	return CE;
}

int UI::getPolarCheckupDuration()
{
	return CP;
}

int UI::getNoOfPolarRovers()
{
	return NumberOfPolarRovers;
}

int UI::getNoOfEmergRovers()
{
	return NumberOfEmergRovers;
}

UI::~UI()
{
}