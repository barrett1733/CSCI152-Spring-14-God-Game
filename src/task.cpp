#include "task.h"

Task::Task(TaskType type, int priority, int cost) :
	_type(type),
	_priority(priority),
    _taskQuota(cost)
{ }

Task::Task(TaskType type, int priority, Position psn, int cost) :
	_type(type),
	_priority(priority),
    _position(psn),
    _taskQuota(cost)
{ }

Task::Task(TaskType type, int priority, Entity * target, int cost) :
    _type(type),
    _priority(priority),
    _target(target),
    _position(target->getPosition()),
    _taskQuota(cost)
{ }

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

Position Task::getPosition()
{
    return this->_position;
}

bool Task::isCompleted()
{
	return this->_taskQuota == this->_progress;
}
