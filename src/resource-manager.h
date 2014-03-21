#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

enum ResourceType
{
	RS_FAITH = 0x00,
	RS_WOOD,
	RS_FOOD,
	RS_STONE,
	RS_IRON,

	// Making the count part of the enum allows you
	// to add or remove enumerations without having to make two updates
	// (one to add the enumerations and one to update the count).
	// This only works if your enum's int values start at zero
	// and are automatically incremented (as is the case here).
	// I.e., move NUM_RESOURCETYPE from below as a define, to here:
	RT_COUNT
};
struct ResourcePool
{
	int resourcePool[RT_COUNT];
	ResourcePool()
	{
		for(int i = 0; i < RT_COUNT; i++)
			resourcePool[i] = 0;
	}
	~ResourcePool()
	{
		for(int i = 0; i < RT_COUNT; i++)
			resourcePool[i] = 0;
	}
};

class ResourceManager
{
private:
	ResourcePool *ptr_resourcePool;
public:
	ResourceManager();
	ResourceManager(ResourcePool&);
	~ResourceManager();
	void registerResourcePool(ResourcePool&);
	bool requestResource(ResourceType,int);
	void sendResource(ResourceType,int);
	int getResourceAmount(ResourceType);
};


#endif
