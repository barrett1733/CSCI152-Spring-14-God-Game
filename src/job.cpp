
#include "job.h"

	Job::Job(JobType type, int priority, int taskNum, int taskQuota):
	_type(type), _priority(priority), _taskNum(taskNum), _taskQuota(taskQuota)
	{}

	Job::~Job(){};
	
	void Job::setType(JobType type)
	{
		this->_type = type;
	}

	void Job::setPriority(int priority)
	{
		this->_priority = priority;
	}

	JobType Job::getType()
	{
		return this->_type;
	}

	int Job::getPriority()
	{
		return this->_priority;
	}

	bool Job::isCompleted()
	{
		return _taskList.size() == 0;
	}

	void Job::createTaskList()
	{
		for(int i=0; i<_taskNum; i++)
		{
			Task task = new Task(mp[_jobType], _taskQuota);
		}
	}

	// int main(){
 //        Position p;
	// 	Entity * entity = new Entity(ET_HOUSE, 100, p);
	// 	JobReference job = new BuildJob(JOB_BUILD_HOUSE, 3, entity);
	// 	delete entity;
	// 	delete job;
	// }
