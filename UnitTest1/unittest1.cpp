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
			pool.resourcePool[0][RS_FOOD] = 100;
			manager.registerResourcePool(pool);
			Assert::AreEqual(pool.resourcePool[0][RS_FOOD], manager.getResourceAmount(RS_FOOD));
		}
	};
}