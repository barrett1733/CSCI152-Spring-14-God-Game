//
//  JobTest.h
//  GodGame_
//
//  Created by apple on 4/30/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#ifndef __GodGame___JobTest__
#define __GodGame___JobTest__

#include <iostream>

#include<cppunit/extensions/HelperMacros.h>
#include"job.h"

class JobTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( JobTest );
    CPPUNIT_TEST( testGatherJobConstructor );
    CPPUNIT_TEST( testBuildJobConstructor );
    CPPUNIT_TEST( testMilitaryJobConstructor );
    CPPUNIT_TEST( testCleanTaskList );
    CPPUNIT_TEST_SUITE_END();
    
    JobReference gatherJob;
    JobReference buildJob;
    JobReference militaryJob;
    
public:
    void setUp();
    void tearDown();
    
    void testGatherJobConstructor();
    void testBuildJobConstructor();
    void testMilitaryJobConstructor();
    void testCleanTaskList();
};

#endif /* defined(__GodGame___JobTest__) */
