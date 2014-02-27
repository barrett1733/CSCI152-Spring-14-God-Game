
#include "job-manager.h"

JobManager jobManager;

void JobManager::registerFactory(JobFactory * factory)
{
	factoryList.push_back(factory);
}

JobReference JobManager::createJob(JobType & jobType)
{
	JobFactory * factory;
	int factoryCount = factoryList.size();

	for(int factoryIndex = 0; factoryIndex < factoryCount; factoryIndex ++)
	{
		factory = factoryList[factoryIndex];
		if(factory->canCreate(jobType))
			return factory->createJob();
	}

	return NULL;
}
