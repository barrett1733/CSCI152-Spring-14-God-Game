#include "stdafx.h"
#include "CppUnitTest.h"
#include "villager-ai.h"
#include "resource-manager.h"
#include "game-manager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestResourceManager)
		{
			ResourcePool rtest;
			VillagerAI test;
			rtest.resourcePool[RS_FOOD] = 100;
			test.registerResourcePool(rtest);
			Assert::AreEqual(rtest.resourcePool[RS_FOOD], test.getResourceAmount(RS_FOOD));
		}
	};
}