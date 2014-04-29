
#include "job.h"

std::map<JobType, TaskType> Job::mp = {
    {JOB_BUILD_HOUSE, TASK_BUILD_HOUSE},
    {JOB_BUILD_STONEWORKS, TASK_BUILD_STONEWORKS},
    {JOB_BUILD_SMELTING, TASK_BUILD_SMELTING},
    {JOB_BUILD_FARM, TASK_BUILD_FARM},
    {JOB_BUILD_LUMBERMILL, TASK_BUILD_LUMBERMILL},
    {JOB_BUILD_WEAPONSMITH, TASK_BUILD_WEAPONSMITH},
    {JOB_BUILD_ARMORSMITH, TASK_BUILD_ARMORSMITH},
    {JOB_BUILD_WATCHTOWER, TASK_BUILD_WATCHTOWER},
    {JOB_BUILD_TOWNCENTER, TASK_BUILD_TOWNCENTER},
    {JOB_BUILD_TEMPLE, TASK_BUILD_TEMPLE}
};

std::map<JobType, int> Job::mapBuildTaskNum = {
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

std::map<JobType, int> Job::mapBuildingHealth = {
    {JOB_BUILD_HOUSE, 100},
    {JOB_BUILD_SMELTING, 100},
    {JOB_BUILD_STONEWORKS, 100},
    {JOB_BUILD_FARM, 100},
    {JOB_BUILD_LUMBERMILL, 100},
    {JOB_BUILD_WEAPONSMITH, 100},
    {JOB_BUILD_ARMORSMITH, 100},
    {JOB_BUILD_WATCHTOWER, 100},
    {JOB_BUILD_TOWNCENTER, 100},
    {JOB_BUILD_TEMPLE, 100}
};

Job::Job(JobType type, int priority) :
	_type(type),
	_priority(priority)
{ }

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


void Job::cleanTaskList()
{
	for(TaskIter iter = _taskList.begin(); iter != _taskList.end(); )
	{
		if ((*iter)->isCompleted() == true)
		{
			delete(*iter);
			_taskList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
//	std::cout<<"Task list size is: "<<t.size()<<std::endl;
}


GatherJob::GatherJob(JobType type, int priority, ResourceCost resourceCost):
	Job(type, priority), cost(resourceCost)
{
	this->createTaskList();
};

void GatherJob::createTaskList()
{
    
    for(int i = 0; i < ( (cost.food + 10) / 20 ); i++)
	{
		TaskReference task = new Task(TASK_GATHER_FOOD, _priority, 20);
        
		_taskList.push_back(task);
	}
    
    for(int i = 0; i < ( (cost.wood + 10) / 20 ); i++)
	{
		TaskReference task = new Task(TASK_GATHER_WOOD, _priority, 20);
        
		_taskList.push_back(task);
	}
    
    for(int i = 0; i < ( (cost.iron + 10) / 20 ); i++)
	{
		TaskReference task = new Task(TASK_GATHER_IRON, _priority, 20);
        
		_taskList.push_back(task);
	}
    
    for(int i = 0; i < ( (cost.stone + 10) / 20 ); i++)
	{
		TaskReference task = new Task(TASK_GATHER_STONE, _priority, 20);
        
		_taskList.push_back(task);
	}
}

BuildJob::BuildJob(JobType type, int priority, Position psn):
	Job(type, priority),
    _target(psn)
{
    _taskNum = mapBuildTaskNum[type];
    _taskQuota = mapBuildingHealth[type] / mapBuildTaskNum[_type];
	this->createTaskList();
};

void BuildJob::createTaskList()
{
	for(int i = 0; i < mapBuildTaskNum[_type]; i++)
	{
		TaskReference task = new Task(mp[_type], _priority, _target, _taskQuota);
		_taskList.push_back(task);
	}
}

MilitaryJob::MilitaryJob(JobType type, int priority, Position psn):
    Job(type, priority),
    _target(psn)
{
    _taskNum = mapBuildTaskNum[type];
    _taskQuota = mapBuildingHealth[type] / mapBuildTaskNum[_type];
	this->createTaskList();
}

void MilitaryJob::createTaskList()
{
	for(int i=0; i<mapBuildTaskNum[_type]; i++)
	{
		TaskReference task = new Task(mp[_type], _priority, _target, _taskQuota);
		_taskList.push_back(task);
	}
}

// int main(){
//        Position p;
// 	Entity * entity = new Entity(ET_HOUSE, 100, p);
// 	JobReference job = new BuildJob(JOB_BUILD_HOUSE, 3, entity);
// 	delete entity;
// 	delete job;
// }
