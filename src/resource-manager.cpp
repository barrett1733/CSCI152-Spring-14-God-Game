#include "resource-manager.h"
// Resource Manager with no pool
// Subtracts XXX amount of resources from the ResourcePool
// Returns true if successful, false if not
bool ResourceManager::requestResource(ResourceType type, int amount, Faction faction)
{
	if(resourcePool.resourcePool[faction][type] >= amount)
	{
		resourcePool.resourcePool[faction][type] -= amount;
		return true;
	}
	else
		return false;
}

// Adds XXX amount of resources back to the pool
void ResourceManager::sendResource(ResourceType type, int amount, Faction faction)
{
	resourcePool.resourcePool[faction][type] += amount;
}

// Get XXX amount of resource
int ResourceManager::getResourceAmount(ResourceType type, Faction faction)
{
	return resourcePool.resourcePool[faction][type];
}
