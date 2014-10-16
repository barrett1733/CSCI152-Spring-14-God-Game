//
//  File: task-manager.h
//  Author: Jimmy Ouyang
//  CSci 152
//  Spring 2014
//
//  Task Manager is responsible for
//		Creating tasks
//		Maintaining tasks
//		Assign tasks to villagers
//		Update tasks
//		Remove complete tasks
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

typedef std::vector<MobileEntityReference> MobileEntityList;
typedef MobileEntityList ::iterator MobileEntityIter;

typedef std::vector<EntityReference> EntityList;
typedef EntityList ::iterator EntityIter;

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

enum ResourceGroup
{
    RG_NONE,
    RG_FOOD,
    RG_WOOD,
    RG_IRON,
    RG_STONE
};

class TaskManager
{
private:
	TaskQueue unassignedTaskQueue;
	TaskVec inProgressTaskList;
	//EntityList availableVillagers;
    static std::map<TaskType, ResourceGroup> taskResourceGroupMap;

public:
	void assign(MobileEntityList & villagerList, EntityList & resourceList);
	void updateProgress();
	void registerTask(TaskReference task);

    Position getNearestResource(MobileEntityReference villager, EntityList & resourceList, TaskType taskType);
//	Entity * getNearestResource(Entity * villager, EntityList ev);
//	Entity * findResource(Entity *, TaskType);

	TaskVec getInProgressTaskList();
	TaskQueue getUnassignedTaskQueue();
    TaskGroup getTaskGroup(TaskType type);
    ResourceGroup getResourceGroup(EntityType type);
	void cleanTaskList(MobileEntityList & villagerList);
};
#endif

extern TaskManager taskManager;
