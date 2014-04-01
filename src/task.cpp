#include "task.h"

	Task::Task(TaskType type, int priority, int progress, int taskQuota):
	_type(type), _priority(priority), _progress(progress), _taskQuota(taskQuota){}
	
	void Task::setType(TaskType type)
	{
		this->_type = type;
	}

	void Task::setTarget(Entity * target)
	{
		this->_target = target;
	}

	void Task::setAssignee(Entity * villager)
	{
		this->_assignee = villager;
	}

    void Task::setProgress(int progress)
    {
        this->_progress = progress;
    }

    int Task::getPriority()
    {
        return _priority;
    }

	TaskType Task::getType()
	{
		return this->_type;
	}

	Entity * Task::getTarget()
	{
		return this->_target;
	}

	Entity * Task::getAssignee()
	{
		return this->_assignee;
	}

	int Task::getProgress()
	{
		return this->_progress;
	}

    int Task::getQuota()
    {
        return this->_taskQuota;
    }

	bool Task::isCompleted()
	{
		return this->_taskQuota == this->_progress;
	}


	GatherTask::GatherTask(TaskType type,  int priority, int progress, int amount):
	Task(type, priority, progress, amount) {};

	BuildTask::BuildTask(TaskType type, Entity * target, int priority, int hpBuilt, int hpAmount):
Task(type, priority, hpBuilt, hpAmount){_target = target;}

	MilitaryTask::MilitaryTask(TaskType type, Entity * target, int priority, int hpDamaged, int hpAmount):
	Task(type, priority, hpDamaged, hpAmount){_target = target;}