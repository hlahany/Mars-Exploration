#include "Formulation_Event.h"


Formulation_Event::Formulation_Event()
{
}



void Formulation_Event::Execute(Mission* &M)
{
	if (TypeOfMission == 'P')
	{
		M = new Polar_Mission;
		M->setFormulationDay(EventDay);
		M->setMissinDuration(MissionDuration);
		M->setMissionID(MissionID);
		M->setTargetLocation(TargetLocation);
		M->setSignificance(Significance);
	}
	if (TypeOfMission == 'E')
	{
		M = new Emerg_Mission;
		M->setFormulationDay(EventDay);
		M->setMissinDuration(MissionDuration);
		M->setMissionID(MissionID);
		M->setTargetLocation(TargetLocation);
		M->setSignificance(Significance);
	}

}

Formulation_Event::~Formulation_Event()
{
}
