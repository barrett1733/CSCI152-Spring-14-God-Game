#include "resource-manager.h"
// Resource pools are created at ResourceManager creation
ResourceManager::ResourceManager()
{
	clearResourcePool();
	ptr_resourcePool = &resourcePool;
}
// Creates ResourceManager that uses passed ResourceManager resource pool
ResourceManager::ResourceManager(ResourceManager &resourceManager)
{
	clearResourcePool();
	if(resourcePool != resourceManager.resourcePool)
		ptr_resourcePool = resourceManager.ptr_resourcePool;
}

ResourceManager::~ResourceManager()
{
	clearResourcePool();
	ptr_resourcePool = 0;
}
void ResourceManager::clearResourcePool()
{
	for(int i=0; i<NUMBER_OF_RESOURCETYPES;i++)
		resourcePool[i] = 0;
}
// Switches to the resource pool of the passed ResourceManager
void ResourceManager::switchResourcePool(ResourceManager &resourceManager)
{
		ptr_resourcePool = resourceManager.ptr_resourcePool;
}
// If availible, subtract X amount of resource from the pool and return true
// Else return false
bool ResourceManager::requestResource(ResourceType type, int amount)
{
	if(*ptr_resourcePool[type] >= amount)
	{
		*ptr_resourcePool[type] -= amount;
		return true;
	}
	else
		return false;
}
// Adds amount of X resource back to the pool
void ResourceManager::sendResource(ResourceType type, int amount)
{
	*ptr_resourcePool[type] += amount;
}
// Returns amount of X resource
int ResourceManager::getResourceAmount(ResourceType type)
{
	return *ptr_resourcePool[type];
}
