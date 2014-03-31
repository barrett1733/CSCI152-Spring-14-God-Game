
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

//#include "job-factory.h"
#include "job.h"
#include "world_gen.h"

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

static std::map<JobType, std::string> mapTaskPriority = {
	{JOB_BUILD_HOUSE, "Build"},
	{JOB_BUILD_FARM, "Build"},
	{JOB_BUILD_SMELTING, "Build"},
	{JOB_BUILD_STONEWORKS, "Build"},
	{JOB_BUILD_LUMBERMILL, "Build"},
	{JOB_BUILD_WEAPONSMITH, "Military"},
	{JOB_BUILD_ARMORSMITH, "Military"},
	{JOB_BUILD_WATCHTOWER, "Military"},
	{JOB_BUILD_TOWNCENTER, "Build"},
	{JOB_BUILD_TEMPLE, "Build"}
};

typedef std::vector<JobReference> JobVec;
typedef JobVec::iterator JobIter;
enum JobPriority
{
	JOBPRIORITY_LOW = 3,
	JOBPRIORITY_MIDIUM = 7,
	JOBPRIORITY_HIGH = 10
};

class JobManager
{
    Faction faction;
	JobVec jobList;
    TaskManager * taskManager;
    
public:
    JobManager(Faction ft) : faction(ft), taskManager(new TaskManager(ft)) {};
    ~JobManager(){delete taskManager;}
    
	void registerJob(JobReference job);

	void createJobList(JobType, int, int);

	//void initJobList();
    
    JobVec getJobList();
    
    Faction getFaction();
    
    TaskManager * getTaskManager();
    
    Entity * findJobTarget(JobType);

	void cleanTaskList(JobReference job);

	void cleanJobList();
	
};

#endif

extern JobManager jobManager;
