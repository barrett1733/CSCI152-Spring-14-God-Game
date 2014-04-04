
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
	long villageCount = playerList.size();
	for(long villageIndex = 0; villageIndex < villageCount; villageIndex ++)
	{
		VillageReference village = playerList[villageIndex];

		if( village->hasGodLogic() )
			village->runGodLogic();

		village->runVillageLogic();
	}
}
