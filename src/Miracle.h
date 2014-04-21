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
 #include <string>
 #include "entity.h"
 #include "entity.cpp"
 #include "entity-manager.cpp"
 #include "config.cpp"
 
 
typedef std::map<EntityType, std::int> MiracleMap;

//miracle manager. go between for player and map
class MiracleManager:config{
	// data
private:
	MiracleMap miracleList;
	
	ResourceManager *resources;
	EntityManager *entities;
	
	//// Methods
	// set up
	MiracleManager(std::string file){load(file);} // constructor
	
	int getCost(EntityType e){return miracleList[e];}
	Entity* castMiracle(EntityType, Position); // adds Entity to EntityManager if resource manager has enough faith
	
	// Inherited methods from config
	// void load(string file); 
	bool setProperty(std::string property, int value);
}

////  Config Method
bool MiracleManager::setProperty(std::string property, int value){
	miracleList[property]=value;
}


