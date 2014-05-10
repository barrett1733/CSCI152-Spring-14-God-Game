#pragma once

#include "resource-manager.h"
#include "game-manager.h"

TEST_CLASS( ResourceManagerTest)
{
	ResourcePool pool;
	ResourceManager manager;
public:
	TEST_METHOD(testSendResource);
	TEST_METHOD(testRecieveResource);
};

