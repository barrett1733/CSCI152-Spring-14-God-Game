
#include "entity-manager.h"
#include "sdl/sdl-manager.h"
#include <iostream>

void EntityManager::createEntity(Entity* entityIn)
{
	std::cout << "EntityManager::createEntity() called" << std::endl;
	EM_Record *rec=new EM_Record( entityIn , Entity_HealthMap[ entityIn->getEntityType() ] );

	entityList.push_back(rec);



	sdl.addWidget(rec->widget);
	widgetList.push_back(rec->widget);
}

void EntityManager::deleteEntity(){}

/*void EntityManager::getEntityType(Entity* entityIn){
    ET_VILLAGER
	ET_ELDER_VILLAGER
	ET_CHILD_VILLAGER

	// DOMESTIC ANIMALS
	ET_COW
	ET_SHEEP
	ET_HORSE
	ET_CHICKEN
	ET_PIG
	ET_FISH
	ET_DEER

	// HOSTILE
	ET_WOLF,
	ET_OGRE,

	ET_BOAR,
	ET_FOX,
	ET_VAMPIRE,
	ET_WEREWOLF,
	ET_HARPY,
	ET_SNOW_TROLL,
	ET_SIREN,
	ET_CTHULHU,
	ET_UNICORN,
	ET_CYCLOPS,
}*/

void EntityManager::update()
{
}

void EntityManager::show()
{
	int count = widgetList.size();
	for(int index = 0; index < count; index ++)
		widgetList[index]->show();
}

void EntityManager::hide()
{
	int count = widgetList.size();
	for(int index = 0; index < count; index ++)
		widgetList[index]->hide();

}

// from config.
bool EntityManager::setProperty(std::string property, std::string value){return true;}
bool EntityManager::setProperty(std::string property, int value){return true;}
bool EntityManager::setProperty(std::string property, int value1, int value2){return true;}

