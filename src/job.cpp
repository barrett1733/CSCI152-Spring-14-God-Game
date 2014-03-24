
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

    std::vector<TaskReference> Job::getTaskList()
	{
		return this->_taskList;
	}

	GatherJob::GatherJob(JobType type, int priority, int taskNum, int taskQuota):
	Job(type, priority, taskNum, taskQuota) {};

	void GatherJob::createTaskList()
	{
		for(int i=0; i<_taskNum; i++)
		{
			TaskReference task = new GatherTask(mp[_type], _taskQuota, _priority, _taskQuota);
			_taskList.push_back(task);
			taskManager.registerTask(task);
		}
	}

	BuildJob::BuildJob(JobType type, int priority, int taskNum, int taskQuota, Entity * target):
	Job(type, priority, taskNum, taskQuota), _target(target) {};

	void BuildJob::createTaskList()
	{
		for(int i=0; i<_taskNum; i++)
		{
			TaskReference task = new BuildTask(mp[_type], _target, _priority, 0, _taskQuota);
			_taskList.push_back(task);
			taskManager.registerTask(task);
		}
	}

	MilitaryJob::MilitaryJob(JobType type, int priority, int taskNum, int taskQuota, Entity * target):
	Job(type, priority, taskNum, taskQuota), _target(target) {};

	void MilitaryJob::createTaskList()
	{
		for(int i=0; i<_taskNum; i++)
		{
			TaskReference task = new MilitaryTask(mp[_type], _target, _priority, 0, _taskQuota);
			_taskList.push_back(task);
			taskManager.registerTask(task);
		}
	}


	// int main(){
 //        Position p;
	// 	Entity * entity = new Entity(ET_HOUSE, 100, p);
	// 	JobReference job = new BuildJob(JOB_BUILD_HOUSE, 3, entity);
	// 	delete entity;
	// 	delete job;
	// }