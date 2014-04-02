#include "task-manager.h"

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
	while (!availableVillagers.empty()) {
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
			task->setTarget(this->findResource(villager, taskType));

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
		TaskReference task = (*it);
		TaskType taskType = task->getType();
		int taskProgress = task->getProgress();
		Entity * target = task->getTarget();
		int targetHealth = target->getCurrentHealth();
		Position p = target->getPosition();

		if (task->getAssignee()->getPosition().distance(p) == 0)
		{
			task->setProgress(++taskProgress);

			if(taskType == TASK_GATHER_FOOD
			   or taskType == TASK_GATHER_IRON
			   or taskType == TASK_GATHER_WOOD
			   or taskType == TASK_GATHER_STONE)
			{
				// Doesn't compile; resourceManager isn't declared.
				// Not sure where it belongs though.
				// We'll have to think about this.
				// - CH, 2014.04.01
				//resourceManager.sendResource(mapTaskResourceType[taskType], 1, taskFaction);
				target->setCurrentHealth(--targetHealth);

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

				target->setCurrentHealth(++targetHealth);

			}else if(taskType == TASK_ATTACK
					 or taskType == TASK_DEFEND
					 or taskType == TASK_PATROL
					 or taskType == TASK_TAME_1
					 or taskType == TASK_PARLEY)
			{

				//...

			}
		}

		//std::cout<<"Updating task progress"<<std::endl;
	}
}

TaskQueue TaskManager::getUnassignedTaskQueue()
{
	return unassignedTaskQueue;
}

Entity * TaskManager::findResource(Entity * villager, TaskType taskType)
{
	if (taskType == TASK_GATHER_FOOD)
	{
		return getNearestResource(villager, foodEntities);
	}else if (taskType == TASK_GATHER_IRON)
	{
		return getNearestResource(villager, ironEntities);
	}else if (taskType == TASK_GATHER_STONE)
	{
		return getNearestResource(villager, stoneEntities);
	}else if (taskType == TASK_GATHER_WOOD)
	{
		return getNearestResource(villager, woodEntities);
	}
	return getNearestResource(villager, foodEntities);
}

Entity * TaskManager::getNearestResource(Entity * villager, EntityVec ev)
{
	Entity * nearestTarget = nullptr;
	double min = INFINITY;
	for (EntityIter it = ev.begin(); it != ev.end(); ++it)
	{
		Position p = (*it)->getPosition();
		if(min > (villager->getPosition().distance(p)))
		{
			min = villager->getPosition().distance(p);
			nearestTarget = *it;
		}
	}
	return nearestTarget;
}

void TaskManager::registerTask(TaskReference task)
{
	unassignedTaskQueue.push(task);
}


void TaskManager::cleanTaskList()
{
		for (TaskIter iter = inProgressTaskList.begin(); iter != inProgressTaskList.end(); ) {
			if ((*iter)->isCompleted())
			{
				//delete(*iter);
				iter = inProgressTaskList.erase(iter);
				availableVillagers.push_back((*iter)->getAssignee());
			}
			else
				++iter;
		}
}
