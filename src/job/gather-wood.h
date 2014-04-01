
#ifndef JOB_FACTORY_GATHER_WOOD_H_
#define JOB_FACTORY_GATHER_WOOD_H_

#include "job-manager.h"
#include "job-factory.h"
#include "job.h"

class JobFactory_GatherWood : public JobFactory
{
public:
	JobFactory_GatherWood()
	{
		jobType = 0 /* ... JT_GATHER_WOOD ? ... */;

		// jobManager.registerFactory(this);
	}

	JobReference createJob();
};

class Job_GatherWood : public Job
{
public:
	Job_GatherWood();
};

#endif
