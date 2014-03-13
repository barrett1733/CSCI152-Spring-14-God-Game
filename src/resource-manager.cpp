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
	// If the resource pool was a static member, then ALL instances of type ResourceManager
	// would have access to the exact same data.
	// We would not need to assign a pointer and we would not need to
	// clear the private resource pool.
	// For that matter, we would not need a copy constructor,
	// because any new instance of ResourceManager would automatically have access to the pool.
	// On the other hand, we need to be able to track the player resources separately from the
	// enemy CPU resources. So, maybe we shouldn't have a static resource pool.
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
	for(int i=0; i < RT_COUNT;i++)
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
