//
//  CSCI 152, Spring 2014, God Game
//

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include "entity.h"
#include "position.h"
#include <vector>
#include <iostream>
#include "task.h"
#include <queue>
#include <set>
//#include "worldGen.h"

struct Comparator
{
  bool operator()(const TaskReference task1, const TaskReference task2)
  {
    return task1->getPriority()>task2->getPriority();
  }
};

class TaskManager
{
private:
    std::set<TaskReference, Comparator> unassignedTaskList;
    std::vector<TaskReference> inProgressTaskList;
    std::vector<Entity *> availableVillagers;

public:
	void assign(Entity * villager, Entity * target);
	void updateProgress();
	void registerTask(TaskReference task);
    void updatePQ();
    Entity * getVillager();
    void findTarget();
	void cleanTaskList();
	Entity * find();
};
#endif

extern TaskManager taskManager;