//
//  TaskManagerTest.cpp
//  GodGame_
//
//  Created by apple on 5/3/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#include "stdafx.h"


////Constructor for Gather Task
//Task(TaskType type, int priority, int);
////Constructor for Build Task
//Task(TaskType type, int priority, Position, int);
////Constructor for Military Task
//Task(TaskType type, int priority, Entity *, int);

TaskManagerTest::TaskManagerTest()
{
    taskManager = new TaskManager();
    
    Position psn1(10, 20);
    Position psn2(20, 30);
    Position psn3(20, 20);
    Position psn4(20, 10);
    Position psn5(15, 15);
    Position psn6(15, 17);
    Position psn7(16, 17);
    Position psn8(17, 17);
    Position psn9(18, 18);

    gatherFoodTask = new Task(TASK_GATHER_FOOD, 3, 20);
    gatherWoodTask = new Task(TASK_GATHER_WOOD, 3, 20);
    gatherIronTask = new Task(TASK_GATHER_IRON, 3, 20);
    gatherStoneTask = new Task(TASK_GATHER_STONE, 3, 20);
    
    buildHouseTask = new Task(TASK_BUILD_HOUSE, 7, psn1, 20);
    buildWatchTowerTask = new Task(TASK_BUILD_WATCHTOWER, 7, psn2, 20);
    buildArmorsmithTask = new Task(TASK_BUILD_ARMORSMITH, 7, psn3, 20);
    buildStoneworksTask = new Task(TASK_BUILD_STONEWORKS, 7, psn4, 20);
    
    //militaryTask = new Task(TASK_ATTACK, 10, );
    
    
    //Entity(EntityType, int health, Position, Faction);
    villager1 = new MobileEntity(Entity(ET_VILLAGER, 20, psn5, F_PLAYER_1));
    villager2 = new MobileEntity(Entity(ET_VILLAGER, 20, psn6, F_PLAYER_1));
    villager3 = new MobileEntity(Entity(ET_VILLAGER, 20, psn7, F_PLAYER_1));
    villager4 = new MobileEntity(Entity(ET_VILLAGER, 20, psn8, F_PLAYER_1));
    villager5 = new MobileEntity(Entity(ET_VILLAGER, 20, psn9, F_PLAYER_1));
    
    villager1->setName("V1");
    villager2->setName("V2");
    villager3->setName("V3");
    villager4->setName("V4");
    villager5->setName("V5");
    
    taskManager->registerTask( gatherFoodTask );
    taskManager->registerTask( gatherWoodTask );
    taskManager->registerTask( gatherIronTask );
    taskManager->registerTask( gatherStoneTask );
    taskManager->registerTask( buildWatchTowerTask );
    taskManager->registerTask( buildHouseTask );
    taskManager->registerTask( buildStoneworksTask );
    taskManager->registerTask( buildArmorsmithTask );
    
    villagerList.push_back(villager1);
    villagerList.push_back(villager2);
    villagerList.push_back(villager3);
    villagerList.push_back(villager4);
    villagerList.push_back(villager5);
    
}

TaskManagerTest::~TaskManagerTest()
{
    
    delete gatherFoodTask;
    delete gatherWoodTask;
    delete gatherIronTask;
    delete gatherStoneTask;
    
    delete buildHouseTask;
    delete buildArmorsmithTask;
    delete buildStoneworksTask;
    delete buildWatchTowerTask;
    
    delete villager1;
    delete villager2;
    delete villager3;
    delete villager4;
    delete villager5;
    
    delete taskManager;
    
}

void TaskManagerTest::testRegisterTask()
{
    Assert::IsTrue( taskManager->getUnassignedTaskQueue().size() == 8 );
	Assert::IsTrue(taskManager->getUnassignedTaskQueue().top()->getType() >= TASK_BUILD_HOUSE);
}

void TaskManagerTest::testAssign()
{
    //taskManager->assign(villagerList);
	Assert::IsTrue(villagerList.size() == 0);
	Assert::IsTrue(taskManager->getInProgressTaskList().size() == 5);
    
	Assert::IsTrue(taskManager->getInProgressTaskList()[0]->getType() >= TASK_BUILD_HOUSE);
	Assert::IsTrue(taskManager->getInProgressTaskList()[0]->getAssignee()->getName() == "V5");

	Assert::IsTrue(taskManager->getInProgressTaskList()[4]->getType() < TASK_BUILD_HOUSE);
	Assert::IsTrue(taskManager->getInProgressTaskList()[4]->getAssignee()->getName() == "V1");
}

void TaskManagerTest::testUpdateProgress()
{
    //taskManager->assign(villagerList);
    
    //villager1->setPosition( taskManager->getInProgressTaskList()[4]->getPosition() );
    villager2->setPosition( taskManager->getInProgressTaskList()[3]->getPosition() );
    villager3->setPosition( taskManager->getInProgressTaskList()[2]->getPosition() );
    villager4->setPosition( taskManager->getInProgressTaskList()[1]->getPosition() );
    villager5->setPosition( taskManager->getInProgressTaskList()[0]->getPosition() );
    
    //taskManager->updateProgress();
    
	Assert::IsTrue(taskManager->getInProgressTaskList()[0]->getProgress() == 1);
	Assert::IsTrue(taskManager->getInProgressTaskList()[1]->getProgress() == 1);
	Assert::IsTrue(taskManager->getInProgressTaskList()[2]->getProgress() == 1);
	Assert::IsTrue(taskManager->getInProgressTaskList()[3]->getProgress() == 1);
//    Assert::IsTrue( taskManager->getInProgressTaskList()[4]->getProgress() == 1 );
    
}

void TaskManagerTest::testGetTaskGroup()
{
    Assert::IsTrue( taskManager->getTaskGroup( TASK_GATHER_FOOD ) == TG_GATHER );
    Assert::IsTrue( taskManager->getTaskGroup( TASK_GATHER_WOOD ) == TG_GATHER );
    Assert::IsTrue( taskManager->getTaskGroup( TASK_GATHER_STONE ) == TG_GATHER );
    Assert::IsTrue( taskManager->getTaskGroup( TASK_GATHER_IRON ) == TG_GATHER );
    Assert::IsTrue( taskManager->getTaskGroup( TASK_BUILD_HOUSE ) == TG_BUILD );
    Assert::IsTrue( taskManager->getTaskGroup( TASK_BUILD_STONEWORKS ) == TG_BUILD );
    Assert::IsTrue( taskManager->getTaskGroup( TASK_BUILD_ARMORSMITH ) == TG_BUILD );
    Assert::IsTrue( taskManager->getTaskGroup( TASK_BUILD_WATCHTOWER ) == TG_BUILD );
    Assert::IsTrue( taskManager->getTaskGroup( TASK_ATTACK ) == TG_MILITARY );
}

void TaskManagerTest::testCleanTaskList()
{
    //taskManager->assign(villagerList);
    
    //villager1->setPosition( taskManager->getInProgressTaskList()[4]->getPosition() );
    villager2->setPosition( taskManager->getInProgressTaskList()[3]->getPosition() );
    villager3->setPosition( taskManager->getInProgressTaskList()[2]->getPosition() );
    villager4->setPosition( taskManager->getInProgressTaskList()[1]->getPosition() );
    villager5->setPosition( taskManager->getInProgressTaskList()[0]->getPosition() );
    
    for (int i = 0; i < 20; i++)
    {
        taskManager->updateProgress();
    }
    
    taskManager->cleanTaskList(villagerList);
    
    Assert::IsTrue( villagerList.size() == 4 );
    Assert::IsTrue( taskManager->getInProgressTaskList().size() == 1 );
}