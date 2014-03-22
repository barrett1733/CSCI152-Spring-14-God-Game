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

// enum TaskStatus { 
// 	UNASSIGNED = 0x01,
// 	IN_PROGRESS,
// 	COMPLETED
// 	//...
// };

class Task
{
protected:
	TaskType _type;
	Entity * _target;
	Entity * _assignee;
	int _priority;
	int _progress;

public:
	Task(TaskType type, int priority, int progress);
	void setType(TaskType type);
	void setTarget(Entity * target);
	void setAssignee(Entity * villager);
	TaskType getType();
	Entity * getTarget();
	Entity * getAssignee();
	bool virtual isCompleted() = 0;
};

class GatherTask : public Task 
{
private:
	int _amount;
public:
	Entity * virtual find() = 0;
	bool isCompleted();
};

class GatherFoodTask : public GatherTask
{
	Entity * find();
};

class GatherWoodTask : public GatherTask
{
	Entity * find();
};

class GatherIronTask : public GatherTask
{
	Entity * find();
};

class GatherRockTask : public GatherTask
{
	Entity * find();
};

class BuildTask : public Task 
{
	//...
	bool isCompleted();
};

class MilitaryTask : public Task 
{
	//...
	bool isCompleted();
};
#endif

typedef Task * TaskReference;