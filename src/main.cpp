
#include <iostream>
#include <sstream>
#include "job-manager.h"
#include <vector>

int main(int argc, char **argv)
{
    Entity * w1 = new Entity(ET_TREE, 100, 15, 15, FT_NONE);
    Entity * w2 = new Entity(ET_TREE, 100, 25, 25, FT_NONE);
    w1->setName("Tree1");
    w2->setName("Tree2");
    woodEntities.push_back(w1);
    woodEntities.push_back(w2);
    
    TaskManager * taskManager = jobManager.getTaskManager();
    jobManager.createJobList(JOB_BUILD_HOUSE, 3, 100);
    assert(jobManager.getJobList().size() == 1);
    assert((*jobManager.getJobList().begin())->getPriority() == 3);
    //std::cout<<taskManager.getUnassignedTaskList().size();
    //assert(taskManager.getUnassignedTaskList().size() == 1);
    
    //jobManager.createJobList(JOB_GATHER_WOOD, 7, 100);
    //assert(taskManager.getUnassignedTaskList().size() == 6);
    //assert((taskManager.getUnassignedTaskQueue)->getPriority() == 3);
    
    jobManager.createJobList(JOB_GATHER_WOOD, 3, 101);
    //assert(taskManager.getUnassignedTaskList().size() == 12);
    
    Position p1, p2, p3, p4, p5;
    p1.x = 10;
    p2.x = 20;
    p3.x = 30;
    p4.x = 40;
    p5.x = 50;
    p1.y = 10;
    p2.y = 20;
    p3.y = 30;
    p4.y = 40;
    p5.y = 50;
    
    Entity * v1 = new Entity (ET_VILLAGER, 20, p1, FT_NONE);
    Entity * v2 = new Entity (ET_VILLAGER, 20, p2, FT_NONE);
    Entity * v3 = new Entity (ET_VILLAGER, 20, p3, FT_NONE);
    Entity * v4 = new Entity (ET_VILLAGER, 20, p4, FT_NONE);
    Entity * v5 = new Entity (ET_VILLAGER, 20, p5, FT_NONE);
    v1->setName("Villager one");
    v2->setName("Villager two");
    v3->setName("Villager three");
    v4->setName("Villager four");
    v5->setName("Villager five");
    
    taskManager->registerVillager(v1);
    taskManager->registerVillager(v2);
    taskManager->registerVillager(v3);
    taskManager->registerVillager(v4);
    taskManager->registerVillager(v5);
    
    assert(taskManager->getavailableVillagers().size() == 5);
    
    typedef std::vector<Entity *> entityVec;
    typedef entityVec ::iterator entityIter;
    
    typedef std::vector<TaskReference> taskVec;
    typedef taskVec::iterator taskIter;
    
    typedef std::priority_queue<TaskReference, taskVec, Comparator> taskQ;
    
    taskQ taskQueue = taskManager->getUnassignedTaskQueue();
    entityVec villagerVec = taskManager->getavailableVillagers();
    taskVec ipTaskVec = taskManager->getInProgressTaskList();
    

    //entityIter it = villagerVec.begin();
    //std::cout<<(*it)->getName()<<std::endl;
    
//    taskManager->assign();
//    
//    villagerVec = taskManager->getavailableVillagers();
//    ipTaskVec = taskManager->getInProgressTaskList();
//    
//    //assert(villagerVec.size() == 2);
//    //assert(taskManager.getUnassignedTaskList().size() == 11);
//    //assert(ipTaskVec.size() == 1);
//    //assert((*ipTaskVec.begin())->getPriority() == 7);
//    //assert((*ipTaskVec.begin())->getAssignee()->getName() == "Villager five");
//    
//    taskManager->assign();
//    taskManager->assign();
//    taskManager->assign();
//    taskManager->assign();
//    
//    villagerVec = taskManager->getavailableVillagers();
//    ipTaskVec = taskManager->getInProgressTaskList();
//    
//   // assert(villagerVec.size() == 1);
//    //assert(taskManager.getUnassignedTaskList().size() == 11);
//    assert(ipTaskVec.size() == 5);
//    
//    //assert((*ipTaskVec.begin())->getPriority() == 7);
//    
//    //assert((ipTaskVec.back())->getAssignee()->getName() == "Villager one");
//    
////Test Target Finding
//    
//    //mapTaskResource[TASK_GATHER_WOOD].push_back(w1);
//    
//    
////Test Gather Task Progress Tracking
//    std::cerr << "woodEntities " << woodEntities.size() << std::endl;
//    
//    int cnt = 0;
//    while (cnt < 20)
//    {
//        std::cerr << resourceManager.getResourceAmount(RS_WOOD, FT_PLAYER_1) << std::endl;
//        taskManager->updateProgress();
//        std::cerr << (*ipTaskVec.begin())->getTarget()->getName() << std::endl;
//        std::cerr << resourceManager.getResourceAmount(RS_WOOD, FT_PLAYER_1) << std::endl;
//        cnt ++;
//    }
//    std::cerr << "w2 " << w2->getCurrentHealth() << std::endl;
//
////Test Gather Task Cleansing & Villager Cleansing
//    
//    assert(taskManager->getInProgressTaskList().size() == 5);
//    assert(taskManager->getavailableVillagers().size() == 0);
//    
//    taskManager->cleanTaskList();
//    
//    assert(taskManager->getInProgressTaskList().size() == 5);
//    assert(taskManager->getavailableVillagers().size() == 0);
//
////Test Job Cleansing
//    
//    std::cerr << jobManager.getJobList().size() << std::endl;
//    jobManager.cleanJobList();
//    //assert(jobManager.getJobList().size() == 3);
//    jobManager.getFaction();
    

    

//Test Build Job
    //Create Job
    jobManager.createJobList(JOB_BUILD_SMELTING, 7, 100);
    
    //Assign Task
    assert(taskManager->getavailableVillagers().size() == 5);
    taskManager->assign();
//    taskManager->assign();
//    taskManager->assign();
//    taskManager->assign();
//    taskManager->assign();
    assert(taskManager->getavailableVillagers().size() == 0);
    
    //Get Task Target
    std::cerr << (*taskManager->getInProgressTaskList().begin())->getTarget()->getCurrentHealth() << std::endl;
    TaskVec tv = taskManager->getInProgressTaskList();
    for(TaskIter iter = tv.begin() ; iter != tv.end() ; ++iter)
    {
        std::cerr << (*iter)->getAssignee()->getPosition().x <<"xxxxx" << (*iter)->getTarget()->getPosition().x << std::endl;

        
        (*iter)->getAssignee()->setPosition((*iter)->getTarget()->getPosition());
    }
    int cnt = 0;
    while (cnt < 50)
    {
        taskManager->updateProgress();
        cnt++;
    }

    std::cerr << (*taskManager->getInProgressTaskList().begin())->getTarget()->getCurrentHealth() << std::endl;
    
    //Track Task Progress
    
    //Task Cleansing
        assert(taskManager->getInProgressTaskList().size() == 5);
        assert(taskManager->getavailableVillagers().size() == 0);
    
        taskManager->cleanTaskList();
    
        std::cerr << taskManager->getInProgressTaskList().size() << std::endl;
        std::cerr << taskManager->getavailableVillagers().size() << std::endl;
        //assert(taskManager->getInProgressTaskList().size() == 0);
        //assert(taskManager->getavailableVillagers().size() == 3);
    
    //Test Job Cleansing
    
        std::cerr << jobManager.getJobList().size() << std::endl;
        jobManager.cleanJobList();
        std::cerr << jobManager.getJobList().size() << std::endl;
        //assert(jobManager.getJobList().size() == 2);
        jobManager.getFaction();
    
    
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