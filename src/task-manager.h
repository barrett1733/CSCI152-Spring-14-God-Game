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
extern std::vector<Entity *> foodEntities;
extern std::vector<Entity *> ironEntities;
extern std::vector<Entity *> stoneEntities;
extern std::vector<Entity *> woodEntities;

typedef std::vector<Entity *> EntityVec;
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

//typedef std::map<TaskType, std::vector<Entity *>> TaskResourceMap;
//typedef std::map<TaskType, ResourceType> TaskResourceTypeMap;

//static TaskResourceMap mapTaskResource = {
//    {TASK_GATHER_FOOD, foodEntities},
//    {TASK_GATHER_IRON, ironEntities},
//    {TASK_GATHER_STONE, stoneEntities},
//    {TASK_GATHER_WOOD, woodEntities}
//};

// static TaskResourceTypeMap mapTaskResourceType = {
// 	{TASK_GATHER_FOOD, RS_FOOD},
// 	{TASK_GATHER_IRON, RS_IRON},
// 	{TASK_GATHER_STONE, RS_STONE},
// 	{TASK_GATHER_WOOD, RS_WOOD}
// };

class TaskManager
{
private:
	TaskQueue unassignedTaskQueue;
	TaskVec inProgressTaskList;
	EntityVec availableVillagers;

public:
	void assign();
	void updateProgress();
	void registerTask(TaskReference task);
	void registerVillager(Entity * villager);
	Entity * getVillager();
	TaskQueue getUnassignedTaskList();
	Entity * getNearestResource(Entity * villager, EntityVec ev);
	Entity * findResource(Entity *, TaskType);
	EntityVec getavailableVillagers();
	TaskVec getInProgressTaskList();
	TaskQueue getUnassignedTaskQueue();
	void cleanTaskList();
};
#endif

extern TaskManager taskManager;
