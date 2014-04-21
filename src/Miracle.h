/******************************
 * Miracles: An action or actions that are defined by the player.
 * Ex: Summon:Cow, AOE:Heal
 *
 * [Miracle] -> (Entity miracle,int cost)
 * [Somthing] -> (Entity miracle)-> [Miracle Manager |? resource.faith-miracle.cost >= 0 ] -> (Entity Miracle) -> [Entity Manager]
 * [Miracle Manager]
 * 	-Map:MiracleCost, EntityType // this is our unique id between entities
 * 	-ResourceManager* // who are we taking resources from
 * 	-EntityManager* // who are we sending a miracle to.
 *
 *
 */
 #include <map>
 #include "entity.h"
 #include "entity.cpp"
 
typedef std::map<EntityType, std::int> MiracleMap;

//miracle manager. go between for player and map
class MiracleManager:Config{
	// data
	MiracleMap miracleList;
	ResourceManager *resources;
	
	// methods
	MiracleManager(std::string fileName,ResourceManager *); // constructor
	int getCost(EntityType);
	EntityType getET_Name(std::string); // finds ET_Name based on string name?
	bool castMiracle(EntityType, Callback input); // casts/creates entity Miracle defined by string, at mouse location on call back?
	void setResourceManager(ResourceManager *); // sets resource manager to take from
	void populateEntityMap(std::string);
}

MiracleManager::MiracleManager(std::string fileName,ResourceManager* rm){
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
