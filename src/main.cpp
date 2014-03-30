
#include <iostream>
#include <sstream>
#include "job-manager.h"
#include <vector>

int main(int argc, char **argv)
{
    jobManager.createJobList(JOB_BUILD_HOUSE, 3, 100);
    assert(jobManager.getJobList().size() == 1);
    assert((*jobManager.getJobList().begin())->getPriority() == 3);
    //std::cout<<taskManager.getUnassignedTaskList().size();
    //assert(taskManager.getUnassignedTaskList().size() == 1);
    
    jobManager.createJobList(JOB_GATHER_WOOD, 7, 100);
    //assert(taskManager.getUnassignedTaskList().size() == 6);
    //assert((taskManager.getUnassignedTaskQueue)->getPriority() == 3);
    
    jobManager.createJobList(JOB_GATHER_WOOD, 3, 101);
    //assert(taskManager.getUnassignedTaskList().size() == 12);
    
    Position p1, p2, p3;
    p1.x = 10;
    p2.x = 20;
    p3.x = 30;
    p1.y = 10;
    p2.y = 20;
    p3.y = 30;
    
    Entity * v1 = new Entity (ET_VILLAGER, 20, p1);
    Entity * v2 = new Entity (ET_VILLAGER, 20, p2);
    Entity * v3 = new Entity (ET_VILLAGER, 20, p3);
    v1->setName("Villager one");
    v2->setName("Villager two");
    v3->setName("Villager three");
    
    taskManager.registerVillager(v1);
    taskManager.registerVillager(v2);
    taskManager.registerVillager(v3);
    
    assert(taskManager.getavailableVillagers().size() == 3);
    
    typedef std::vector<Entity *> entityVec;
    typedef entityVec ::iterator entityIter;
    
    typedef std::vector<TaskReference> taskVec;
    typedef taskVec::iterator taskIter;
    
    typedef std::priority_queue<TaskReference, taskVec, Comparator> taskQ;
    
    taskQ taskQueue = taskManager.getUnassignedTaskQueue();
    entityVec villagerVec = taskManager.getavailableVillagers();
    taskVec ipTaskVec = taskManager.getInProgressTaskList();
    

    //entityIter it = villagerVec.begin();
    //std::cout<<(*it)->getName()<<std::endl;
    
    taskManager.assign();
    
    villagerVec = taskManager.getavailableVillagers();
    ipTaskVec = taskManager.getInProgressTaskList();
    
    assert(villagerVec.size() == 2);
    //assert(taskManager.getUnassignedTaskList().size() == 11);
    assert(ipTaskVec.size() == 1);
    assert((*ipTaskVec.begin())->getPriority() == 7);
    assert((*ipTaskVec.begin())->getAssignee()->getName() == "Villager three");
    assert((*ipTaskVec.begin())->getAssignee()->getPosition().x == 30);
    
    assert((*ipTaskVec.begin())->getAssignee()->getPosition().y == 30);
    
    taskManager.assign();
    
    villagerVec = taskManager.getavailableVillagers();
    ipTaskVec = taskManager.getInProgressTaskList();
    
    assert(villagerVec.size() == 1);
    //assert(taskManager.getUnassignedTaskList().size() == 11);
    assert(ipTaskVec.size() == 2);
    
    assert((*ipTaskVec.begin())->getPriority() == 7);
    
    assert((ipTaskVec.back())->getAssignee()->getName() == "Villager two");
    assert(((ipTaskVec.back()))->getAssignee()->getPosition().x == 20);
    
    assert((ipTaskVec.back())->getAssignee()->getPosition().y == 20);
    
//Test Task progress update
    

    
    
    
    ///TaskReference task = new GatherTask(TASK_GATHER_FOOD, 3, 3, 3);
    
//    Position p, q;
//    p.x = 10;
//    p.y = 10;
//    q.x = 20;
//    q.y = 20;
//    std::cout<<p.distance(q)<<std::endl;
//    
//    Entity * ety = new Entity(ET_VILLAGER, 20, p);
//    std::cout<<ety->getCurrentHealth()<<std::endl;
//    std::cout<<(*ety).getCurrentHealth()<<std::endl;
//    
//    int i = 10;
//    int* j = &i;
//    
//    std::cout<<j<<" "<<&j<<std::endl;
//    
//    std::vector<int> v = {1, 2, 3};
//    std::cout<<*(v.begin());
    
	return 0;
}