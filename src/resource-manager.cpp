#include "resource-manager.h"
// Resource Manager with no pool
ResourceManager::ResourceManager()
{
	ptr_resourcePool = 0;
}

// Creates ResourceManager that uses passed ResourcePool
ResourceManager::ResourceManager(ResourcePool &resourcePool)
{
	if(ptr_resourcePool != &resourcePool)
		ptr_resourcePool = &resourcePool;
}

ResourceManager::~ResourceManager()
{
	ptr_resourcePool = 0;
}

// Registers a ResourcePool
void ResourceManager::registerResourcePool(ResourcePool &resourcePool)
{
	ptr_resourcePool = &resourcePool;
}

// Subtracts XXX amount of resources from the ResourcePool
// Returns true if successful, false if not
bool ResourceManager::requestResource(ResourceType type, int amount)
{
	if(ptr_resourcePool->resourcePool[type] >= amount)
	{
		ptr_resourcePool->resourcePool[type] -= amount;
		return true;
	}
	else
		return false;
}

// Adds XXX amount of resources back to the pool
void ResourceManager::sendResource(ResourceType type, int amount)
{
	ptr_resourcePool->resourcePool[type] += amount;
}

// Get XXX amount of resource
int ResourceManager::getResourceAmount(ResourceType type)
{
	return ptr_resourcePool->resourcePool[type];
}
