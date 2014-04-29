#include "task-manager.h"

//std::vector<Entity *> foodEntities;
//std::vector<Entity *> ironEntities;
//std::vector<Entity *> stoneEntities;
//std::vector<Entity *> woodEntities;

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

		if(this->getTaskGroup(taskType) == TG_GATHER)
		{

			task->setAssignee(villager);
            //findNearestResource -- Should be defined somewhere else
			//task->setTarget(new Entity());
            
		}
		else if(this->getTaskGroup(taskType) == TG_BUILD)
		{

			task->setAssignee(villager);

		}
		else if(this->getTaskGroup(taskType) == TG_MILITARY)
		{

			task->setAssignee(villager);

		}
        //findPath() -- Maybe somewhere else
	}

}

TaskQueue TaskManager::getUnassignedTaskList()
{
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
		int taskProgress = task->getProgress();
		Position p = task->getPosition();

		if (task->getAssignee()->getPosition().distance(p) == 0)
		{
			task->setProgress(++taskProgress);
		}

		//std::cout<<"Updating task progress"<<std::endl;
	}
}

TaskQueue TaskManager::getUnassignedTaskQueue()
{
	return unassignedTaskQueue;
}

//Entity * TaskManager::findResource(Entity * villager, TaskType taskType)
//{
//	if (taskType == TASK_GATHER_FOOD)
//	{
//		return getNearestResource(villager, foodEntities);
//	}
//	else if (taskType == TASK_GATHER_IRON)
//	{
//		return getNearestResource(villager, ironEntities);
//	}
//	else if (taskType == TASK_GATHER_STONE)
//	{
//		return getNearestResource(villager, stoneEntities);
//	}
//	else if (taskType == TASK_GATHER_WOOD)
//	{
//		return getNearestResource(villager, woodEntities);
//	}
//	return getNearestResource(villager, foodEntities);
//}
//
//Entity * TaskManager::getNearestResource(Entity * villager, EntityVec ev)
//{
//	Entity * nearestTarget = nullptr;
//	double min = DBL_MAX;
//	for (EntityIter it = ev.begin(); it != ev.end(); ++it)
//	{
//		Position p = (*it)->getPosition();
//		if(min > (villager->getPosition().distance(p)))
//		{
//			min = villager->getPosition().distance(p);
//			nearestTarget = *it;
//		}
//	}
//    ev.erase(std::find(ev.begin(), ev.end(), nearestTarget));
//	return nearestTarget;
//}

void TaskManager::registerTask(TaskReference task)
{
	unassignedTaskQueue.push(task);
}

TaskGroup TaskManager::getTaskGroup(TaskType type)
{
    if (type < TASK_BUILD_HOUSE) return TG_GATHER;
    if (type < TASK_ATTACK) return TG_BUILD;
    else return TG_MILITARY;
}

void TaskManager::cleanTaskList()
{
	for (TaskIter iter = inProgressTaskList.begin(); iter != inProgressTaskList.end(); ++iter)
	{
		if ((*iter)->isCompleted())
		{
			//delete(*iter);
			iter = inProgressTaskList.erase(iter);
			availableVillagers.push_back((*iter)->getAssignee());
            
//            //Make the resource available again if it is not empty
//            if((*iter)->getTarget()->getCurrentHealth() > 0)
//            {
//                switch((*iter)->getType())
//                {
//                    case TASK_GATHER_FOOD:
//                        foodEntities.push_back((*iter)->getTarget());
//                        break;
//                    case TASK_GATHER_IRON:
//                        ironEntities.push_back((*iter)->getTarget());
//                        break;
//                    case TASK_GATHER_STONE:
//                        stoneEntities.push_back((*iter)->getTarget());
//                        break;
//                    case TASK_GATHER_WOOD:
//                        woodEntities.push_back((*iter)->getTarget());
//                        break;
//                    default:
//                        break;
//                }
//                
//            }
            
		}
	}
}
