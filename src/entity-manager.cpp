
#include <iostream>

#include "entity-manager.h"

EntityManager * EntityManager::self = 0;
std::map<std::string, void (*)(SDL_Event&, WidgetReference)> EntityManager::callbackMap;
bool EntityManager::callbackMapInitialized = false;
VillageManager EntityManager::villageManager;
WidgetContainerReference EntityManager::buttonContainer = 0;

EntityManager::EntityManager(int worldSize) :
	visible(false)
{
	if(self)
	{
		std::cerr << "\033[31m EntityManager already exists!\033[m" << std::endl;
		return;
	}
	self = this;

	initializeCallbackMap();
	buttonContainer = new SdlWidgetContainer(callbackMap, "res/sidebar.cfg");

	mapView.hide();
	widgetList.push_back(&mapView);
	SdlEntity::mapView = &mapView;
	SdlEntity::worldSize = worldSize;

	//  Village Manager
	villageManager.show();
	villageManager.addVillage(F_PLAYER_1);
	villageManager.addVillage(F_PLAYER_2);
	hide();
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


	villageManager.importEntity(record->entity);

	return record;
}

EntityRecord * EntityManager::createRecord(const EntityReference entity)
{
	return createRecord(*entity);
}

void EntityManager::update()
{
	if(!visible) show();

	villageManager.update();

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
	villageManager.show();
	mapView.show();
	buttonContainer->show();
	// unsigned long count = widgetList.size();
	// for(int index = 0; index < count; index ++)
	// 	widgetList[index]->show();
}

void EntityManager::hide()
{
	villageManager.hide();
	if(!visible) return;
	std::cout << "EntityManager::hide()" << std::endl;
	visible = false;
	mapView.hide();
	buttonContainer->hide();
}


//

void EntityManager::initializeCallbackMap()
{
	if(callbackMapInitialized) return;
	callbackMapInitialized = true;

	callbackMap["build()"] = build;

	callbackMap["triangleSliderCallback()"] = triangleSliderCallback;
	callbackMap["sliderCallback()"] = sliderCallback;
}

//

void EntityManager::build(SDL_Event & event, WidgetReference widget)
{
	std::cout << "EntityManager::build(" << widget->id << ")" << std::endl;
	if(self)
	{
		//  NOTE: widget->id is the EntityType (needs to be cast).

		self->villageManager.buildHouse();
	}
	else
		std::cerr << "EntityManager not initialized." << std::endl;
}

void EntityManager::sliderCallback(SDL_Event & event, WidgetReference widget)
{

}

void EntityManager::triangleSliderCallback(SDL_Event & event, WidgetReference widget)
{

}

