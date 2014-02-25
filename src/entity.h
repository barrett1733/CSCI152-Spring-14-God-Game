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
	ET_TREE_1 = 0x000001,
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

	// PASSIVE ANIMALS
	ET_SHEEP,
	ET_COW,
	ET_HORSE,
	ET_CHICKEN,
	ET_PIG,
	ET_FISH,

	// HOSTILE ANIMALS
	ET_DEER,
	ET_BOAR,
	ET_WOLVES,
	ET_FOX,

	// MYTH CREATURES
	ET_VAMPIRE,
	ET_WEREWOLF,
	ET_HARPY,
	ET_SNOW_TROLL,
	ET_ORGE,
	ET_SIREN,
	ET_CTHULHU,
	ET_UNICORN,
	ET_CYCLOPS,

	// BUILDINGS
	ET_FOUNDATION = 0x010000,
	ET_TOWN_HALL,
	ET_HOVEL,
	ET_HOUSE,
	ET_MANSION,
	ET_STOREHOUSE,
	ET_QUARRY,
	ET_STONE_CUTTER,
	ET_WOODSHOP,
	ET_SMELTER,
	ET_BLACKSMITH,
	ET_FARMHOUSE,
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
	EntityType type;
public:
	Entity(EntityType,int,Position);
	std::string getName();
	Position getPosition();
	int getMaxHealth();
	int getCurrentHealth();
	EntityType getEntityType();
	void setName(std::string);
	void setPosition(Position);
	void setMaxHealth(int);
	void setCurrentHealth(int);
	void setEntityType(EntityType);
};

class MobileEntity : public Entity
{
private:
	int hunger;
	int faction;
	int strength;
	int defense;
public:
	int getHunger();
	int getFaction();
	int getStrength();
	int getDefense();
	void setHunger();
	void setFaction();
	void setStrength();
	void setDefense();
};

//extern Entity * EntityList;

#endif
