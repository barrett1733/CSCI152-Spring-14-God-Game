#pragma once

#include <vector>
#include "village.h"

class PlayerManager
{
	std::vector<PlayerReference> playerList;

public:
	PlayerManager();

	long addPlayer(Faction);

	void update();
};
