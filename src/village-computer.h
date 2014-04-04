#include "village.h"
#pragma once

enum Difficulty
{
	EASY = 1,
	NORMAL,
	HARD
};

class VillageComputer : public Village
{
private:
	Difficulty difficulty;
	enum JobType { GATHER, MILITARY, BUILD, WORSHIP, JT_COUNT };
	int villagers;
	double jobsArray[JT_COUNT];
	bool requestVillager(JobType, int);

public:
	VillageComputer(Faction, Difficulty);
	void run();
};

