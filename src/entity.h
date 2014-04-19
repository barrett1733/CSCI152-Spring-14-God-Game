//
//  CSCI 152, Spring 2014, God Game
//

#ifndef ENTITY_H_
#define ENTITY_H_

#include "position.h"
#include <string>

enum Faction {
	FT_NONE,
	FT_STATIC, // TODO: Rename FT_RESOURCE. -CH
	FT_ANIMAL_DOMESTIC, // Should not exist. Domistics belong to a village faction. -CH
	FT_ANIMAL_PASSIVE,
	FT_ANIMAL_HOSTILE,
	FT_PLAYER_1,
	FT_PLAYER_2,
	FT_PLAYER_3,
	FT_PLAYER_4,
	FT_PLAYER_5,
	FT_PLAYER_6,
	FT_PLAYER_7,
	FT_PLAYER_8,

	FT_COUNT
};

enum EntityGroup {
	EG_NONE,
	EG_RESOURCE,
	EG_BUILDING,

	EG_MOBILE, // if entity.group < EG_MOBILE, then entity isn't mobile

	EG_VILLAGER,
	EG_DOMESTIC,
	EG_PASSIVE,
	EG_HOSTILE,
};

enum EntityType {
	ET_NONE = 0x00,

	// RESOURCES
	ET_TREE = 0x000001,
	ET_TREE_2,
	ET_SHRUB_1,
	ET_SHRUB_2,
	ET_BOULDER,
	ET_STONE,
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
	endofdmestics,
	// PASSIVE
	ET_DEER,

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
	EntityGroup group;
	EntityType type;
	Faction faction;
	int maxHealth;
	int currentHealth;

protected:
	Position position;

public:
	Entity(const Entity&);
	Entity(EntityType, int health, Position, Faction);

	Entity& operator= (const Entity&);

	std::string getName() const;
	EntityGroup getGroup() const;
	EntityType getEntityType() const;
	EntityType getType() const;
	Faction getFaction() const;
	Position getPosition() const;
	int getMaxHealth();
	int getCurrentHealth();

	void setName(std::string);
	void setGroup(EntityGroup);
	void setEntityType(EntityType);
	void setFaction(Faction);
	void setMaxHealth(int);
	void setCurrentHealth(int);
	void setPosition(Position);

	virtual void update() {}

	friend std::ostream& operator<< (std::ostream & os, const Entity & entity)
	{
		os << entity.name << " ";
		os << entity.type << " ";
		os << entity.faction << " ";
		os << entity.position << " ";
		os << entity.currentHealth << "/" << entity.maxHealth;
		return os;
	}
};

class MobileEntity : public Entity
{
private:
	int hunger;
	int strength;
	int defense;
public:
	MobileEntity(const Entity&);
	int getHunger();
	int getStrength();
	int getDefense();
	void setHunger(int);
	void setStrength(int);
	void setDefense(int);

	void update();
};

typedef Entity * EntityReference;

#endif
