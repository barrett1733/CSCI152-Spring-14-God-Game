#pragma once
#include "actor-ai.h"

class ComputerAI : ActorAI
{
private:
	enum JobType { GATHER, MILITARY, BUILD, WORSHIP, JT_COUNT };
	int villagers;
	double jobsArray[JT_COUNT];
	bool requestVillager(JobType,int);

public:
	ComputerAI(int,AiDifficulty);
	~ComputerAI(void);
	void run();

};
