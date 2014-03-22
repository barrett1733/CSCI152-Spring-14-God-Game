
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

//#include "job-factory.h"
#include "job.h"
#include "task.h"

static std::vector<JobType> jobTypeList = {
	JOB_GATHER_FOOD,
	JOB_GATHER_IRON,
	JOB_GATHER_WOOD,
	JOB_GATHER_STONE,
	
	JOB_BUILD_HOUSE,
	JOB_BUILD_STONEWORKS,
	JOB_BUILD_SMELTING,
	JOB_BUILD_FARM,
	JOB_BUILD_LUMBERMILL,
	JOB_BUILD_STOREHOUSE,
	JOB_BUILD_WEAPONSMITH,
	JOB_BUILD_ARMORSMITH,
	JOB_BUILD_WATCHTOWER,
	JOB_BUILD_TOWNCENTER
};

std::map<JobType, int> m = {
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
	JOBPRIORITY_LOW = 3;
	JOBPRIORITY_MIDIUM = 7;
	JOBPRIORITY_HIGH = 10;
}

class JobManager
{
	std::vector<JobReference> jobList;

public:
	void registerJob(JobReference job);

	void createJobList(JobType & jobType);

	//void initJobList();

	void cleanJobList();
	
};

#endif

extern JobManager jobManager;
