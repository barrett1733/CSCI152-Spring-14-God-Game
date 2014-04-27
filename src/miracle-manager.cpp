#include "miracle-manager.h"

MiracleManager::MiracleManager(std::string file)
{
	load(file); // All we need is to load the config file.
}

int MiracleManager::getCost(EntityType et)
{
	return miracleList[et];
}

Entity* MiracleManager::createMiracle(EntityType et, Position p, Faction f)
{
	// Will make an entity based on incoming data.
	return (new Entity(et,100,p,f));
	// MAGIC - How much health does a Miracle Have?
	//				- Using default health of 100
}

////  Config Method
bool MiracleManager::setProperty(std::string property, int value)
{
	miracleList[string_to_ET(property)]=value;
	return(true);
}

EntityType string_to_ET(std::string name)
{
	if(property=="ET_MIRACLE_HEAL"){
		return(ET_MIRACLE_HEAL);
	}
	else if(property=="ET_MIRACLE_COW"){
		return(ET_MIRACLE_SUMMONCOW);
	}
	else if(property=="ET_MIRACLE_STATBOOST"){
		return(ET_MIRACLE_STATBOOST);
	}
	else if(property=="ET_MIRACLE_LIGTNING"){
		return(ET_MIRACLE_LIGTNING);
	}
	else if(property=="ET_MIRACLE_EARTHQUAKE"){
		return(ET_MIRACLE_EARTHQUAKE);
	}
	else if(property=="ET_MIRACLE_METEOR"){
		return(ET_MIRACLE_METEOR);
	}
	else{
		return(ET_MIRACLE);
	}
}