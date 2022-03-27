#include "MarsStation.h"

MarsStation::MarsStation(UI UsIn)
{
	CurrentDay = 1;
	UserInterface = UsIn;
	Event = nullptr;
	NumberOfPolarMissions = 0;
	NumberOfEmergMissions = 0;

	WaitMissionCount = 0;
	InExecuteMissionCount = 0;
	AvailableRoverCount = 0;
	InCheckupRoverCount = 0;
	CompletedMissionCount = 0;
}

void MarsStation::FillLists()
{
	Event = UserInterface.getEventList();
	int CounterRovers = 1;

	for (int i=0; i<UserInterface.getNoOfEmergRovers(); i++)
	{
		Emerg_Rover* x= new Emerg_Rover;
		x->setSpeed(UserInterface.getEmergSpeed());
		x->setCheckupDuration(UserInterface.getEmergCheckupDuration());
		x->setRoverID(CounterRovers);
		AvailableEmergRover.enqueue(x);
		CounterRovers++;
	}
	
	for (int i=0; i<UserInterface.getNoOfPolarRovers(); i++)
	{
		Polar_Rover* x= new Polar_Rover;
		x->setSpeed(UserInterface.getPolarSpeed());
		x->setCheckupDuration(UserInterface.getPolarCheckupDuration());
		x->setRoverID(CounterRovers);
		AvailablePolarRover.enqueue(x);
		CounterRovers++;
	}

}

void MarsStation::Execute()
{
	FillLists();
	int OperationMode = UserInterface.getOperationMode();
	if (OperationMode == 3)
		UserInterface.SilentMode();


	while (!Event->isEmpty() || !InExecutionRovers.isEmpty() || (!WaitingEmergMission.isEmpty() && (UserInterface.getNoOfEmergRovers() != 0 || UserInterface.getNoOfPolarRovers() != 0)) || (!WaitingPolarMission.isEmpty() && UserInterface.getNoOfPolarRovers() != 0))
	{
		Formulation_Event* Ev = nullptr;
		Mission* NewMission = nullptr;
		while (Event->peek(Ev) && Ev->getEventDay() == CurrentDay)
		{
			Event->dequeue(Ev);
			Ev->Execute(NewMission);
			if (Ev->getTypeOfMission() == 'P')
			{
				WaitingPolarMission.enqueue((Polar_Mission*)NewMission);
				NumberOfPolarMissions++;
			}
			else if (Ev->getTypeOfMission() == 'E')
			{
				WaitingEmergMission.enqueue((Emerg_Mission*)NewMission, ((Emerg_Mission*)NewMission)->getPriority());
				NumberOfEmergMissions++;
			}
		}
	
		AssignWaitingMissions();
		CheckupRoversOut();
		MoveRovers();

		if (OperationMode == 1)
		{ 
			UserInterface.WaitKeyPress();
			ModeofOperation();
		}
		else if (OperationMode == 2)
		{
			ModeofOperation();
			UserInterface.WaitOneSecond();
		}

		CurrentDay++;
	}
	
}

void MarsStation::AssignWaitingMissions()
{
	Emerg_Mission* EM;
	while (WaitingEmergMission.peek(EM) && !AvailableEmergRover.isEmpty())
	{
		Emerg_Rover* ER;
		AvailableEmergRover.dequeue(ER);
		ER->setAssignedMission(EM);
		EM->setAssignedDay(CurrentDay);
		ER->CalculateExecutionDays();
		ExecuteRover(ER);
		WaitingEmergMission.dequeue(EM);
	}

	while (WaitingEmergMission.peek(EM) && AvailableEmergRover.isEmpty() && !AvailablePolarRover.isEmpty())
	{
		Polar_Rover* PR;
		AvailablePolarRover.dequeue(PR);
		PR->setAssignedMission(EM);
		EM->setAssignedDay(CurrentDay);
		PR->CalculateExecutionDays();
		ExecuteRover(PR);
		WaitingEmergMission.dequeue(EM);
	}

	Polar_Mission* PM;
	while (WaitingPolarMission.peek(PM) && !AvailablePolarRover.isEmpty())
	{
		Polar_Rover* PR;
		AvailablePolarRover.dequeue(PR);
		PR->setAssignedMission(PM);
		PM->setAssignedDay(CurrentDay);
		PR->CalculateExecutionDays();
		ExecuteRover(PR);
		WaitingPolarMission.dequeue(PM);
	}

}

