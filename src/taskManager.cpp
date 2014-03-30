#include "taskManager.h"

TaskManager taskManager;
std::vector<Entity *> foodEntities;
std::vector<Entity *> ironEntities;
std::vector<Entity *> stoneEntities;
std::vector<Entity *> woodEntities;

void TaskManager::assign()
{
	//pop from unassignedTaskList
	//pop a villager
	//if a gatherTask, find the nearest resource for the villager
	//if a buildTask, set target to job target
	//if a militaryTask, set target to job target
    TaskReference task = unassignedTaskQueue.top();
    TaskType taskType = task->getType();
    
    unassignedTaskQueue.pop();
	inProgressTaskList.push_back(task);
    Entity * villager = getVillager();
    availableVillagers.pop_back();
    
	if(taskType == TASK_GATHER_FOOD
		or taskType == TASK_GATHER_IRON
		or taskType == TASK_GATHER_WOOD
		or taskType == TASK_GATHER_STONE)
	{
		
        task->setAssignee(villager);
		task->setTarget(this->findTarget(villager, taskType));
        
	}else if(taskType == TASK_BUILD_HOUSE
		or taskType == TASK_BUILD_STONEWORKS
		or taskType == TASK_BUILD_SMELTING
		or taskType == TASK_BUILD_FARM
		or taskType == TASK_BUILD_LUMBERMILL
		or taskType == TASK_BUILD_STOREHOUSE
		or taskType == TASK_BUILD_WEAPONSMITH
		or taskType == TASK_BUILD_ARMORSMITH
		or taskType == TASK_BUILD_WATCHTOWER
		or taskType == TASK_BUILD_TOWNCENTER)
	{
        
		task->setAssignee(villager);
        
	}else if(taskType == TASK_ATTACK
		or taskType == TASK_DEFEND
		or taskType == TASK_PATROL
		or taskType == TASK_TAME_1
		or taskType == TASK_PARLEY)
	{
        
		task->setAssignee(villager);
        
	}
}

TaskQueue TaskManager::getUnassignedTaskList() {
    return unassignedTaskQueue;
}

void TaskManager:: registerVillager(Entity * villager)
{
    availableVillagers.push_back(villager);
}

Entity * TaskManager::getVillager()
{
    return availableVillagers.back();
}

EntityVec TaskManager::getavailableVillagers()
{
    return availableVillagers;
}

TaskVec TaskManager::getInProgressTaskList()
{
    return inProgressTaskList;
}

void TaskManager::updateProgress()
{
	for (TaskIter it = inProgressTaskList.begin() ; it != inProgressTaskList.end(); ++it)
	{
		std::cout<<"Updating task progress"<<std::endl;
	}
}

TaskQueue TaskManager::getUnassignedTaskQueue()
{
    return unassignedTaskQueue;
}

Entity * TaskManager::findTarget(Entity * villager, TaskType taskType)
{
	Entity * nearestTarget = nullptr;
	double min = 0;
    for (EntityIter it = mapTaskResource[taskType].begin() ; it != mapTaskResource[taskType].end(); ++it)
	{
        Position p = (*it)->getPosition();
        //foodEntities.push_back(villager);
		std::cout<<"Find the closest target"<<std::endl;
		if(min > villager->getPosition().distance(p))
			nearestTarget = *it;
	}
	std::cout<<"Find the closest target"<<std::endl;
	return nearestTarget;
}

void TaskManager::registerTask(TaskReference task)
{
    unassignedTaskQueue.push(task);
}


void TaskManager::cleanTaskList()
{
	std::cout<<"Remove completed task from inProgressTaskList!"<<std::endl;
	for (TaskIter it = inProgressTaskList.begin() ; it != inProgressTaskList.end(); ++it)
	{
		if((*it)->isCompleted())
			{
				inProgressTaskList.erase(it);
				availableVillagers.push_back((*it)->getAssignee());
				delete *it;
			}
	}
}