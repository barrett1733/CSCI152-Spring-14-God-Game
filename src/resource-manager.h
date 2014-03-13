#define RESOURCE_TYPE_MAX 4

enum ResourceType
{
	RS_FAITH = 0x00,
	RS_WOOD,
	RS_FOOD,
	RS_STONE,
	RS_IRON
	
	// Making the count part of the enum allows you
	// to add or remove enumerations without having to make two updates
	// (one to add the enumerations and one to update the count).
	// This only works if your enum's int values start at zero
	// and are automatically incremented (as is the case here).
	// I.e., move NUM_RESOURCETYPE from below as a define, to here:
	//NUM_RESOURCETYPES
};

#define NUM_RESOURCETYPES 5

class ResourceManager
{
private:
	int resourcePool[NUM_RESOURCETYPES];
	int (*ptr_resourcePool)[NUM_RESOURCETYPES];
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
