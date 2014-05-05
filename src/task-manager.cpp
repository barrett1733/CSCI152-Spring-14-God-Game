#include "task-manager.h"

std::map<TaskType, ResourceGroup> TaskManager::taskResourceGroupMap
{
    { TASK_GATHER_FOOD, RG_FOOD },
    { TASK_GATHER_WOOD, RG_WOOD },
    { TASK_GATHER_IRON, RG_IRON },
    { TASK_GATHER_STONE, RG_STONE }
};

void TaskManager::assign(MobileEntityVec & villagerList, EntityVec & resourceList)
{
	//pop from unassignedTaskList
	//pop a villager
	//if a gatherTask, find the nearest resource for the villager
	//if a buildTask, set target to job target
	//if a militaryTask, set target to job target
	while (!villagerList.empty()) {
		TaskReference task = unassignedTaskQueue.top();
		TaskType taskType = task->getType();

		unassignedTaskQueue.pop();
		inProgressTaskList.push_back(task);
		MobileEntityReference villager = villagerList.back();
        //std::cout << villager->getName() << std::endl;
		villagerList.pop_back();

		if(this->getTaskGroup(taskType) == TG_GATHER)
		{

			task->setAssignee(villager);
            task->setPosition(getNearestResource(villager, resourceList, taskType));
            
		}
		else if(this->getTaskGroup(taskType) == TG_BUILD)
		{

			task->setAssignee(villager);

		}
		else if(this->getTaskGroup(taskType) == TG_MILITARY)
		{

			task->setAssignee(villager);

		}
        villager->setTask(task);
        //findPath() -- Maybe somewhere else
	}

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


Position TaskManager::getNearestResource(MobileEntityReference villager, EntityVec & resourceList, TaskType taskType)
{
	EntityReference nearestTarget = nullptr;
	double min = DBL_MAX;
	for (EntityIter it = resourceList.begin(); it != resourceList.end(); ++it)
	{
        if (getResourceGroup( (*it)->getType() ) == taskResourceGroupMap[taskType])
        {
            Position p = (*it)->getPosition();
            if(min > (villager->getPosition().distance(p)))
            {
                min = villager->getPosition().distance(p);
                nearestTarget = *it;
            }
        }
	}

	return nearestTarget->getPosition();
}

void TaskManager::registerTask(TaskReference task)
{
	unassignedTaskQueue.push(task);
}

TaskGroup TaskManager::getTaskGroup(TaskType type)
{
    if (type < TASK_BUILD_HOUSE) return TG_GATHER;
    else if (type < TASK_ATTACK) return TG_BUILD;
    else return TG_MILITARY;
}

ResourceGroup TaskManager::getResourceGroup(EntityType type)
{
    if (type > ET_RESOURCE && type < ET_BOULDER)
        return RG_WOOD;
    else if (type > ET_SHRUB_2 && type < ET_COAL)
        return RG_STONE;
    else if (type > ET_COAL && type < ET_COPPER)
        return RG_IRON;
    else if (type > ET_DOMESTIC && type < ET_BUILDING)
        return RG_FOOD;
    return RG_NONE;
}

void TaskManager::cleanTaskList(MobileEntityVec & villagerList)
{
	for (TaskIter iter = inProgressTaskList.begin(); iter != inProgressTaskList.end();)
	{
		if ((*iter)->isCompleted())
		{
			//delete(*iter);
			iter = inProgressTaskList.erase(iter);
			villagerList.push_back((*iter)->getAssignee());
        }else
            ++iter;
		
            //std::cout << villagerList.size() << std::endl;
            
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
