//
//  JobManagerTest.h
//  GodGame_
//
//  Created by apple on 5/3/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#ifndef __GodGame___JobManagerTest__
#define __GodGame___JobManagerTest__


#include "job-manager.h"

TEST_CLASS(JobManagerTest)
{
    JobManager * jobManager;

public:
	TEST_METHOD( testCreateJob );
	TEST_METHOD(testGetJobGroup);
	TEST_METHOD(testCleanJobList);
        
	JobManagerTest();
	~JobManagerTest();

        
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
    
};


#endif /* defined(__GodGame___JobManagerTest__) */
