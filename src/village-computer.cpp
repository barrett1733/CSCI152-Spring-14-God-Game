#include "village-computer.h"


VillageComputer::VillageComputer(Faction faction, Difficulty difficulty) : Village(faction), difficulty(difficulty)
{
	for (int i = 0; i<JT_COUNT; i++)
		jobsArray[i];
}

void VillageComputer::run()
{
	// TODO: PlayerComputer::run();
	// Determine military action
	// Determine miracles
	// Determine Triangle balance.
	// jobManager.setBalance(militaryBalance, buildBalance, gatherBalance);
}

bool VillageComputer::requestVillager(JobType job, int amount)
{
	if (amount <= villagers)
	{
		jobsArray[job] += amount;
		int remainder = amount % 2;
		for (int i = 0; i<JT_COUNT - 1; i++)
		if (i != job)
			jobsArray[i] += amount / 2;
		jobsArray[JT_COUNT - 2] += remainder;
		return true;
	}
	else return false;
}