#include "job-manager.h"
#pragma once

class Creature
{
private:
	JobManager jobManager;
	void decideRun();
	void decideWalk();

protected:
	Faction faction;

public:
	Creature(Faction);
	void run();
};

typedef Creature * PlayerReference;
