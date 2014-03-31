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
    TASK_BUILD_TEMPLE,

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
    int _taskQuota;

public:
	Task(TaskType type, int priority, int progress, int);
	void setType(TaskType type);
	void setTarget(Entity * target);
	void setAssignee(Entity * villager);
    void setPriority(int priority);
    void setProgress(int progress);
	TaskType getType();
	Entity * getTarget();
	Entity * getAssignee();
    int getProgress();
    int getPriority();
    int getQuota();
	bool isCompleted();
};

class GatherTask : public Task 
{
public:
    GatherTask(TaskType, int, int, int);
};

class BuildTask : public Task 
{
	//...
public:
    BuildTask(TaskType, Entity *, int, int, int);
};

class MilitaryTask : public Task 
{
	//...
public:
    MilitaryTask(TaskType, Entity *, int, int, int);
};
#endif

typedef Task * TaskReference;