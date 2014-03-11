/******************************
 * Miracles: An action or actions that are defined by the player.
 * Ex: Summon:Cow, AOE:Heal
 *
 */
 #include <map>
 #include "entity.h"
 #include "entity.cpp"
 
 struct Pair{
	std::string name;
	int cost;
 }

typedef std::map<std::int, std::int> MiracleMap;
typedef std::pair<std::int, std::int> MiraclePair;

//miracle manager. go between for player and map
class MiracleManager:Config{
	MiracleMap miracleList;
	ResourceManager *resources;
	
	Miracle(std::string fileName,ResourceManager *); // constructor
	int getCost(std::string);
	EntityType getET_Name(std::string); // finds ET_Name based on string name?
	bool castMiracle(std::string, Callback input); // casts/creates entity Miracle defined by string, at mouse location on call back?
	void setResourceManager(ResourceManager *); // sets resource manager to take from
}