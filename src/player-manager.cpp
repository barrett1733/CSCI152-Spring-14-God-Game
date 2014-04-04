
#include "player-manager.h"

PlayerManager::PlayerManager()
{

}

long PlayerManager::addPlayer(Faction faction)
{
	playerList.push_back(new Village(faction));
	return playerList.size();
}

void PlayerManager::update()
{
	for (auto iter = playerList.begin(); iter != playerList.end(); ++iter)
		(*iter)->run();
}
