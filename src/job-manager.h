
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

class JobManager
{
	std::vector<TaskReference> taskList;
	std::vector<JobReference> jobList;

public:
	void registerJob(JobReference job);

	void createTask(TaskReference task);

	void createJobList(JobType & jobType);

	void initJobList();

	void cleanJobList();

	TaskReference createTask(TaskType & taskType);
	
};

#endif

extern JobManager jobManager;
