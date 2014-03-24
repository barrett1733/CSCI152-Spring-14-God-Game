
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

//#include "job-factory.h"
#include "job.h"

static std::map<JobType, int> m = {
	{JOB_BUILD_HOUSE, 5},
	{JOB_BUILD_STONEWORKS, 5},
	{JOB_BUILD_SMELTING, 5},
	{JOB_BUILD_FARM, 5},
	{JOB_BUILD_LUMBERMILL, 5},
	{JOB_BUILD_STOREHOUSE, 5},
	{JOB_BUILD_WEAPONSMITH, 5},
	{JOB_BUILD_ARMORSMITH, 5},
	{JOB_BUILD_WATCHTOWER, 5},
	{JOB_BUILD_TOWNCENTER, 5}
};

enum JobPriority
{
	JOBPRIORITY_LOW = 3,
	JOBPRIORITY_MIDIUM = 7,
	JOBPRIORITY_HIGH = 10
};

class JobManager
{
	std::vector<JobReference> jobList;

public:
	void registerJob(JobReference job);

	void createJobList(JobType jobType, int priority);

	//void initJobList();
    
    std::vector<JobReference> getJobList();
    
    Entity * findTarget();

	void cleanTaskList(JobReference job);

	void cleanJobList();
	
};

#endif

extern JobManager jobManager;
