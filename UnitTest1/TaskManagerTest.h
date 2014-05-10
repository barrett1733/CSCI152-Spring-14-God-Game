//
//  TaskManagerTest.h
//  GodGame_
//
//  Created by apple on 5/3/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#ifndef __GodGame___TaskManagerTest__
#define __GodGame___TaskManagerTest__

#include "task-manager.h"

TEST_CLASS( TaskManagerTest )
{

    TaskManager * taskManager;
    TaskReference gatherFoodTask = 0;
    TaskReference gatherWoodTask = 0;
    TaskReference gatherIronTask = 0;
    TaskReference gatherStoneTask = 0;
    TaskReference buildHouseTask = 0;
    TaskReference buildStoneworksTask = 0;
    TaskReference buildArmorsmithTask = 0;
    TaskReference buildWatchTowerTask = 0;
    TaskReference attackTask = 0;
    
    MobileEntityReference villager1 = 0;
    MobileEntityReference villager2 = 0;
    MobileEntityReference villager3 = 0;
    MobileEntityReference villager4 = 0;
    MobileEntityReference villager5 = 0;
    
    MobileEntityVec villagerList;
    
    
//  void assign();
//	void updateProgress();
//	void registerTask(TaskReference task);
//	void registerVillager(Entity * villager);
//  TaskGroup getTaskGroup(TaskType type);
//	void cleanTaskList();
public:
    TEST_METHOD( testRegisterTask );
	TEST_METHOD(testAssign);
	TEST_METHOD(testUpdateProgress);
	TEST_METHOD(testGetTaskGroup);
	TEST_METHOD(testCleanTaskList);
    
	TaskManagerTest();
	~TaskManagerTest();
       
};

#endif /* defined(__GodGame___TaskManagerTest__) */
