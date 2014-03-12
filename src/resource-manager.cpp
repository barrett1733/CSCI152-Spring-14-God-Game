
#include <map>

enum ResourceType
{
	TRI_MILITARY = 0x00,
	TRI_CONSTRUCT,
	TRI_GATHER,
	TRI_WORSHIP,
	RES_FAITH,
	RES_WOOD,
	RES_FOOD,
	RES_STONE,
	RES_IRON
};

class ResourceManager
{
private:
	struct ResourceRequest
	{
		ResourceType type;
		int amount;
	};
	int resourceAmount[20];
	std::map<int,ResourceRequest> requestedList;
	int getRequestedSum(ResourceType);
public:
	ResourceManager();
	~ResourceManager();
	void getTriangleData();
	bool requestResource(ResourceType,int);
	bool requestResource(ResourceType,int,int);
	int getResourceAmount(ResourceType);
	bool removeRequest(int);
};

ResourceManager::ResourceManager()
{
	for(int i=0; i<20; i++)
		resourceAmount[i] = 0;
}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::getTriangleData()
{

}
// Basic request resource
// Allocates and returns true if enough resources are availible
bool ResourceManager::requestResource(ResourceType type, int amount)
{
	if(resourceAmount[type] >= amount)
	{
		resourceAmount[type] -= amount;
		return true;
	}
	else
		return false;
}
// Advanced resource request
// # Not implimented
bool ResourceManager::requestResource(ResourceType type, int amount, int id)
{
	if(getRequestedSum(type) - amount >= 0 && requestedList.count(id) == 0)
	{
		ResourceRequest temp = {type,amount};
		requestedList[id] = temp;
		return true;
	}
	return false;
}

int ResourceManager::getResourceAmount(ResourceType type)
{
	return resourceAmount[type];
}
// Returns sums of all requests made of a resource
int ResourceManager::getRequestedSum(ResourceType type)
{
	int tempTotal = 0;
	if(requestedList.size() > 0)
	{
		for (auto iter = requestedList.cbegin(); iter != requestedList.cend(); ++iter)
			if(type == iter->second.type)
				tempTotal += iter->second.amount;
		return tempTotal;
	}
	return 0;
}



