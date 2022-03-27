#include "Emerg_Mission.h"

Emerg_Mission::Emerg_Mission()
{
	Priority = 0;
}

Emerg_Mission::~Emerg_Mission()
{
}


int Emerg_Mission::getPriority()
{
	Priority = 4 * Significance + 3 * FormulationDay + 2 * TargetLocation + MissionDuration;
	return Priority;
}
