#include "taskManager.h"

void TaskManager::assign(Entity * villager, Entity * target)
{
	//pop from unassignedTaskList
	//pop a villager
	//if a gatherTask, find the nearest resource for the villager
	//if a buildTask, set target to job target
	//if a militaryTask, set target to job target
	TaskReference task = q.pop_back()
	task.setStatus(InProgress);
	inProgressTaskList.push_back(task);
	Entity * villager = availableVillager.pop_back();
	Entity * target;
	if(typeof(task)=="GatherTask")
	{
		task.setAssignee(villager);
		if(task->getType()=="TASK_GATHER_FOOD")
		{
			std::cout<<"find the nearest resource for food"<<std::endl;
		}else if (task->getType()=="TASK_GATHER_WOOD")
		{
			std::cout<<"find the nearest resource for wood"<<std::endl;
		}else if (task->getType()=="TASK_GATHER_IRON")
		{
			std::cout<<"find the nearest resource for iron"<<std::endl;
		}else if (task->getType()=="TASK_GATHER_STONE")
		{
			std::cout<<"find the nearest resource for stone"<<std::endl;
		}
		task.setTarget(target);
	}else if(typeof(task)=="BuildTask")
	{
		task.setAssignee(villager);
	}else if(typeof(task)=="MilitaryTask")
	{
		task.setAssignee(villager);
	}
}

void TaskManager::updateProgress()
{
	for (std::vector<TaskReference>::iterator it = inProgressTaskList.begin() ; it != inProgressTaskList.end(); ++it)
	{
		std::cout<<"Updating task progress"<<std::endl;
	}
}



void TaskManager::cleanTaskList()
{
	std::cout<<"Remove completed task from inProgressTaskList!"<<std::endl;
	for (std::vector<TaskReference>::iterator it = inProgressTaskList.begin() ; it != inProgressTaskList.end(); ++it)
	{
		if(it.isCompleted())
			inProgressTaskList.remove(it);
		std::cout<<"Updating task progress"<<std::endl;			
	}
}