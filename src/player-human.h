#include "player.h"

#ifndef VILLAGE_H_
#define VILLAGE_H_

class PlayerHuman : public Player
{

public:
	PlayerHuman(Faction);
	void run();
};

#endif
