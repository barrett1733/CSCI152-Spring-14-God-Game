#pragma once
#include "player-human.h"
class PlayerComputer :
	public PlayerHuman
{
public:
	PlayerComputer();
	~PlayerComputer();
	void run();
};

