#pragma once
#include "villager-ai.h";
#include "resource-manager.h";


enum AiDifficulty
{
	EASY,
	NORMAL,
	HARD
};

class ActorAI
{
protected:
	int delay;
	int counter;
	int faction;
	AiDifficulty myDifficulty;

public:
	ActorAI(int,AiDifficulty);
	~ActorAI();
	virtual void run();
	virtual void makeDecision();
};
