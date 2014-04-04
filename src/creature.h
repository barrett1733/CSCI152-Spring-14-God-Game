#include "job-manager.h"
#pragma once

typedef Creature * PlayerReference;

class Creature
{
private:
	JobManager jobManager;

public:
	Creature(void);
	~Creature(void);
	void run();
};

