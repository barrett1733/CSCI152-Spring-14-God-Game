//
//  JobTest.cpp
//  GodGame_
//
//  Created by apple on 4/30/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#include "JobTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( JobTest );

void JobTest::setUp()
{
    JobType type = JOB_GATHER_RESOURCE;
    int priority = 7;
    ResourceCost cost = {10, 20, 30, 40};
    gatherJob = new GatherJob(type, priority, cost);
    
    priority = 7;
    Position psn(10, 20);
    //BuildJob(JobType type, int priority, Position psn);
    buildJob = new BuildJob(JOB_BUILD_LUMBERMILL, priority, psn);

}

void JobTest::tearDown()
{
    delete gatherJob;
    delete buildJob;
}

void JobTest::testGatherJobConstructor()
{
    //GatherJob(JobType type, int priority, ResourceCost);
    
    TaskVec taskList = gatherJob->getTaskList();
    int gatherWoodTaskCount = 0;
    int gatherFoodTaskCount = 0;
    int gatherStoneTaskCount = 0;
    int gatherIronTaskCount = 0;
    
    for(TaskIter iter = taskList.begin(); iter != taskList.end(); ++iter)
    {
        CPPUNIT_ASSERT((*iter)->getQuota() == 20);
        switch ((*iter)->getType()) {
            case TASK_GATHER_FOOD:
                gatherFoodTaskCount++;
                
                break;
            
            case TASK_GATHER_WOOD:
                gatherWoodTaskCount++;
                break;
            
            case TASK_GATHER_STONE:
                gatherStoneTaskCount++;
                break;
            
            case TASK_GATHER_IRON:
                gatherIronTaskCount++;
                break;
                
            default:
                break;
        }
    }
    
    CPPUNIT_ASSERT(taskList.size() == 6);
    CPPUNIT_ASSERT(gatherFoodTaskCount == 1);
    CPPUNIT_ASSERT(gatherWoodTaskCount == 1);
    CPPUNIT_ASSERT(gatherIronTaskCount == 2);
    CPPUNIT_ASSERT(gatherStoneTaskCount == 2);
}

void JobTest::testBuildJobConstructor()
{
    
    TaskVec taskList  = buildJob->getTaskList();
    CPPUNIT_ASSERT(  taskList.size() == 4 );
    for(TaskIter iter = taskList.begin(); iter != taskList.end(); ++iter)
    {
        CPPUNIT_ASSERT( (*iter)->getType() == TASK_BUILD_LUMBERMILL );
        CPPUNIT_ASSERT( (*iter)->getQuota() == 25 );
        delete (*iter);
    }
    
}

void JobTest::testMilitaryJobConstructor()
{
    
}

void JobTest::testCleanTaskList()
{
    TaskVec taskList  = gatherJob->getTaskList();
    for (TaskIter iter = taskList.begin(); iter != taskList.end(); ++iter)
    {
        (*iter)->setProgress( (*iter)->getQuota() );
    }
    
    gatherJob->cleanTaskList();
    taskList  = gatherJob->getTaskList();
    
    CPPUNIT_ASSERT( taskList.size() == 0 );
    CPPUNIT_ASSERT( gatherJob->isCompleted() );
}