void MarsStation::ExecuteRover(Rover* R)
{
	InExecutionRovers.enqueue(R, 1000 - (R->getAssignedMission()->getCompletionDay()));
	R->IncrementCompletedMissions();
}

void MarsStation::MoveRovers()
{
	Rover* RoverToBeRemoved;
	while (InExecutionRovers.peek(RoverToBeRemoved) && (RoverToBeRemoved->getAssignedMission()->getCompletionDay() == CurrentDay))
	{
		InExecutionRovers.dequeue(RoverToBeRemoved);
		CompletedMissions.enqueue(RoverToBeRemoved->getAssignedMission(), 1000 - (RoverToBeRemoved->getAssignedMission()->getCompletionDay()));
		
		Polar_Rover* PR = dynamic_cast<Polar_Rover*>(RoverToBeRemoved);

		if (PR)
		{
			if (((Polar_Rover*)RoverToBeRemoved)->getCompletedMissions() == UserInterface.getMissionsBeforeCheckup())
			{
				InCheckupPolarRover.enqueue((Polar_Rover*)RoverToBeRemoved);
				RoverToBeRemoved->setSentCheckupDay(CurrentDay);
				((Polar_Rover*)RoverToBeRemoved)->ResetCompletedMissions();
			}
			else
				AvailablePolarRover.enqueue(((Polar_Rover*)RoverToBeRemoved));
		}
		else if (!PR)
		{
			if (((Emerg_Rover*)RoverToBeRemoved)->getCompletedMissions() == UserInterface.getMissionsBeforeCheckup())
			{
				InCheckupEmergRover.enqueue(((Emerg_Rover*)RoverToBeRemoved));
				RoverToBeRemoved->setSentCheckupDay(CurrentDay);
				((Emerg_Rover*)RoverToBeRemoved)->ResetCompletedMissions();
			}
			else
				AvailableEmergRover.enqueue(((Emerg_Rover*)RoverToBeRemoved));
		}
	}
}


void MarsStation::CheckupRoversOut()
{
	if (InCheckupEmergRover.isEmpty() && InCheckupPolarRover.isEmpty())
		return;
	
	Emerg_Rover* ER;
	while (InCheckupEmergRover.peek(ER) && (ER->getCheckupDuration() + ER->getSentCheckupDay() == CurrentDay))
	{
		InCheckupEmergRover.dequeue(ER);
		AvailableEmergRover.enqueue(ER);
	}

	Polar_Rover* PR;
	while (InCheckupPolarRover.peek(PR) && (PR->getCheckupDuration() + PR->getSentCheckupDay() == CurrentDay))
	{
		InCheckupPolarRover.dequeue(PR);
		AvailablePolarRover.enqueue(PR);
	}
}

void MarsStation::ModeofOperation()
{
	UserInterface.Print("Current Day: ");
	UserInterface.Print(CurrentDay);
	UserInterface.Print("\n");
	UpdateStatisticsforDay();
	PrintWaitingMissions();
	PrintInExecutionMissions();
	PrintAvailableRovers();
	PrintInCheckupRovers();
	PrintCompletedMissions();

	ResetWaitMissionCount();
	ResetInExecuteMissionCount();
	ResetAvailableRoverCount();
	ResetInCheckupRoverCount();
}

void MarsStation::PrintWaitingMissions()
{
	UserInterface.Print(WaitMissionCount);
	UserInterface.Print(" Waiting Missions: ");

	Emerg_Mission* EM;
	P_Queue <Emerg_Mission*> TempEmerg = WaitingEmergMission;
	UserInterface.Print("[");
	while (TempEmerg.dequeue(EM))
	{
		UserInterface.Print(EM->getMissionID());
		if (TempEmerg.peek(EM))
			UserInterface.Print(",");
	}
	UserInterface.Print("] ");


	Polar_Mission* PM;
	LinkedQueue <Polar_Mission*> TempPolar = WaitingPolarMission;
	UserInterface.Print("(");
	while (TempPolar.dequeue(PM))
	{
		UserInterface.Print(PM->getMissionID());
		if (TempPolar.peek(PM))
			UserInterface.Print(",");
	}
	UserInterface.Print(") ");
	UserInterface.Print("\n");
	UserInterface.Print("------------------------------------------------------\n");

}

