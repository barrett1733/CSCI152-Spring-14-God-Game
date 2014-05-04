#include "miracle-entity.h"

miracle-entity(EntityType, int health, Position, Faction):Entity(EntityType, int health, Position, Faction){}

miracle-entity(const Entity&):Entity(const Entity&){}

void update(std::vector<Entity*>& entityList, ObstructionMapReference obstructionMap){
	std::vector<Entity*> affectedEntitiesList;
	if(EntityType==ET_MIRACLE_HEAL){
		affectedEntitiesList=getEntitiesWithin(50.0, this->getPosition(),entityList);
		for(int i=0; i<affectedEntitiesList.size(); i++){
			affectedEntitiesList[i].setCurrentHealth(affectedEntitiesList[i].getCurrentHealth()+20);
		}
	}
	else if(EntityType==ET_MIRACLE_SUMMONCOW){
		entityList.pushBack(new Entity(ET_COW, 100, this->getPosition(), this->getFaction()));
	}
	else if(EntityType==ET_MIRACLE_STATBOOST){
		affectedEntitiesList=getEntitiesWithin(75.0, this->getPosition(),entityList);
		for(int i=0; i<affectedEntitiesList.size(); i++){
			affectedEntitiesList[i].setMaxHealth(affectedEntitiesList[i].getMaxHealth()*2);
			affectedEntitiesList[i].setCurrentHealth(affectedEntitiesList[i].getMaxHealth());
		}
	}
	else if(EntityType==ET_MIRACLE_LIGTNING){
		affectedEntitiesList=getEntitiesWithin(25.0, this->getPosition(),entityList);
		for(int i=0; i<affectedEntitiesList.size(); i++){
			affectedEntitiesList[i].setCurrentHealth(affectedEntitiesList[i].getCurrentHealth()*0.75-20);
		}
	}
	else if(EntityType==ET_MIRACLE_EARTHQUAKE){
		affectedEntitiesList=getEntitiesWithin(100.0, this->getPosition(),entityList);
		for(int i=0; i<affectedEntitiesList.size(); i++){
			affectedEntitiesList[i].setCurrentHealth(affectedEntitiesList[i].getCurrentHealth()*0.50-20);
		}
	}
	else if(EntityType==ET_MIRACLE_METEOR){
		affectedEntitiesList=getEntitiesWithin(80.0, this->getPosition(),entityList);
		for(int i=0; i<affectedEntitiesList.size(); i++){
			affectedEntitiesList[i].setCurrentHealth(0);
		}
	}
	else{
	
	}
	setCurrentHealth(0);
};

std::vector<Entity*>& getEntitiesWithin(double range, Position p, std::vector<Entity*>& entityList){
	std::vector<Entity*> returnList;
	
	for(int i=0; i<entityList.size(); i++){
		if(p.distance(entityList[i].getPosition()) <= range){
			retrunList.pushBack(entityList[i]);
		}
	}
	
	return(&returnList);
}


