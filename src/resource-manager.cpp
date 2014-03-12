#include "resource-manager.h"

ResourceManager::ResourceManager()
{
	resourcePool = new std::vector<int>;
	resourcePool->resize(20);
	resourcePoolDeleted = false;
}

ResourceManager::~ResourceManager()
{
	if(!resourcePoolDeleted)
		delete resourcePool;
	resourcePool = NULL;
	resourcePoolDeleted = 1;
}
void ResourceManager::registerResourcePool(ResourceManager &resourceManager)
{
	if(resourcePool != resourceManager.resourcePool)
	{
		delete resourcePool;
		resourcePool = resourceManager.resourcePool;
		resourcePoolDeleted = resourceManager.resourcePoolDeleted;
	}
}
// If availible, subtracts X amount of resource from the pool and returns true
// Else return false
bool ResourceManager::requestResource(ResourceType type, int amount)
{
	if(resourcePool->at(type) >= amount)
	{
		resourcePool->at(type) -= amount;
		return true;
	}
	else
		return false;
}
// Adds amount of X resource back to the pool
void ResourceManager::sendResource(ResourceType type, int amount)
{
	resourcePool->at(type) += amount;
}
// Returns amount of X resource
int ResourceManager::getResourceAmount(ResourceType type)
{
	return resourcePool->at(type);
}
