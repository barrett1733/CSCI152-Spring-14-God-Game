//
//  CSCI 152, Spring 2014, God Game
//

#ifndef ENTITY_H_
#define ENTITY_H_

#include "position.h"
#include <string>

enum EntityType {
	ET_NONE = 0x00,

	// RESOURCES
	ET_TREE = 0x000001,
	ET_TREE_2,
	ET_SHRUB_1,
	ET_SHRUB_2,
	ET_BOULDER,
	ET_COAL,
	ET_IRON,
	ET_GOLD,
	ET_COPPER,

	// VILLAGERS
	ET_VILLAGER = 0x000100,

	ET_ELDER_VILLAGER,
	ET_CHILD_VILLAGER,

	// DOMESTIC ANIMALS
	ET_COW,

	ET_SHEEP,
	ET_HORSE,
	ET_CHICKEN,
	ET_PIG,
	ET_FISH,

	// PASSIVE
	ET_DEER,

	// HOSTILE
	ET_WOLF,
	ET_ORGE,

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

	// BUILDINGS
	ET_FOUNDATION = 0x010000,
	ET_TOWN_CENTER,
	ET_STOREHOUSE,
	ET_HOUSE,
	ET_STONEWORKS,
	ET_LUMBERMILL,
	ET_SMELTER,
	ET_WEAPONSMITH,
	ET_ARMORSMITH,
	ET_FARM,
	ET_TEMPLE,

	ET_HOVEL,
	ET_MANSION,
	ET_QUARRY,
	ET_WATCHTOWER,
	ET_MINES
};

class Entity
{
private:
	std::string name;
	Position position;
	int maxHealth;
	int currentHealth;
	int faction;
	EntityType type;
public:
	Entity(EntityType,int,Position,int);
	std::string getName();
	Position getPosition();
	int getMaxHealth();
	int getCurrentHealth();
	int getFaction();
	EntityType getEntityType();
	void setName(std::string);
	void setPosition(Position);
	void setMaxHealth(int);
	void setCurrentHealth(int);
	void setEntityType(EntityType);
	void setFaction();
};

class MobileEntity : public Entity
{
private:
	int hunger;
	int strength;
	int defense;
public:
	int getHunger();
	int getStrength();
	int getDefense();
	void setHunger();
	void setStrength();
	void setDefense();
};

//extern Entity * EntityList;

#endif
