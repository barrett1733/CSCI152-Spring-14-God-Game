#include "entity-manager.h"


EntityManager::EntityManager()
{
	load("res/stats-files.cfg");
	loadingType = ET_NONE;
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
		//setStats(*record->entity);
		//obstructionMap->set(record->entity->getPosition(), OT_OBSTRUCTED);
	}
	else
	{
		record->entity = new MobileEntity(entity);
		//setStats(*record->entity);
	}

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

void EntityManager::setStats(Entity& entity)
{
	EntityType type = entity.getEntityType();
	entity.setCurrentHealth(entityStatsMap[type].getCurrentHealth());
	entity.setMaxHealth(entityStatsMap[type].getMaxHealth());
}

void EntityManager::setStats(MobileEntity& entity)
{
	EntityType type = entity.getEntityType();
	entity.setCurrentHealth(entityStatsMap[type].getCurrentHealth());
	entity.setMaxHealth(entityStatsMap[type].getMaxHealth());
	entity.setStrength(entityStatsMap[type].getStrength());
	entity.setDefense(entityStatsMap[type].getDefense());
}

bool EntityManager::setProperty(std::string property, std::string value)
{
	if (property == "type")
	{
		if ("ET_RESOURCE" == value) loadingType = ET_RESOURCE;
		if ("ET_TREE" == value) loadingType = ET_TREE;
		if ("ET_TREE_2" == value) loadingType = ET_TREE_2;
		if ("ET_SHRUB_1" == value) loadingType = ET_SHRUB_1;
		if ("ET_SHRUB_2" == value) loadingType = ET_SHRUB_2;
		if ("ET_BOULDER" == value) loadingType = ET_BOULDER;
		if ("ET_STONE" == value) loadingType = ET_STONE;
		if ("ET_COAL" == value) loadingType = ET_COAL;
		if ("ET_IRON" == value) loadingType = ET_IRON;
		if ("ET_GOLD" == value) loadingType = ET_GOLD;
		if ("ET_COPPER" == value) loadingType = ET_COPPER;

		if ("ET_VILLAGER" == value) loadingType = ET_VILLAGER;

		if ("ET_ELDER_VILLAGER" == value) loadingType = ET_ELDER_VILLAGER;
		if ("ET_CHILD_VILLAGER" == value) loadingType = ET_CHILD_VILLAGER;

		// DOMESTIC ANIMALS
		if ("ET_DOMESTIC" == value) loadingType = ET_DOMESTIC;
		if ("ET_COW" == value) loadingType = ET_COW;

		if ("ET_SHEEP" == value) loadingType = ET_SHEEP;
		if ("ET_HORSE" == value) loadingType = ET_HORSE;
		if ("ET_CHICKEN" == value) loadingType = ET_CHICKEN;
		if ("ET_PIG" == value) loadingType = ET_PIG;
		if ("ET_FISH" == value) loadingType = ET_FISH;

		// PASSIVE
		if ("ET_PASSIVE" == value) loadingType = ET_PASSIVE;
		if ("ET_DEER" == value) loadingType = ET_DEER;

		// HOSTILE
		if ("ET_HOSTILE" == value) loadingType = ET_HOSTILE;
		if ("ET_WOLF" == value) loadingType = ET_WOLF;
		if ("ET_OGRE" == value) loadingType = ET_OGRE;

		if ("ET_BOAR" == value) loadingType = ET_BOAR;
		if ("ET_FOX" == value) loadingType = ET_FOX;
		if ("ET_VAMPIRE" == value) loadingType = ET_VAMPIRE;
		if ("ET_WEREWOLF" == value) loadingType = ET_WEREWOLF;
		if ("ET_HARPY" == value) loadingType = ET_HARPY;
		if ("ET_SNOW_TROLL" == value) loadingType = ET_SNOW_TROLL;
		if ("ET_SIREN" == value) loadingType = ET_SIREN;
		if ("ET_CTHULHU" == value) loadingType = ET_CTHULHU;
		if ("ET_UNICORN" == value) loadingType = ET_UNICORN;
		if ("ET_CYCLOPS" == value) loadingType = ET_CYCLOPS;

		// BUILDINGS
		if ("ET_BUILDING" == value) loadingType = ET_BUILDING;

		// In-Game buildings
		if ("ET_TOWN_CENTER" == value) loadingType = ET_TOWN_CENTER;
		if ("ET_TEMPLE" == value) loadingType = ET_TEMPLE;
		if ("ET_HOUSE" == value) loadingType = ET_HOUSE;
		if ("ET_MILL" == value) loadingType = ET_MILL;
		if ("ET_MASONRY" == value) loadingType = ET_MASONRY;
		if ("ET_FOUNDARY" == value) loadingType = ET_FOUNDARY;
		if ("ET_SMITH" == value) loadingType = ET_SMITH;
		if ("ET_ARMORY" == value) loadingType = ET_ARMORY;

		if ("ET_FOUNDATION" == value) loadingType = ET_FOUNDATION;
		if ("ET_STOREHOUSE" == value) loadingType = ET_STOREHOUSE;
		if ("ET_STONEWORKS" == value) loadingType = ET_STONEWORKS;
		if ("ET_LUMBERMILL" == value) loadingType = ET_LUMBERMILL;
		if ("ET_SMELTER" == value) loadingType = ET_SMELTER;
		if ("ET_WEAPONSMITH" == value) loadingType = ET_WEAPONSMITH;
		if ("ET_ARMORSMITH" == value) loadingType = ET_ARMORSMITH;
		if ("ET_FARM" == value) loadingType = ET_FARM;
		if ("ET_HOVEL" == value) loadingType = ET_HOVEL;
		if ("ET_MANSION" == value) loadingType = ET_MANSION;
		if ("ET_QUARRY" == value) loadingType = ET_QUARRY;
		if ("ET_WATCHTOWER" == value) loadingType = ET_WATCHTOWER;
		if ("ET_MINES" == value) loadingType = ET_MINES;

		//Miracles
		if ("ET_MIRACLE" == value) loadingType = ET_MIRACLE;
		if ("ET_MIRACLE_HEAL" == value) loadingType = ET_MIRACLE_HEAL;
		if ("ET_MIRACLE_SUMMONCOW" == value) loadingType = ET_MIRACLE_SUMMONCOW;
		if ("ET_MIRACLE_STATBOOST" == value) loadingType = ET_MIRACLE_STATBOOST;
		if ("ET_MIRACLE_LIGTNING" == value) loadingType = ET_MIRACLE_LIGTNING;
		if ("ET_MIRACLE_EARTHQUAKE" == value) loadingType = ET_MIRACLE_EARTHQUAKE;
		if ("ET_MIRACLE_METEOR" == value) loadingType = ET_MIRACLE_METEOR;
	}
	else return false;
	return true;
}

bool EntityManager::setProperty(std::string property, int value)
{
	if (property == "health")
	{
		entityStatsMap[loadingType].setCurrentHealth(value);
		entityStatsMap[loadingType].setMaxHealth(value);
	}
	if (property == "attack")
	{
		entityStatsMap[loadingType].setStrength(value);
	}
	if (property == "defense")
	{
		entityStatsMap[loadingType].setDefense(value);
	}
	if (property == "sightrange")
	{
		entityStatsMap[loadingType].setSightRange(value);
	}
	return true;
}
