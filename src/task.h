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

class Task
{
protected:
	TaskType _type;
	Position _position;
	Entity * _assignee;
    Entity * _target;
	int _priority;
	int _progress;
	int _taskQuota;

public:
    //Constructor for Gather Task
	Task(TaskType type, int priority, int);
    //Constructor for Build Task
	Task(TaskType type, int priority, Position, int);
    //Constructor for Military Task
    Task(TaskType type, int priority, Entity *, int);
    
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
    Position getPosition();
	bool isCompleted();
};

#endif

typedef Task * TaskReference;
