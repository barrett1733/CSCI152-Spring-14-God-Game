
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
		if (jobList[i].isCompleted == true)
		{
			jobList.remove(jobList.begin()+i);
		}
	}
}

void JobManager::initJobList()
{
	
}

void JobManager::createJobList()
{
	switch ()
	{
		case "Game starts":
				//create a job for each value in enum
		case "Short of Wood":
				//create a gather-wood job
		case "Short of Iron":
				//create a gather-iron job
		case "Short of Food"
				//create a gather-food job
		case "Short of Stone"
				//create a gather-stone job
		case "Short of House"
				//create a build-house job
		case "User Input"
				//create a highest priority job
	}			

}