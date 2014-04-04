#include "player.h"

#ifndef VILLAGE_H_
#define VILLAGE_H_

class PlayerHuman : public Player
{
	ResourceManager resourceManager;

	void balanceJobs();
	void createBuildings();
	void needsDefending();

public:
	PlayerHuman(Faction);
	void run();
};

#endif
