
#include "job-manager.h"
#include "entity-manager.h"

EntityManager * JobManager::entityManager = 0;

std::map<JobType, ResourceCost> JobManager::mapBuildingCost = {
  
    {JOB_BUILD_HOUSE, { 50, 50, 50 } },
    {JOB_BUILD_FARM, { 50, 50, 50 } },
    {JOB_BUILD_SMELTING, { 50, 50, 50 } },
    {JOB_BUILD_STONEWORKS, { 50, 50, 50 } },
    {JOB_BUILD_LUMBERMILL, { 50, 50, 50 } },
    {JOB_BUILD_WEAPONSMITH, { 50, 100, 200 } },
    {JOB_BUILD_ARMORSMITH, { 50, 100, 200 } },
    {JOB_BUILD_WATCHTOWER, { 50, 50, 50 } },
    {JOB_BUILD_TOWNCENTER, { 50, 50, 50 } },
    {JOB_BUILD_TEMPLE, { 50, 50, 50 } }
    
};

ResourceCost JobManager::getResourceCost(JobType jobType)
{
    return mapBuildingCost[jobType];
}

void JobManager::registerJob(JobReference job)
{
	jobList.push_back(job);
    TaskVec taskList = job->getTaskList();
    for(TaskIter it = taskList.begin(); it != taskList.end(); it++)
    {
        taskManager->registerTask(*it);
    }
}

void JobManager::cleanJobList()
{
	for(JobIter iter = this->jobList.begin(); iter != this->jobList.end();)
	{
		(*iter)->cleanTaskList();
		if ((*iter)->isCompleted() == true)
		{
			delete(*iter);
			this->jobList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

std::vector<JobReference> JobManager:: getJobList()
{
	return this->jobList;
}

void JobManager::createJob(JobType type, int priority, ResourceCost resourceCost)
{
    JobReference job = new GatherJob(type, priority, resourceCost);
    
    //Create tasks
    job->createTaskList();
    registerJob(job);
}

void JobManager::createJob(JobType type, int priority, Position psn)
{
    JobReference job;
    if (this->getJobGroup(type) == JG_BUILD)
        job = new BuildJob(type, priority, psn);
    else if (this->getJobGroup(type) == JG_MILITARY)
        job = new MilitaryJob(type, priority, psn);
	else job = new BuildJob(type, priority, psn);////////this is just so I can compile
    this->registerJob(job);
}

JobGroup JobManager::getJobGroup(JobType type)
{
    if (type < JOB_BUILD_HOUSE) return JG_GATHER;
    if (type < JOB_ATTACK) return JG_BUILD;
    else return JG_MILITARY;
}

TaskManager * JobManager::getTaskManager()
{
	return this->taskManager;
}
