//
//  File: job-manager.h
//  Author: Jimmy Ouyang
//  CSci 152
//  Spring 2014
//
//  Job Manager is responsible for
//  	Creating jobs
//		Keeping track of all jobs
//		Updating the task manager
//		Remove complete jobs
//
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

//#include "job-factory.h"
#include "job.h"
#include "world-gen.h"

typedef std::vector<JobReference> JobList;
typedef JobList::iterator JobIter;

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
	JobList jobList;
	TaskManager * taskManager;

public:
    static std::map<JobType, ResourceCost> mapBuildingCost;

    ResourceCost getResourceCost(JobType);

	JobManager() : taskManager(new TaskManager()) {};
	~JobManager(){delete taskManager;}

	void registerJob(JobReference job);

    void createJob(JobType, int priority, ResourceCost);
	void createJob(JobType, int priority, Position psn);

    JobGroup getJobGroup(JobType type);

	JobList getJobList();

    void update(MobileEntityList & villagerList, EntityList & resourceList);

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
