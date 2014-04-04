#include "resource-manager.h"
#include "job-manager.h"

#pragma once

class Player
{
private:
	Faction faction;
	JobManager jobManager;

public:
	Player(Faction);
	Faction getFaction() { return faction; }
};

typedef Player * PlayerReference;

