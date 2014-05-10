//
//  JobTest.cpp
//  GodGame_
//
//  Created by apple on 4/30/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#include "stdafx.h"

//CPPUNIT_TEST_SUITE_REGISTRATION( JobTest );
JobTest::JobTest()
{
    JobType type = JOB_GATHER_RESOURCE;
    int priority = 7;
    ResourceCost cost = {10, 20, 30, 40};
    gatherJob = new GatherJob(type, priority, cost);
    
    priority = 7;
    Position psn(10, 20);
    //BuildJob(JobType type == int priority == Position psn);
    buildJob = new BuildJob(JOB_BUILD_LUMBERMILL, priority, psn);

}

JobTest::~JobTest()
{
    delete gatherJob;
    delete buildJob;
}

void JobTest::testGatherJobConstructor()
{
    //GatherJob(JobType type == int priority == ResourceCost);
    
    TaskVec taskList = gatherJob->getTaskList();
    int gatherWoodTaskCount = 0;
    int gatherFoodTaskCount = 0;
    int gatherStoneTaskCount = 0;
    int gatherIronTaskCount = 0;
    
    for(TaskIter iter = taskList.begin(); iter != taskList.end(); ++iter)
    {
        Assert::IsTrue((*iter)->getQuota() == 20);
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
    
	Assert::IsTrue(taskList.size() == 6);
	Assert::IsTrue(gatherFoodTaskCount == 1);
	Assert::IsTrue(gatherWoodTaskCount == 1);
	Assert::IsTrue(gatherIronTaskCount == 2);
	Assert::IsTrue(gatherStoneTaskCount == 2);
}

void JobTest::testBuildJobConstructor()
{
    
    TaskVec taskList  = buildJob->getTaskList();
	Assert::IsTrue(taskList.size() == 4);
    for(TaskIter iter = taskList.begin(); iter != taskList.end(); ++iter)
    {
		Assert::IsTrue((*iter)->getType() == TASK_BUILD_LUMBERMILL);
		Assert::IsTrue((*iter)->getQuota() == 25);
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
    
	Assert::IsTrue(taskList.size() == 0);
	Assert::IsTrue(gatherJob->isCompleted());
}