void MarsStation::PrintInExecutionMissions()
{
	UserInterface.Print(InExecuteMissionCount);
	UserInterface.Print(" In-Execution Missions/Rovers: ");

	P_Queue<Rover*> TempInExecutionRovers = InExecutionRovers;
	Rover* R = nullptr;
	LinkedQueue<Rover*> TempEmergRovers;
	LinkedQueue<Rover*> TempPolarRovers;

	while (TempInExecutionRovers.dequeue(R))
	{
		Polar_Rover* PR = dynamic_cast<Polar_Rover*>(R);
		if (PR)
			TempPolarRovers.enqueue(R);
		else if (!PR)
			TempEmergRovers.enqueue(R);
	}

	//Printing In-Execution Emergency Rovers and Missions
	UserInterface.Print("[");
	while (TempEmergRovers.dequeue(R))
	{
		UserInterface.Print(R->getAssignedMission()->getMissionID());
		UserInterface.Print("/");
		UserInterface.Print(R->getRoverID());
		if (TempEmergRovers.peek(R))
			UserInterface.Print(", ");
	}
	UserInterface.Print("] ");

	//Printing In-Execution Polar Rovers and Missions
	UserInterface.Print("(");
	while (TempPolarRovers.dequeue(R))
	{
			UserInterface.Print(R->getAssignedMission()->getMissionID());
			UserInterface.Print("/");
			UserInterface.Print(R->getRoverID());
			if (TempPolarRovers.peek(R))
				UserInterface.Print(", ");
	}
	UserInterface.Print(")");
	UserInterface.Print("\n");
	UserInterface.Print("------------------------------------------------------\n");
}

void MarsStation::PrintAvailableRovers()
{
	UserInterface.Print(AvailableRoverCount);
	UserInterface.Print(" Available Rovers: ");

	//Printing Available Emergency Rovers
	Emerg_Rover* ER;
	LinkedQueue <Emerg_Rover*> TempEmergRover = AvailableEmergRover;

	UserInterface.Print("[");
	while (TempEmergRover.dequeue(ER))
	{
		UserInterface.Print(ER->getRoverID());
		if (TempEmergRover.peek(ER))
			UserInterface.Print(",");
	}
	UserInterface.Print("] ");

	//Printing Available Polar Rovers
	Polar_Rover* PR;
	LinkedQueue <Polar_Rover*> TempPolarRover = AvailablePolarRover;

	UserInterface.Print("(");
	while (TempPolarRover.dequeue(PR))
	{
		UserInterface.Print(PR->getRoverID());
		if (TempPolarRover.peek(PR))
			UserInterface.Print(",");
	}
	UserInterface.Print(") ");
	UserInterface.Print("\n");	
	UserInterface.Print("------------------------------------------------------\n");
}

void MarsStation::PrintInCheckupRovers()
{
	UserInterface.Print(InCheckupRoverCount);
	UserInterface.Print(" In-Checkup Rovers: ");

	// Printing In-Checkup Emergency Rovers
	LinkedQueue <Emerg_Rover*> TempEmergRover = InCheckupEmergRover;
	Emerg_Rover * ER;

	UserInterface.Print("[");
	while (TempEmergRover.dequeue(ER))
	{
		UserInterface.Print(ER->getRoverID());
		if (TempEmergRover.peek(ER))
			UserInterface.Print(",");
	}
	UserInterface.Print("] ");

	//Printing In-Checkup Polar Rovers
	Polar_Rover* PR;
	LinkedQueue <Polar_Rover*> TempPolarRover = InCheckupPolarRover;

	UserInterface.Print("(");
	while (TempPolarRover.dequeue(PR))
	{
		UserInterface.Print(PR->getRoverID());
		if (TempPolarRover.peek(PR))
			UserInterface.Print(",");
	}
	UserInterface.Print(") ");
	UserInterface.Print("\n");
	UserInterface.Print("------------------------------------------------------\n");

}

