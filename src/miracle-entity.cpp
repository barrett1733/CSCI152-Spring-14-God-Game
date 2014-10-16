//
//  File: miracle-entity.cpp
//  Author: Allen Mills
//  CSci 152
//  Spring 2014
//
// Compilable file for miracle-entity.h
//

#include "miracle-entity.h"

// Miracle Entity, Constructor 1
MiracleEntity::MiracleEntity(EntityType type, int health, Position position, Faction faction) :
	Entity(type, position, faction)
{
}

// Miracle Entity, Constructor 2
// BUG: compile error.
//MiracleEntity::MiracleEntity(const Entity&):Entity(const Entity&){}

// Miracle Entity, update function
void MiracleEntity::update(std::vector<Entity*>& entityList, ObstructionMapReference obstructionMap){
	std::vector<Entity*> affectedEntitiesList;
	switch(this->getEntityType())
	{
		case ET_MIRACLE_HEAL:
			affectedEntitiesList=getEntitiesWithin(50.0, this->getPosition(),entityList);
			for(int i=0; i<affectedEntitiesList.size(); i++){
				affectedEntitiesList.at(i)->setCurrentHealth(affectedEntitiesList[i]->getCurrentHealth()+20);
			}
			break;
		case ET_MIRACLE_SUMMONCOW:
			entityList.push_back(new Entity(ET_COW, 100, this->getPosition(), this->getFaction()));
			break;
		case ET_MIRACLE_STATBOOST:
			affectedEntitiesList=getEntitiesWithin(75.0, this->getPosition(),entityList);
			for(int i=0; i<affectedEntitiesList.size(); i++){
				affectedEntitiesList.at(i)->setMaxHealth(affectedEntitiesList.at(i)->getMaxHealth()*2);
				affectedEntitiesList.at(i)->setCurrentHealth(affectedEntitiesList.at(i)->getMaxHealth());
			}
			break;
		case ET_MIRACLE_LIGTNING:
			affectedEntitiesList=getEntitiesWithin(25.0, this->getPosition(),entityList);
			for(int i=0; i<affectedEntitiesList.size(); i++){
				affectedEntitiesList.at(i)->setCurrentHealth(affectedEntitiesList.at(i)->getCurrentHealth()*0.75-20);
			}
			break;
		case ET_MIRACLE_EARTHQUAKE:
			affectedEntitiesList=getEntitiesWithin(100.0, this->getPosition(),entityList);
			for(int i=0; i<affectedEntitiesList.size(); i++){
				affectedEntitiesList.at(i)->setCurrentHealth(affectedEntitiesList.at(i)->getCurrentHealth()*0.50-20);
			}
			break;
		case ET_MIRACLE_METEOR:
			affectedEntitiesList=getEntitiesWithin(80.0, this->getPosition(),entityList);
			for(int i=0; i<affectedEntitiesList.size(); i++){
				affectedEntitiesList.at(i)->setCurrentHealth(0);
			}
			break;
		default:
			break;
	}
	setCurrentHealth(0);
};


// function, getEntitiesWithin
std::vector<Entity*> getEntitiesWithin(double range, Position p, std::vector<Entity*>& entityList){
	std::vector<Entity*> returnList;

	for(int i=0; i<entityList.size(); i++){
		if(p.distance(entityList.at(i)->getPosition()) <= range){
			returnList.push_back(entityList.at(i));
		}
	}

	return(returnList);
}



