#include "miracle-manager.h"
#include "miracle-entity.cpp"

MiracleManager::MiracleManager(std::string file)
{
	 // All we need is to load the config file.
	load(file);
}

int MiracleManager::getCost(EntityType et)
{
	return miracleList[et];
}

Entity* MiracleManager::createMiracle(EntityType et, Position p, Faction f)
{
	// Will make an entity based on incoming data.
	return (new miracleEntity(et,100,p,f));
	// MAGIC - How much health does a Miracle Have?
	//				- Using default health of 100
	//				- When it comes down to it. This really does
	//				    not matter, the entities health will become
	//				    zero after a single update anyways.
}

////  Config Method
bool MiracleManager::setProperty(std::string property, int value)
{
	miracleList[string_to_ET(property)]=value;
	return(true);
}

// converter. String -> EntityType
EntityType string_to_ET(std::string property)
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