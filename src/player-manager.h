#include <vector>
#include "village-computer.h"
#include "entity.h"
#pragma once

class PlayerManager
{
	std::vector<PlayerReference> playerList;

public:
	PlayerManager();

	long addPlayer(Faction);

	void update();
};
