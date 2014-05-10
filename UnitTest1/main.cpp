//
//  main.cpp
//  GodGame_
//
//  Created by apple on 4/30/14.
//  Copyright (c) 2014 apple. All rights reserved.
//

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


int main(int argc, char* argv[])
{
    // Get the top level suite from the registry
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    
    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( suite );
    
    // Change the default outputter to a compiler error format outputter
    runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                        std::cerr ) );
    // Run the tests.
    bool wasSucessful = runner.run();
    
    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}