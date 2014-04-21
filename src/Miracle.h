/******************************
 * Miracles: An action or actions that are defined by the player.
 * Ex: Summon:Cow, AOE:Heal
 *
 * Miracle Manager
 *		Takes input data and returns an Entity:Miracle
 */
 #include <map>
 #include <string>
 #include "entity.h"
 #include "entity.cpp"
 #include "config.cpp"
 
 
typedef std::map<EntityType, std::int> MiracleMap;

//miracle manager. go between for player and map
class MiracleManager:config{
	// data
private:
	MiracleMap miracleList;
	bool setProperty(std::string property, int value);
	
public:
	MiracleManager(std::string file); // constructor
	int getCost(EntityType e);
	Entity* createMiracle(EntityType, Position);
}

MiracleManager::MiracleManager(std::string file){
	// All we need is to load the config file.
	load(file);
}
int MiracleManager::getCost(EntityType e){return miracleList[e];}
Entity* MiracleManager::createMiracle(EntityType et, Position p, Faction f){
	// Will make an entity based on incoming data.
	return (new Entity(et,100,p,f));
}

////  Config Method
bool MiracleManager::setProperty(std::string property, int value){
	miracleList[property]=value;
}


