#include "entity.h"

#pragma once

class Player
{
private:
	Faction faction;

public:
	Player(Faction);
	Faction getFaction() { return faction; }
	virtual void update();
};

typedef Player * PlayerReference;

