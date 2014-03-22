
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
		if (jobList[i].isCompleted())
		{
			jobList.remove(jobList.begin()+i);
		}
	}
}

void JobManager::createJobList(JobType jobType, int priority, int taskNum, int taskGoal)
{			
	JobReference job;

	job = new Job(jobType, priority, taskNum, taskGoal);
	registerJob(job);
}