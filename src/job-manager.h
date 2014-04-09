
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

//#include "job-factory.h"
#include "job.h"
#include "world-gen.h"

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
	JobVec jobList;
	TaskManager * taskManager;

public:
    static std::map<JobType, int> mapBuildTaskNum;
    
    static std::map<JobType, std::string> mapTaskPriority;
    
	JobManager() : taskManager(new TaskManager()) {};
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
