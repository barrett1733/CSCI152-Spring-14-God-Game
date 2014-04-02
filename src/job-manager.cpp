
#include "job-manager.h"

JobManager jobManager(FT_PLAYER_1);

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
		}else{
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

	if(jobType == JOB_GATHER_FOOD or
	   jobType == JOB_GATHER_STONE or
	   jobType == JOB_GATHER_WOOD or
	   jobType == JOB_GATHER_IRON)
	{
		if(priority == 3)//Job start create 5 gather jobs with large amount
		{
			taskNum = 5;
			taskGoal = 99999999;
		}else
		{
			taskGoal = 20;

			taskNum = (amount%taskGoal == 0) ? (amount/taskGoal) : (amount/taskGoal + 1);
		}
		job = new GatherJob(jobType, priority, taskNum, taskGoal);
	}

	else if(jobType == JOB_BUILD_HOUSE
			or jobType == JOB_BUILD_STONEWORKS
			or jobType == JOB_BUILD_SMELTING
			or jobType == JOB_BUILD_FARM
			or jobType == JOB_BUILD_LUMBERMILL
			or jobType == JOB_BUILD_WEAPONSMITH
			or jobType == JOB_BUILD_ARMORSMITH
			or jobType == JOB_BUILD_WATCHTOWER
			or jobType == JOB_BUILD_TOWNCENTER
			or jobType == JOB_BUILD_TEMPLE
		)
	{
		taskNum = mapBuildTaskNum[jobType];
		taskGoal = amount / taskNum;
		job = new BuildJob(jobType, priority, taskNum, taskGoal,findJobTarget(jobType));
	}

	else if(jobType == JOB_ATTACK
			or jobType == JOB_DEFEND
			or jobType == JOB_PATROL
			or jobType == JOB_TAME_1
			or jobType == JOB_PARLEY)
	{
		taskNum = 10;//Total villager number * triangle value on military
		job = new MilitaryJob(jobType, priority, taskNum, taskGoal, findJobTarget(jobType));
	}
	else
		return; // 'job' is invalid if control reaches this point (currently, it can't, but with extension it could).

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

Faction JobManager::getFaction()
{
	return this->faction;
}

Entity * JobManager::findJobTarget(JobType jobType)
{
	if(jobType == JOB_BUILD_HOUSE
	   or jobType == JOB_BUILD_STONEWORKS
	   or jobType == JOB_BUILD_SMELTING
	   or jobType == JOB_BUILD_FARM
	   or jobType == JOB_BUILD_LUMBERMILL
	   or jobType == JOB_BUILD_WEAPONSMITH
	   or jobType == JOB_BUILD_ARMORSMITH
	   or jobType == JOB_BUILD_WATCHTOWER
	   or jobType == JOB_BUILD_TOWNCENTER
	   or jobType == JOB_BUILD_TEMPLE)
	{
	   //Find the available area near Town Center

		//Mark this area occupied

	}else if(jobType == JOB_ATTACK
			 or jobType == JOB_DEFEND
			 or jobType == JOB_PATROL
			 or jobType == JOB_TAME_1
			 or jobType == JOB_PARLEY)
	{
		//TBD
	}

	Entity * ety= new Entity(ET_HOUSE, 100, *new Position(), FT_NONE);
	ety->setCurrentHealth(0);
	return ety;
}
