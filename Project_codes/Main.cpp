#include <iostream>
using namespace std;
#include "MarsStation.h"
#include "UI.h"

int main()
{
	UI MainUserInterface;
	bool Success = MainUserInterface.InputData();
	MarsStation MS(MainUserInterface);
	if (Success)
	{
		MS.Execute();
		MainUserInterface.OutputData(MS.getCompletedMissions(), MS.getNumberOfPolarMissions(), MS.getNumberOfEmergMissions(), MS.CalcAvgWait(), MS.CalcAvgExecution());
	}
	return 0;
}