void MarsStation::PrintCompletedMissions()
{
	UserInterface.Print(CompletedMissionCount);
	UserInterface.Print(" Completed Missions: ");
	
	P_Queue<Mission*> TempCompletedMissions = CompletedMissions;
	Mission* M = nullptr;
	LinkedQueue<Mission*> TempEmergMissions;
	LinkedQueue<Mission*> TempPolarMissions;
	
	while (TempCompletedMissions.dequeue(M))
	{
		Emerg_Mission* EM = dynamic_cast<Emerg_Mission*>(M);
		if (EM)
			TempEmergMissions.enqueue(M);
		else if (!EM)
			TempPolarMissions.enqueue(M);
	}

	//Printing Completed Emergency Missions
	UserInterface.Print("[");
	while (TempEmergMissions.dequeue(M))
	{
		UserInterface.Print(M->getMissionID());
		if (TempEmergMissions.peek(M))
			UserInterface.Print(", ");
	}
	UserInterface.Print("] ");

	//Printing Completed Polar Missions
	UserInterface.Print("(");
	while (TempPolarMissions.dequeue(M))
	{
		UserInterface.Print(M->getMissionID());
			if (TempPolarMissions.peek(M))
				UserInterface.Print(", ");
	}
	UserInterface.Print(") ");
	UserInterface.Print("\n");
	UserInterface.Print("------------------------------------------------------\n");
	UserInterface.Print("\n");
}

void MarsStation::UpdateStatisticsforDay()
{
	WaitMissionCount = WaitingEmergMission.getSize() + WaitingPolarMission.getSize();
	InExecuteMissionCount = InExecutionRovers.getSize();
	AvailableRoverCount = AvailableEmergRover.getSize() + AvailablePolarRover.getSize();
	InCheckupRoverCount = InCheckupEmergRover.getSize() + InCheckupPolarRover.getSize();
	CompletedMissionCount = CompletedMissions.getSize();
}

P_Queue<Mission*> MarsStation::getCompletedMissions()
{
	return CompletedMissions;
}

int MarsStation::getNumberOfPolarMissions()
{
	return NumberOfPolarMissions;
}

int MarsStation::getNumberOfEmergMissions()
{
	return NumberOfEmergMissions;
}

void MarsStation::ResetWaitMissionCount()
{
	WaitMissionCount = 0;
}

void MarsStation::ResetInExecuteMissionCount()
{
	InExecuteMissionCount = 0;
}

void MarsStation::ResetAvailableRoverCount()
{
	AvailableRoverCount = 0;
}

void MarsStation::ResetInCheckupRoverCount()
{
	InCheckupRoverCount = 0;
}

float MarsStation::CalcAvgExecution()
{
	if (UserInterface.getTotalEvents() == 0) return 0;
	float SumExecutionDays = 0;
	P_Queue<Mission*> Temp = CompletedMissions;
	Mission* M = nullptr;
	
	while (Temp.dequeue(M))
		SumExecutionDays += M->getExecutionDays();

	float result = SumExecutionDays / UserInterface.getTotalEvents();
	return result;
}

float MarsStation::CalcAvgWait()
{
	if (UserInterface.getTotalEvents() == 0) return 0;
	float SumWaitDays = 0;
	P_Queue<Mission*> Temp = CompletedMissions;
	Mission* M = nullptr;

	while (Temp.dequeue(M))
		SumWaitDays += M->getWaitingDays();

	float result = SumWaitDays / UserInterface.getTotalEvents();
	return result;
}

MarsStation::~MarsStation()
{
	if (Event)
		delete Event;

	Mission* M;
	while (CompletedMissions.dequeue(M));

	Emerg_Rover* ER;
	while (AvailableEmergRover.dequeue(ER));
	while (InCheckupEmergRover.dequeue(ER));

	Polar_Rover* PR;
	while (AvailablePolarRover.dequeue(PR));
	while (InCheckupPolarRover.dequeue(PR));

}