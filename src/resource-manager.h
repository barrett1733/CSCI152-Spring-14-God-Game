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

class ResourceManager
{
private:
	// From looking at the implementation, it looks like the resourcePool
	// should be static. This would also eliminate the need for a pointer.
	// See additional comments in the implmentation file.
	int resourcePool[RT_COUNT];
	int (*ptr_resourcePool)[RT_COUNT];
	void clearResourcePool();
public:
	ResourceManager();
	ResourceManager(ResourceManager&);
	~ResourceManager();
	void switchResourcePool(ResourceManager&);
	bool requestResource(ResourceType,int);
	void sendResource(ResourceType,int);
	int getResourceAmount(ResourceType);
};


#endif
