
#ifndef JOB_MANAGER_H_
#define JOB_MANAGER_H_

#include <vector>

//#include "job-factory.h"
#include "job.h"
#include "world-gen.h"

typedef std::vector<JobReference> JobVec;
typedef JobVec::iterator JobIter;


struct ResourceCost
{
    int wood;
    //int food;
    int stone;
    int iron;
	ResourceCost() {}
	ResourceCost(int a, int b, int c) :
		wood(a),
		stone(b),
		iron(c)
	{}
};



class JobManager
{
	JobVec jobList;
	TaskManager * taskManager;
    
public:
	static std::map<JobType, int> mapBuildTaskNum;
	static void initMapBuildTaskNum();

	static std::map<JobType, std::string> mapTaskPriority;
	static void initMapTaskPriority();

	static std::map<JobType, ResourceCost> mapBuildingCost;
	static void initMapBuildingCost();

    ResourceCost getResourceCost(JobType);
    
	JobManager() : taskManager(new TaskManager())
	{
		initMapBuildTaskNum();
		initMapTaskPriority();
		initMapBuildingCost();
	};
	~JobManager(){delete taskManager;}

	void registerJob(JobReference job);

	void createJobList(JobType, int, int);
    void createJobList(JobType, int, int, Entity *);

	//void initJobList();

	JobVec getJobList();

	Faction getFaction();

	TaskManager * getTaskManager();

	Entity * findJobTarget(JobType);

	void cleanTaskList(JobReference job);

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
