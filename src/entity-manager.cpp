
#include "entity-manager.h"
#include <iostream>


EntityManager::EntityManager(int worldSize) :
	visible(false)
{
	mapView.hide();
	widgetList.push_back(&mapView);
	SdlEntity::mapView = &mapView;
	SdlEntity::worldSize = worldSize;
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

EntityRecord * EntityManager::createRecord(const Entity & entity)
{
	//return createEntity(*entity);

	Faction faction = entity.getFaction();
	EntityGroup group = entity.getGroup();

	EntityRecord *record = new EntityRecord();
	record->entity = (group < EG_MOBILE) ? new Entity(entity) : new MobileEntity(entity);
	record->widget = new SdlEntity(*record->entity);

	recordList.push_back(record);
	widgetList.push_back(record->widget);

	factionMap[faction].push_back(record);

	return record;
}

EntityRecord * EntityManager::createRecord(const EntityReference entity)
{
	return createRecord(*entity);
}

void EntityManager::update()
{
	if(!visible) show();

	unsigned long count = recordList.size();
	for(unsigned long index = 0; index < count; index ++)
		recordList[index]->update();

	// ...
}

void EntityManager::show()
{
	if(visible) return;
	std::cout << "EntityManager::show()" << std::endl;
	visible = true;
	mapView.show();
	// unsigned long count = widgetList.size();
	// for(int index = 0; index < count; index ++)
	// 	widgetList[index]->show();
}

void EntityManager::hide()
{
	if(!visible) return;
	std::cout << "EntityManager::hide()" << std::endl;
	visible = false;
	mapView.hide();
}

// from config.
bool EntityManager::setProperty(std::string property, std::string value){return true;}
bool EntityManager::setProperty(std::string property, int value){return true;}
bool EntityManager::setProperty(std::string property, int value1, int value2){return true;}

