
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

#include "job-factory.h"
#include "job.h"

class JobManager
{
	std::vector<JobFactory*> factoryList;
	std::vector<Job*> jobList;

public:
	void registerFactory(JobFactory * factory);

	JobReference createJob(JobType & jobType);
};

#endif

extern JobManager jobManager;
