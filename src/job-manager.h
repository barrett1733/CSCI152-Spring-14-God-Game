
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

//#include "job-factory.h"
#include "job.h"
#include "world-gen.h"

typedef std::vector<JobReference> JobVec;
typedef JobVec::iterator JobIter;

class EntityManager; // Forward Declaration

enum JobGroup
{
    JG_NONE,
    JG_GATHER,
    JG_BUILD,
    JG_MILITARY
};


class JobManager
{
	JobVec jobList;
	TaskManager * taskManager;
    
public:
	static EntityManager * entityManager;
    
    static std::map<JobType, ResourceCost> mapBuildingCost;
    
    ResourceCost getResourceCost(JobType);
    
	JobManager() : taskManager(new TaskManager()) {};
	~JobManager(){delete taskManager;}

	void registerJob(JobReference job);
    
    void createJob(JobType, int priority, ResourceCost);
	void createJob(JobType, int priority, Position psn);
    
    JobGroup getJobGroup(JobType type);

	JobVec getJobList();

	TaskManager * getTaskManager();

	void cleanJobList();
    
	/*
	// Desired interface:

	int getTaskCount();


	void createJob(JobType, int priority, Position);
	void createJob(JobType, int priority, EntityReference);

	void assignTask(EntityReference);
	TaskReference getTask(EntityReference);
	*/
};

#endif
