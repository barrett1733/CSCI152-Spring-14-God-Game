#include "villager-ai.h";
#include "resource-manager.h";

#ifndef PLAYER_AI_H_
#define PLAYER_AI_H_

enum AiDifficulty
{
	EASY,
	NORMAL,
	HARD
};

class PlayerAI
{
private:
	int delay;
	int counter;
	int faction;
	int villager;
	AiDifficulty myDifficulty;
	VillagerAI myVillagerAI;
	ResourcePool myResourcePool;

public:
	PlayerAI(int,AiDifficulty);
	~PlayerAI();
	void run();
	//void makeDecisions();
};

class psuedoTriangle
{
	double gather, military, build;
};

class psuedoSlider
{
	double worship;
};


#endif