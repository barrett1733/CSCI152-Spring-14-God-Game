#include "miracle-manager.h"

MiracleManager::MiracleManager(std::string file)
{
	load(file); // All we need is to load the config file.
}

int MiracleManager::getCost(EntityType et)
{
	return miracleList[et];
}

Entity* MiracleManager::createMiracle(EntityType et, Position p, Faction f){
	// Will make an entity based on incoming data.
	return (new Entity(et,100,p,f));
	// MAGIC - How much health does a Miracle Have?
	//				- Using default health of 100
}

////  Config Method
bool MiracleManager::setProperty(std::string property, int value){
	//miracleList[property]=value;
	// ERROR - property is a string, this needs to be an entity type.
	//				- How in the world do I convert from string to ET?
	
	return(false);
	// MAGIC - Nothing happening. fix error above and remove this.
} 