#include <vector>
#include "village-computer.h"
#include "entity.h"
#pragma once

class PlayerManager
{
	std::vector<PlayerReference> playerList;
	Difficulty playerDifficulty;

public:
	PlayerManager();
	PlayerManager(Difficulty);

	long addCreaturePlayer();
	long addHumanPlayer(Faction);
	long addComputerPlayer(Faction);

	void setDifficulty(Difficulty);
	void update();
	long getPlayerListSize() { return playerList.size(); };
};
