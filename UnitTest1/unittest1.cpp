#include "stdafx.h"
#include "CppUnitTest.h"
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
			ResourcePool pool;
			ResourceManager manager;
			pool.resourcePool[F_PLAYER_1][RS_FOOD] = 100;
			manager.sendResource(RS_FOOD, 100, F_PLAYER_1);
			Assert::AreEqual(pool.resourcePool[0][RS_FOOD], manager.getResourceAmount(RS_FOOD,F_PLAYER_1));
		}
	};
}