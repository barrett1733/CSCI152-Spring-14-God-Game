//
//  CSCI 152, Spring 2014, God Game
//

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <vector>
#include <iostream>
#include "task.h"
#include <queue>
#include <set>
#include <map>
#include <assert.h>
#include "resource-manager.h"
#include <memory>
#include "world-gen.h"
#include <float.h>
//#include "worldGen.h"
//extern std::vector<Entity *> foodEntities;
//extern std::vector<Entity *> ironEntities;
//extern std::vector<Entity *> stoneEntities;
//extern std::vector<Entity *> woodEntities;

typedef std::vector<MobileEntityReference> MobileEntityVec;
typedef MobileEntityVec ::iterator MobileEntityIter;

typedef std::vector<EntityReference> EntityVec;
typedef EntityVec ::iterator EntityIter;

typedef std::vector<TaskReference> TaskVec;
typedef TaskVec::iterator TaskIter;

struct Comparator
{
	bool operator()(const TaskReference task1, const TaskReference task2)
	{
		return task1->getPriority() < task2->getPriority();
	}
};

typedef std::priority_queue<TaskReference, TaskVec, Comparator> TaskQueue;

enum TaskGroup
{
    TG_NONE,
    TG_GATHER,
    TG_BUILD,
    TG_MILITARY
};

class TaskManager
{
private:
	TaskQueue unassignedTaskQueue;
	TaskVec inProgressTaskList;
	//EntityVec availableVillagers;

public:
	void assign(MobileEntityVec & villagerList);
	void updateProgress();
	void registerTask(TaskReference task);

//	Entity * getNearestResource(Entity * villager, EntityVec ev);
//	Entity * findResource(Entity *, TaskType);

	TaskVec getInProgressTaskList();
	TaskQueue getUnassignedTaskQueue();
    TaskGroup getTaskGroup(TaskType type);
	void cleanTaskList(MobileEntityVec & villagerList);
};
#endif

extern TaskManager taskManager;
