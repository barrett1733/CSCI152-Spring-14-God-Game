
#include "player-manager.h"

PlayerManager::PlayerManager(Difficulty diff) : playerDifficulty(diff)
{

}

long PlayerManager::addCreaturePlayer(Faction faction)
{
	playerList.push_back(new Creature(faction));
	return playerList.size();
}
long PlayerManager::addHumanPlayer(Faction faction)
{
	playerList.push_back(new Village(faction));
	return playerList.size();
}
long PlayerManager::addComputerPlayer(Faction faction)
{
	playerList.push_back(new VillageComputer(faction,playerDifficulty));
	return playerList.size();
}

void PlayerManager::update()
{
	for (auto iter = playerList.begin(); iter != playerList.end(); ++iter)
		(*iter)->run();
}
