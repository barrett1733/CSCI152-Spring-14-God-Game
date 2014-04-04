#include "village.h"
#pragma once

class VillageComputer : public Village
{
public:
	VillageComputer(Faction);
	void run();
};

