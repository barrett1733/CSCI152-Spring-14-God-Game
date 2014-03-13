
#define RESOURCE_TYPE_MAX 4

enum ResourceType
{
	RS_FAITH = 0x00,
	RS_WOOD,
	RS_FOOD,
	RS_STONE,
	RS_IRON
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