
#include "job-manager.h"

 std::map<JobType, int> JobManager::mapBuildTaskNum = {
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

std::map<JobType, std::string> JobManager::mapTaskPriority = {
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

void JobManager::createJobList(JobType jobType, int priority, int amount)
{
	JobReference job;
	int taskNum, taskGoal = 0;

	if(jobType == JOB_GATHER_FOOD ||
	   jobType == JOB_GATHER_STONE ||
	   jobType == JOB_GATHER_WOOD ||
	   jobType == JOB_GATHER_IRON)
	{
		if(priority == 3)//Job start create 5 gather jobs with large amount
		{
			taskNum = 5;
			taskGoal = 99999999;
		}
		else
		{
			taskGoal = 20;

			taskNum = (amount%taskGoal == 0) ? (amount/taskGoal) : (amount/taskGoal + 1);
		}
		job = new GatherJob(jobType, priority, taskNum, taskGoal);
	}

	else if(jobType == JOB_BUILD_HOUSE
		|| jobType == JOB_BUILD_STONEWORKS
		|| jobType == JOB_BUILD_SMELTING
		|| jobType == JOB_BUILD_FARM
		|| jobType == JOB_BUILD_LUMBERMILL
		|| jobType == JOB_BUILD_WEAPONSMITH
		|| jobType == JOB_BUILD_ARMORSMITH
		|| jobType == JOB_BUILD_WATCHTOWER
		|| jobType == JOB_BUILD_TOWNCENTER
		|| jobType == JOB_BUILD_TEMPLE
		)
	{
		taskNum = mapBuildTaskNum[jobType];
		taskGoal = amount / taskNum;
		job = new BuildJob(jobType, priority, taskNum, taskGoal,findJobTarget(jobType));
	}

	else if(jobType == JOB_ATTACK
		|| jobType == JOB_DEFEND
		|| jobType == JOB_PATROL
		|| jobType == JOB_TAME_1
		|| jobType == JOB_PARLEY)
	{
		taskNum = 10;//Total villager number * triangle value on military
		job = new MilitaryJob(jobType, priority, taskNum, taskGoal, findJobTarget(jobType));
	}
	else
		return; // 'job' is invalid if control reaches this point (currently, it can't, but with extension it could).

    /*
     * Register job and tasks
     */
    
	TaskVec taskList = job->getTaskList();

	registerJob(job);
	for(TaskIter it = taskList.begin(); it != taskList.end(); it++)
	{
		taskManager->registerTask(*it);
	}
}

//For Attack task, the target has to be designated in Villager AI
void JobManager::createJobList(JobType jobType, int priority, int amount, Entity * target)
{
	JobReference job;
	int taskNum, taskGoal = 0;
    
	if(jobType == JOB_ATTACK
            || jobType == JOB_DEFEND
            || jobType == JOB_PATROL
            || jobType == JOB_TAME_1
            || jobType == JOB_PARLEY)
	{
		taskNum = 10;//Total villager number * triangle value on military
		job = new MilitaryJob(jobType, priority, taskNum, taskGoal, target);
	}
	else
		return; // 'job' is invalid if control reaches this point (currently, it can't, but with extension it could).
    
    /*
     * Register job and tasks
     */
    
	TaskVec taskList = job->getTaskList();
    
	registerJob(job);
	for(TaskIter it = taskList.begin(); it != taskList.end(); it++)
	{
		taskManager->registerTask(*it);
	}
}

TaskManager * JobManager::getTaskManager()
{
	return this->taskManager;
}

Entity * JobManager::findJobTarget(JobType jobType)
{
	if(jobType == JOB_BUILD_HOUSE
	   || jobType == JOB_BUILD_STONEWORKS
	   || jobType == JOB_BUILD_SMELTING
	   || jobType == JOB_BUILD_FARM
	   || jobType == JOB_BUILD_LUMBERMILL
	   || jobType == JOB_BUILD_WEAPONSMITH
	   || jobType == JOB_BUILD_ARMORSMITH
	   || jobType == JOB_BUILD_WATCHTOWER
	   || jobType == JOB_BUILD_TOWNCENTER
	   || jobType == JOB_BUILD_TEMPLE)
	{
	   //Find the available area near Town Center
        //Get towncenter
        //Get next entity whose type is ET_NONE;
		//Mark this area occupied
        //return the target;

	}

	Entity * ety= new Entity(ET_HOUSE, 100, *new Position(), F_NONE);
	ety->setCurrentHealth(0);
	return ety;
}
