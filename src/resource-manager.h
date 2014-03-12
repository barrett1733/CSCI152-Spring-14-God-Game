#include <vector>

enum ResourceType
{
	RS_FAITH = 0x00,
	RS_WOOD,
	RS_FOOD,
	RS_STONE,
	RS_IRON
};

class ResourceManager
{
private:
	struct
	{
	std::vector<int>* resourcePool;
	int* resourcePoolDeleted;
	};
public:
	ResourceManager();
	~ResourceManager();
	void registerResourcePool(ResourceManager&);
	void deleteResourcePool();
	bool requestResource(ResourceType,int);
	void sendResource(ResourceType,int);
	int getResourceAmount(ResourceType);
};