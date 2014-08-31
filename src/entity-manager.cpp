#include "entity-manager.h"


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::deleteRecord(){}

EntityReference EntityManager::createRecord(const Entity & entity)
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

	recordMap.insert(EntityRecordPair(record->entity->getGroup(), record));

	factionMap[faction].push_back(record);

	return record->entity;
}

EntityReference EntityManager::createRecord(const EntityReference entity)
{
	return createRecord(*entity);
}

void EntityManager::update(ObstructionMapReference obstructionMap)
{
	std::map<EntityGroup, EntityRecord*>::iterator it;

	for (it = recordMap.begin(); it != recordMap.end(); ++it)
		it->second->erase();

	for (it = recordMap.begin(); it != recordMap.end(); ++it)
		it->second->update(obstructionMap);
}
