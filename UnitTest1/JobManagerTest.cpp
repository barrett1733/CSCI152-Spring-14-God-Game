//
//  JobManagerTest.cpp
//  GodGame_
//
//  Created by apple on 5/3/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#include "stdafx.h"


JobManagerTest::JobManagerTest()
{
    jobManager = new JobManager();
    
    Position psn1(10, 20);
    
    ResourceCost cost = { 10, 20, 30, 40 };

    jobManager->createJob( JOB_BUILD_STONEWORKS, 7, psn1 );
    jobManager->createJob( JOB_GATHER_RESOURCE, 7, cost );
    
}

JobManagerTest::~JobManagerTest()
{
    delete jobManager;
}

void JobManagerTest::testCreateJob()
{
    
	Assert::IsTrue(jobManager->getJobList().size() == 2);
	Assert::IsTrue(jobManager->getTaskManager()->getUnassignedTaskQueue().size() == 8);
    
}

void JobManagerTest::testGetJobGroup()
{
    
	Assert::IsTrue(jobManager->getJobGroup(JOB_GATHER_RESOURCE) == JG_GATHER);
	Assert::IsTrue(jobManager->getJobGroup(JOB_BUILD_HOUSE) == JG_BUILD);
	Assert::IsTrue(jobManager->getJobGroup(JOB_BUILD_STONEWORKS) == JG_BUILD);
	Assert::IsTrue(jobManager->getJobGroup(JOB_BUILD_ARMORSMITH) == JG_BUILD);
	Assert::IsTrue(jobManager->getJobGroup(JOB_BUILD_WATCHTOWER) == JG_BUILD);
	Assert::IsTrue(jobManager->getJobGroup(JOB_ATTACK) == JG_MILITARY);
    
}

void JobManagerTest::testCleanJobList()
{
    TaskManager * taskManager = jobManager->getTaskManager();
    TaskQueue que = taskManager->getUnassignedTaskQueue();
    TaskVec inProgressList = taskManager->getInProgressTaskList();
    while(!que.empty())
    {
        inProgressList.push_back(que.top());
        
        que.pop();
        
    }
    
    for (TaskIter iter = inProgressList.begin(); iter != inProgressList.end(); ++ iter)
    {
        (*iter)->setProgress((*iter)->getQuota());
    }
    jobManager->cleanJobList();
    
	Assert::IsTrue(jobManager->getJobList().size() == 0);
}