
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

//#include "job-factory.h"
#include "job.h"

static std::map<JobType, int> mapBuildTaskNum = {
	{JOB_BUILD_HOUSE, 1},
	{JOB_BUILD_SMELTING, 2},
	{JOB_BUILD_STONEWORKS, 2},
	{JOB_BUILD_FARM, 2},
	{JOB_BUILD_LUMBERMILL, 3},
	{JOB_BUILD_WEAPONSMITH, 4},
	{JOB_BUILD_ARMORSMITH, 4},
	{JOB_BUILD_WATCHTOWER, 1},
	{JOB_BUILD_TOWNCENTER, 20},
	{JOB_BUILD_TEMPLE, 10}
};

std::map<JobType, string> mapTaskPriority = {
	{JOB_BUILD_HOUSE, "Build"},
	{JOB_BUILD_FARM, "Build"},
	{JOB_BUILD_SMELTING, "Build"},
	{JOB_BUILD_STONEWORKS, "Build"},
	{JOB_BUILD_LUMBERMILL, "Build"},
	{JOB_BUILD_WEAPONSMITH, "Military"},
	{JOB_BUILD_ARMORSMITH, "Military"},
	{JOB_BUILD_WATCHTOWER, "Military"},
	{JOB_BUILD_TOWNCENTER, "Build"},
	{JOB_BUILD_TEMPLE, "Build"},
	
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
