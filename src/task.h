//
//  CSCI 152, Spring 2014, God Game
//

#ifndef TASK_H_
#define TASK_H_

#include "entity.h"
#include "position.h"

enum TaskType
{
	TASK_NONE = 0x00,

	TASK_GATHER_FOOD = 0x01,
	TASK_GATHER_IRON,
	TASK_GATHER_WOOD,
	TASK_GATHER_STONE,
	
	TASK_BUILD_HOUSE = 0x100,
	TASK_BUILD_STONEWORKS,
	TASK_BUILD_SMELTING,
	TASK_BUILD_FARM,
	TASK_BUILD_LUMBERMILL,
	TASK_BUILD_STOREHOUSE,
	TASK_BUILD_WEAPONSMITH,
	TASK_BUILD_ARMORSMITH,
	TASK_BUILD_WATCHTOWER,
	TASK_BUILD_TOWNCENTER,

	TASK_ATTACK = 0x10000,
	TASK_DEFEND,
	TASK_PATROL,
	TASK_TAME_1,
	TASK_PARLEY,

};

enum TaskStatus { 
	UNASSIGNED = 0x01,
	IN_PROGRESS,
	COMPLETED
	//...
};

class Task
{
protected:
	TaskType _type;
	Entity * _target;
	Entity * _assignee;
	int _priority;
	TaskStatus _status;
	int _progress;

public:
	Task(TaskType type, Entity * target, Entity * villager, int priority, TaskStatus status, int progress);
	void setType(TaskType type);
	void setTarget(Entity * target);
	void setAssignee(Entity * villager);
	void setStatus(TaskStatus status);
	void setProgress(int progress);
	TaskType getType();
	Entity * getTarget();
	Entity * getAssignee();
	TaskStatus getStatus();
	int getProgress();
	bool isCompleted();

};

class GatherTask : public Task 
{
private:
	int amount;
};


class BuildTask : public Task 
{

};

class MilitaryTask : public Task 
{

};
#endif

typedef Task * TaskReference;