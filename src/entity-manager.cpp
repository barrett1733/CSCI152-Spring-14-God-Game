#include "entity-manager.h"


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::addWidget(WidgetReference widget)
{
	widgetList.push_back(widget);
}

void EntityManager::deleteEntity(){}

EntityRecord * EntityManager::createRecord(const Entity & entity)
{
	Faction faction = entity.getFaction();
	EntityGroup group = entity.getGroup();

	EntityRecord *record = new EntityRecord();
	if (group < EG_MOBILE)
	{
		record->entity = new Entity(entity);
		//obstructionMap->set(record->entity->getPosition(), OT_OBSTRUCTED);
	}
	else
		record->entity = new MobileEntity(entity);

	record->widget = new SdlEntity(*record->entity);

	recordList.push_back(record);
	entityList.push_back((EntityReference)record->entity);
	widgetList.push_back(record->widget);

	factionMap[faction].push_back(record);

	//villageManager.importEntity(record->entity);

	return record;
}

EntityRecord * EntityManager::createRecord(const EntityReference entity)
{
	return createRecord(*entity);
}