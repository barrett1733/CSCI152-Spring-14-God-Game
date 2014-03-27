
#include "entity-manager.h"
#include "sdl/sdl-manager.h"
#include <iostream>

EntityManager::EntityManager() :
	visible(false)
{
	mapView.hide();
}
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

void EntityManager::createEntity(const Entity & entity)
{
	//return createEntity(*entity);
	std::cout << "EntityManager::createEntity(const Entity&)" << std::endl;

	Faction faction = entity.getFaction();

	EM_Record *record = new EM_Record();
	record->entity = new Entity(entity);
	record->widget = new SdlEntity(entity);

	recordList.push_back(record);
	factionMap[faction].push_back(record);
}

void EntityManager::createEntity(const EntityReference entity)
{
	std::cout << "EntityManager::createEntity(const EntityReference)" << std::endl;
	return createEntity(*entity);
}

void EntityManager::update()
{
	if(!visible) show();

	// ...
}

void EntityManager::show()
{
	if(visible) return;
	std::cout << "EntityManager::show()" << std::endl;
	visible = true;

	mapView.show();

	int count = widgetList.size();
	for(int index = 0; index < count; index ++)
		widgetList[index]->show();
}

void EntityManager::hide()
{
	if(!visible) return;
	std::cout << "EntityManager::hide()" << std::endl;
	visible = false;
	int count = widgetList.size();
	for(int index = 0; index < count; index ++)
		widgetList[index]->hide();

}

// from config.
bool EntityManager::setProperty(std::string property, std::string value){return true;}
bool EntityManager::setProperty(std::string property, int value){return true;}
bool EntityManager::setProperty(std::string property, int value1, int value2){return true;}

