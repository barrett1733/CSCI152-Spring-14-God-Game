
#include "entity.h"

//Entity * EntityList[MAX_ENTITY_COUNT];

Entity::Entity(const Entity & entity) :
	group(entity.group),
	type(entity.type),
	faction(entity.faction),
	maxHealth(entity.maxHealth),
	currentHealth(entity.currentHealth),
	position(entity.position)
{ }

Entity::Entity(EntityType type, int health, Position position, Faction faction) :
	type(type),
	faction(faction),
	maxHealth(health),
	currentHealth(health),
	position(position)
{ }




Entity& Entity::operator= (const Entity& entity)
{
	name = entity.name;
	group = entity.group;
	type = entity.type;
	faction = entity.faction;
	position = entity.position;
	currentHealth = entity.currentHealth;
	maxHealth = entity.maxHealth;

	return *this;
}

std::string Entity::getName() const
{
	return this->name;
}

EntityGroup Entity::getGroup() const
{
	return this->group;
}

EntityType Entity::getEntityType() const
{
	return this->type;
}

EntityType Entity::getType() const
{
	return this->type;
}

Position Entity::getPosition() const
{
	return this->position;
}

Faction Entity::getFaction() const
{
	return this->faction;
}

int Entity::getMaxHealth() {
	return this->maxHealth;
}
int Entity::getCurrentHealth() {
	return this->currentHealth;
}


void Entity::setName(std::string name)
{
	this->name = name;
}
void Entity::setGroup(EntityGroup group)
{
	this->group = group;
}
void Entity::setEntityType(EntityType type)
{
	this->type = type;
}
void Entity::setFaction(Faction faction)
{
	this->faction = faction;
}
void Entity::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}
void Entity::setCurrentHealth(int currentHealth)
{
	this->currentHealth = currentHealth;
}
void Entity::setPosition(Position position)
{
	this->position = position;
}

////////
//  MOBILE ENTITY
////////

MobileEntity::MobileEntity(const Entity & entity) :
	Entity(entity)
{}

int MobileEntity::getHunger() {
	return this->hunger;
}
int MobileEntity::getStrength() {
	return this->strength;
}
int MobileEntity::getDefense() {
	return this->defense;
}

void MobileEntity::setHunger(int hunger) {
	this->hunger = hunger;
}
void MobileEntity::setStrength(int strength) {
	this->strength = strength;
}
void MobileEntity::setDefense(int defense) {
	this->defense = defense;
}

void MobileEntity::update()
{
	int r = rand();
	switch(r % 4)
	{
		case 0:
			position.move(D_UP);
			break;

		case 1:
			position.move(D_RIGHT);
			break;

		case 2:
			position.move(D_DOWN);
			break;

		case 3:
			position.move(D_LEFT);
			break;
	}
}
