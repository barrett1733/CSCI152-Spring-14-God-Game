#include "miracle-entity.h"

miracle-entity(EntityType, int health, Position, Faction):Entity(EntityType, int health, Position, Faction){}

miracle-entity(const Entity&):Entity(const Entity&){}

void update(std::vector<Entity*>& entityList, ObstructionMapReference obstructionMap){
	if(EntityType==ET_MIRACLE_HEAL){
	
	}
	else if(EntityType==ET_MIRACLE_SUMMONCOW){
	
	}
	else if(EntityType==ET_MIRACLE_STATBOOST){
	
	}
	else if(EntityType==ET_MIRACLE_LIGTNING){
	
	}
	else if(EntityType==ET_MIRACLE_EARTHQUAKE){
	
	}
	else if(EntityType==ET_MIRACLE_METEOR){
	
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


