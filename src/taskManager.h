//
//  CSCI 152, Spring 2014, God Game
//

#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include "entity.h"
#include "position.h"
#include ""

struct Comparator
{
  bool operator()(const TaskReference task1, const TaskReference task2)
  {
    return task1.getPriority()>task2.getPriority();
  }
};

class TaskManager()
{
private:
	std::priority_queue<TaskReference, unassignedTaskList, Comparator> q;
	std::vector<TaskReference> unassignedTaskList;
	std::vector<TaskReference> inProgressTaskList;
public:
	void assign(Entity * villager, Entity * target);
	void updateStatus(TaskStatus status);
	void updateProgress(int progress);
	void cleanTaskList();
	Entity * find();
}
#endif