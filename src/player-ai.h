
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
	AiDifficulty myDifficulty;
	VillagerAI myVillagerAI;
	ResourceManager myResourceManager;

public:
	PlayerAI(int,AiDifficulty);
	~PlayerAI();
	void run();
	void makeDecisions();
};

#endif