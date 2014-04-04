#include <vector>
#include "village-computer.h"
#include "entity.h"
#pragma once

class PlayerManager
{
	std::vector<PlayerReference> playerList;
	Difficulty playerDifficulty;

public:
	PlayerManager(Difficulty);

	long addCreaturePlayer(Faction);
	long addHumanPlayer(Faction);
	long addComputerPlayer(Faction);

	void update();
	long getPlayerListSize() { return playerList.size() };
};
