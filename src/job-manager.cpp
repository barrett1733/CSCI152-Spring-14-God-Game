
#include "job-manager.h"

JobManager jobManager;

void JobManager::registerJob(JobReference job)
{
	jobList.push_back(job);
	std::cout<<"Job list size is: "<<jobList.size()<<std::endl;
}

void JobManager::cleanJobList()
{
	for(int i=0; i<jobList.size(); i++)
	{
		if (jobList[i]->isCompleted() == true)
		{
			this->jobList.erase(jobList.begin()+i);
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
	int taskNum, taskGoal;

	if(jobType == JOB_GATHER_FOOD or JOB_GATHER_STONE or JOB_GATHER_WOOD
		or JOB_GATHER_IRON)
	{
		if(priority == 3)//Job start create 5 gather jobs with large amount
		{
			taskNum = 5;
			taskGoal = 99999999;
		}else
		{
			taskGoal = 20;
			taskNum = amount/taskGoal + 1;
		}
		job = new GatherJob(jobType, priority, taskNum, taskGoal);
	}

	else if(jobType ==  JOB_GATHER_FOOD
			or JOB_BUILD_HOUSE
			or JOB_BUILD_STONEWORKS
			or JOB_BUILD_SMELTING
			or JOB_BUILD_FARM
			or JOB_BUILD_LUMBERMILL
			or JOB_BUILD_WEAPONSMITH
			or JOB_BUILD_ARMORSMITH
			or JOB_BUILD_WATCHTOWER
			or JOB_BUILD_TOWNCENTER
			or JOB_BUILD_TEMPLE
		)
	{
		taskNum = m[jobType];
		job = new BuildJob(jobType, priority, taskNum, taskGoal,findTarget());
	}

	else if(jobType == JOB_ATTACK
			or JOB_DEFEND
			or JOB_PATROL
			or JOB_TAME_1
			or JOB_PARLEY)
		taskNum = 10;//Total villager number * triangle value on military
		job = new MilitaryJob(jobType, priority, taskNum, taskGoal, findTarget());
		
		registerJob(job);
}

Entity * JobManager::findTarget()
{
    return new Entity(ET_HOUSE, 100, *new Position());
}

void JobManager::cleanTaskList(JobReference job)
{
	std::vector<TaskReference> t = job->getTaskList();
	for(int i=0; i<t.size(); i++)
	{
		if (t[i]->isCompleted())
		{
			delete t[i];
			t.erase(t.begin()+i);
		}
	}
	std::cout<<"Task list size is: "<<t.size()<<std::endl;
}
