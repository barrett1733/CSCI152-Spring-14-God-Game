//
//  File: resource-manager.cpp
//  Author: Steven Barrett
//  CSci 152
//  Spring 2014
//
//  Handles the resources for a village
//
#include "resource-manager.h"
// Resource Manager with no pool
// Subtracts XXX amount of resources from the ResourcePool
// Returns true if successful, false if not
bool ResourceManager::requestResource(ResourceType type, int amount)
{
	if(resourcePool.resourcePool[type] >= amount)
	{
		resourcePool.resourcePool[type] -= amount;
		return true;
	}
	else
		return false;
}

// Adds XXX amount of resources back to the pool
void ResourceManager::sendResource(ResourceType type, int amount)
{
	resourcePool.resourcePool[type] += amount;
}

// Get XXX amount of resource
int ResourceManager::getResourceAmount(ResourceType type)
{
	return resourcePool.resourcePool[type];
}
