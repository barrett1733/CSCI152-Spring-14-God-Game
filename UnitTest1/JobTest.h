//
//  JobTest.h
//  GodGame_
//
//  Created by apple on 4/30/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#ifndef __GodGame___JobTest__
#define __GodGame___JobTest__

#include "job.h"

TEST_CLASS(JobTest)
{

	JobReference gatherJob;
	JobReference buildJob;
	JobReference militaryJob;
public:
	JobTest();
	~JobTest();
	TEST_METHOD(testGatherJobConstructor);
	TEST_METHOD(testBuildJobConstructor);
	TEST_METHOD(testMilitaryJobConstructor);
	TEST_METHOD(testCleanTaskList);

};



#endif /* defined(__GodGame___JobTest__) */
