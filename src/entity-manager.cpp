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

void EntityManager::createRecord(const Entity & entity)
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
}

void EntityManager::createRecord(const EntityReference entity)
{
	createRecord(*entity);
}

void EntityManager::update(ObstructionMapReference obstructionMap)
{
	unsigned long count = recordList.size();
	for (unsigned long index = 0; index < count; index++)
		recordList[index]->update(entityList, obstructionMap);
}