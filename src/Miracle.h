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

typedef std::map<EntityType, std::int> MiracleMap;
typedef std::pair<EntityType, std::int> MiraclePair;

//miracle manager. go between for player and map
class MiracleManager:Config{
	MiracleMap miracleList;
	ResourceManager *resources;
	
	Miracle(std::string fileName,ResourceManager *); // constructor
	int getCost(EntityType);
	EntityType getET_Name(std::string); // finds ET_Name based on string name?
	bool castMiracle(EntityType, Callback input); // casts/creates entity Miracle defined by string, at mouse location on call back?
	void setResourceManager(ResourceManager *); // sets resource manager to take from
	void populateEntityMap(std::string);
}

MiracleManager::Miracle(std::string fileName,ResourceManager* rm){
	// constructor
	populateEntitiyMap(fileName);
	setResourceManager(rm);
}
int MiracleManager::getCost(EntityType miracle){
	return miracleList[miracle];
}
bool MiracleManager::castMiracle(EntityType miracle, Callback input){
	// casts/creates entity Miracle defined by string, at mouse location on call back?
	if(resources->requestResource(miracle,getCost(miracle))){
		// call the callback function?
	}
	
}
void MiracleManager::setResourceManager(ResourceManager *rm){
	// sets resource manager to take from
	this->resources=rm;
}
void MiracleManager::populateEntityMap(std::string fileName){}//fills MiracleMap with data from config file
