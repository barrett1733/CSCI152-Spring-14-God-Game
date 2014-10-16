//
//  File: resource-manager.h
//  Author: Steven Barrett
//  CSci 152
//  Spring 2014
//
//  Handles the resources for a village
//
#include "entity.h"

#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

enum ResourceType
{
	RS_FAITH = 0x00,
	RS_WOOD,
	RS_FOOD,
	RS_STONE,
	RS_IRON,
	RT_COUNT
};
struct ResourcePool
{
	int resourcePool[RT_COUNT];
	ResourcePool()
	{
			for(int j = 0; j < RT_COUNT; j++)
				resourcePool[j] = 0;
	}
};

class ResourceManager
{
private:
	ResourcePool resourcePool;
public:
	bool requestResource(ResourceType,int);
	void sendResource(ResourceType,int);
	int getResourceAmount(ResourceType);
};


#endif
