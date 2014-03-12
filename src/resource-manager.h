
enum ResourceType
{
	RS_FAITH = 0x00,
	RS_WOOD,
	RS_FOOD,
	RS_STONE,
	RS_IRON
};

#define NUM_RESOURCETYPES 20

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