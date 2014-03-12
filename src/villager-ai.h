
#include "resource-manager.h"

class VillagerAI : public ResourceManager
{
private:
	int faction;
	int optionalOption;
	int delay;
	bool running;
	void balanceJobs();
	void checkResource(int);
	void getTriangleStats();

public:
	VillagerAI(int,int);
	~VillagerAI();
	void start();
	void stop();
	void run();
};
