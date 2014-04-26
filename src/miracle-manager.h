/******************************
 * Miracles: An action or actions that are defined by the player.
 * Ex: Summon:Cow, AOE:Heal
 *
 */
 #include <map>
 #include "entity.h"
 #include "entity.cpp"

 struct Pair
 {
	std::string name;
	int cost;
 };

 // Entity class for miracle to enable manager to interact with entities
class MiracleEntity : public Entity
{
	//	static int AOE=0;
	//	virtual Action()=0;
};

typedef std::map<std::string, std::int> MiracleMap;
typedef std::pair<std::string, std::int> MiraclePair;

//miracle manager. go between for player and map
class MiracleManager : public Config
{
	MiracleMap miracleList;
	ResourceManager *resources;

	Miracle(std::string fileName,ResourceManager *);
	int getCost(std::string);
	int getET_Name(std::string);
	bool castMiracle(std::string, Callback input);
	void setResourceManager(ResourceManager *);
};
