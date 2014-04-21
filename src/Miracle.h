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
class MiracleManager:config{ // config not in this branch yet.
	// data
	MiracleMap miracleList;
	
	ResourceManager *resources; // don't have either of these.
	EntityManager *entities;
	
	//// Methods
	// set up
	MiracleManager(std::string fileName,ResourceManager *,EntityManager*); // constructor
	void setResourceManager(ResourceManager *); // sets resource manager to take from
	void setEntityManager(EntityManager*); // ditto on entity manager to send to
	
	bool castMiracle(Entity*); // adds Entity to EntityManager if resource manager has enough faith
	
	// Inherited methods from config
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
