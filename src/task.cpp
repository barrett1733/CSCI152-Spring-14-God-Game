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

	bool GatherTask::isCompleted()
	{
		return this->_amount == this->_progress;
	}


	GatherTask::GatherTask(TaskType type, int priority, int progress, int amount):
	Task(type, priority, progress, amount) {};

	// void GatherTask::updateProgress(int gathering)
	// {
	// 	this->_progress += gathering;
	// }

	// Entity * GatherFoodTask::find()
	// {
	// 	if(this->assignee)
	// 	{
	// 		std::cout<<"Find the nearest resource for food"<<std::endl;
	// 		return null;
	// 	}
	// }

	// Entity * GatherWoodTask::find()
	// {
	// 	if(this->assignee)
	// 	{
	// 		std::cout<<"Find the nearest resource for wood"<<std::endl;
	// 		return null;
	// 	}
	// }

	// Entity * GatherIronTask::find()
	// {
	// 	if(this->assignee)
	// 	{
	// 		std::cout<<"Find the nearest resource for iron"<<std::endl;
	// 		return null;
	// 	}
	// }

	// Entity * GatherRockTask::find()
	// {
	// 	if(this->assignee)
	// 	{
	// 		std::cout<<"Find the nearest resource for rock"<<std::endl;
	// 		return null;
	// 	}
	// }

	BuildTask::BuildTask(TaskType type, Entity * target, int priority, int hpBuilt, int hpAmount):
	Task(type, priority, hpBuilt, hpAmount), _target(target){}

	void GatherTask::updateProgress(int building)
	{
		this->_progress += building;
	}

	MilitaryTask::MilitaryTask(TaskType type, Entity * target, int priority, int hpDamaged, int hpAmount):
	Task(type, priority, hpDamaged, hpAmount), _target(target){}