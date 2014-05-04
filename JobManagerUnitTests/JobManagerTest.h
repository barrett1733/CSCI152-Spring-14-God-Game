//
//  JobManagerTest.h
//  GodGame_
//
//  Created by apple on 5/3/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#ifndef __GodGame___JobManagerTest__
#define __GodGame___JobManagerTest__

#include <iostream>
#include<cppunit/extensions/HelperMacros.h>
#include"job-manager.h"

class JobManagerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( JobManagerTest );

    CPPUNIT_TEST( testCreateJob );
    CPPUNIT_TEST( testGetJobGroup );
    CPPUNIT_TEST( testCleanJobList );
    
    CPPUNIT_TEST_SUITE_END();
    
    JobManager * jobManager;
    
public:
    void setUp();
    void tearDown();
    
//	void registerJob(JobReference job);
//
//  void createJob(JobType, int priority, ResourceCost);
//	void createJob(JobType, int priority, Position psn);
//    
//  JobGroup getJobGroup(JobType type);
//
//	void cleanTaskList(JobReference job);
//    
//	void cleanJobList();

    
    void testCreateJob();
    void testGetJobGroup();
    void testCleanJobList();
    
};


#endif /* defined(__GodGame___JobManagerTest__) */
