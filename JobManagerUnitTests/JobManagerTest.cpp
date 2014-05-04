//
//  JobManagerTest.cpp
//  GodGame_
//
//  Created by apple on 5/3/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#include "JobManagerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( JobManagerTest );

void JobManagerTest::setUp()
{
    jobManager = new JobManager();
    
    Position psn1(10, 20);
    
    ResourceCost cost = { 10, 20, 30, 40 };

    jobManager->createJob( JOB_BUILD_STONEWORKS, 7, psn1 );
    jobManager->createJob( JOB_GATHER_RESOURCE, 7, cost );
    
}

void JobManagerTest::tearDown()
{
    delete jobManager;
}

void JobManagerTest::testCreateJob()
{
    
    CPPUNIT_ASSERT( jobManager->getJobList().size() == 2 );
    CPPUNIT_ASSERT( jobManager->getTaskManager()->getUnassignedTaskQueue().size() == 8 );
    
}

void JobManagerTest::testGetJobGroup()
{
    
    CPPUNIT_ASSERT( jobManager->getJobGroup( JOB_GATHER_RESOURCE ) == JG_GATHER );
    CPPUNIT_ASSERT( jobManager->getJobGroup( JOB_BUILD_HOUSE ) == JG_BUILD );
    CPPUNIT_ASSERT( jobManager->getJobGroup( JOB_BUILD_STONEWORKS ) == JG_BUILD );
    CPPUNIT_ASSERT( jobManager->getJobGroup( JOB_BUILD_ARMORSMITH ) == JG_BUILD );
    CPPUNIT_ASSERT( jobManager->getJobGroup( JOB_BUILD_WATCHTOWER ) == JG_BUILD );
    CPPUNIT_ASSERT( jobManager->getJobGroup( JOB_ATTACK ) == JG_MILITARY );
    
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
    
    CPPUNIT_ASSERT( jobManager->getJobList().size() == 0 );
}