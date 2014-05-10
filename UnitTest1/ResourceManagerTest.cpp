#include "stdafx.h"
#include "ResourceManagerTest.h"



void ResourceManagerTest::testSendResource()
{
	manager.sendResource(RS_FOOD, 100, F_PLAYER_1);
	Assert::AreEqual(100, manager.getResourceAmount(RS_FOOD, F_PLAYER_1));
}
void ResourceManagerTest::testRecieveResource()
{
	pool.resourcePool[F_PLAYER_1][RS_FOOD] = 100;
	bool tempResources = manager.requestResource(RS_FOOD, 100, F_PLAYER_1);
	Assert::AreEqual(pool.resourcePool[F_PLAYER_1][RS_FOOD], 100);
	Assert::IsTrue(tempResources);
	tempResources = manager.requestResource(RS_FOOD, 100, F_PLAYER_1);
	Assert::IsFalse(tempResources);
}
