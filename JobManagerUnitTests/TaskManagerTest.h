//
//  TaskManagerTest.h
//  GodGame_
//
//  Created by apple on 5/3/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#ifndef __GodGame___TaskManagerTest__
#define __GodGame___TaskManagerTest__

#include <iostream>

#include<cppunit/extensions/HelperMacros.h>
#include"task-manager.h"

class TaskManagerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( TaskManagerTest );
    CPPUNIT_TEST( testRegisterTask );
    CPPUNIT_TEST( testAssign );
    CPPUNIT_TEST( testUpdateProgress );
    CPPUNIT_TEST( testGetTaskGroup );
    CPPUNIT_TEST( testCleanTaskList );
    CPPUNIT_TEST_SUITE_END();
    
    TaskManager * taskManager;
    TaskReference gatherFoodTask = nullptr;
    TaskReference gatherWoodTask = nullptr;
    TaskReference gatherIronTask = nullptr;
    TaskReference gatherStoneTask = nullptr;
    TaskReference buildHouseTask = nullptr;
    TaskReference buildStoneworksTask = nullptr;
    TaskReference buildArmorsmithTask = nullptr;
    TaskReference buildWatchTowerTask = nullptr;
    TaskReference attackTask = nullptr;
    
    MobileEntityReference villager1 = nullptr;
    MobileEntityReference villager2 = nullptr;
    MobileEntityReference villager3 = nullptr;
    MobileEntityReference villager4 = nullptr;
    MobileEntityReference villager5 = nullptr;
    
    MobileEntityVec villagerList;
    
public:
    void setUp();
    void tearDown();
    
//  void assign();
//	void updateProgress();
//	void registerTask(TaskReference task);
//	void registerVillager(Entity * villager);
//  TaskGroup getTaskGroup(TaskType type);
//	void cleanTaskList();
    
    void testRegisterTask();
    void testAssign();
    void testUpdateProgress();
    void testGetTaskGroup();
    void testCleanTaskList();
    
};

#endif /* defined(__GodGame___TaskManagerTest__) */
