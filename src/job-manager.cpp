
#include "job-manager.h"

JobManager jobManager;

void JobManager::registerJob(JobReference job)
{
	jobList.push_back(job);
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

	else if(jobType ==  JOB_GATHER_FOOD
			or jobType == JOB_BUILD_HOUSE
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
        std::cout<<"test"<<std::endl;
		job = new BuildJob(jobType, priority, taskNum, taskGoal,findTarget());
	}

	else if(jobType == JOB_ATTACK
			or jobType == JOB_DEFEND
			or jobType == JOB_PATROL
			or jobType == JOB_TAME_1
			or jobType == JOB_PARLEY)
    {
        taskNum = 10;//Total villager number * triangle value on military
		job = new MilitaryJob(jobType, priority, taskNum, taskGoal, findTarget());
    }
		registerJob(job);
}

Entity * JobManager::findTarget()
{
    Entity * ety= new Entity(ET_HOUSE, 100, *new Position());
    return ety;
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
