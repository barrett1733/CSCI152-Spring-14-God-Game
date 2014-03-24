#include "taskManager.h"

TaskManager taskManager;

void TaskManager::assign(Entity * villager, Entity * target)
{
	//pop from unassignedTaskList
	//pop a villager
	//if a gatherTask, find the nearest resource for the villager
	//if a buildTask, set target to job target
	//if a militaryTask, set target to job target
    std::set<TaskReference>::iterator i = unassignedTaskList.begin();
    TaskReference task = *i;
    unassignedTaskList.erase(i);
	inProgressTaskList.push_back(task);
	if(strcmp(typeid(*task).name(),"GatherTask")==0)
	{
		task->setAssignee(villager);
		//findTarget(villager);
		//task.setTarget(target);
	}else if(strcmp(typeid(*task).name(),"BuildTask")==0)
	{
		task->setAssignee(villager);
	}else if(strcmp(typeid(*task).name(),"MilitaryTask")==0)
	{
		task->setAssignee(villager);
	}
}

Entity * TaskManager::getVillager()
{
//    if(!availableVillagers.empty())
  //       *(availableVillagers.begin());
	std::cout<<availableVillagers.size()<<std::endl;
    return *(availableVillagers.begin());
}

void TaskManager::updateProgress()
{
	for (std::vector<TaskReference>::iterator it = inProgressTaskList.begin() ; it != inProgressTaskList.end(); ++it)
	{
		std::cout<<"Updating task progress"<<std::endl;
	}
}

void TaskManager::findTarget()
{
	// for(int i=0; i<entityList.size(); i++)
	// {
	// 	std::cout<<"Find the closest target"<<endl;
	// }
	std::cout<<"Find the closest target"<<std::endl;
}

void TaskManager::registerTask(TaskReference task)
{
	unassignedTaskList.insert(task);
	std::cout<<"Unassigned task list size is: "<<unassignedTaskList.size()<<std::endl;
}


void TaskManager::cleanTaskList()
{
	std::cout<<"Remove completed task from inProgressTaskList!"<<std::endl;
	for (std::vector<TaskReference>::iterator it = inProgressTaskList.begin() ; it != inProgressTaskList.end(); ++it)
	{
		if((*it)->isCompleted())
			{
				inProgressTaskList.erase(it);
				availableVillagers.push_back((*it)->getAssignee());
				delete *it;
			}
	}
}