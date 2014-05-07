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
