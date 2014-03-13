#include "resource-manager.h"

class VillagerAI : public ResourceManager
{
private:
	int faction;
	int optionalOption;
	bool running;
	int delay;
	int counter;
	void balanceJobs();
	void checkResource(int);

	// VillageAI should be agnostic as to HOW the triangle values are set.
	// Instead, it should accept the values as in:
	//void setTriangleStats(double a, double b, double c);
	// Then again, I'm not sure the village AI needs to know about the triangle at all.
	// I think it's mostly for the job management.
	// The Job Manager will set the priority on tasks base on the triangle,
	// and villagers will pick up tasks based on the task priority and their own preference.
	void getTriangleStats();

public:
	VillagerAI(int,int);
	~VillagerAI();
	void start();
	void stop();
	void run();
};
