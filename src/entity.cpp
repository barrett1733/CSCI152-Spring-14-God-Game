
#include "entity.h"

//Entity * EntityList[MAX_ENTITY_COUNT];

Entity::Entity(const Entity & entity) :
	type(entity.type),
	maxHealth(entity.maxHealth),
	currentHealth(entity.currentHealth),
	faction(entity.faction),
	position(entity.position)
{ }

Entity::Entity(EntityType entityType, int health, Position position, Faction faction) :
	type(entityType),
	maxHealth(health),
	currentHealth(health),
	faction(faction),
	position(position)
{ }

Entity::Entity(EntityType entityType, int health, int xPos, int yPos, Faction faction) :
	type(entityType),
	maxHealth(health),
	currentHealth(health),
	faction(faction),
	position(xPos, yPos)
{ }

Entity& Entity::operator= (const Entity& entity)
{
	name = entity.name;
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
void Entity::setEntityType(EntityType type) {
	this->type = type;
}
void Entity::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}
void Entity::setCurrentHealth(int currentHealth) {
	this->currentHealth = currentHealth;
}
void Entity::setName(std::string name) {
	this->name = name;
}
void Entity::setPosition(Position position) {
	this->position = position;
}
void Entity::setFaction(Faction faction) {
	this->faction = faction;
}


MobileEntity::MobileEntity(EntityType entityType, int health, Position position, Faction faction, int hunger, int strength, int defense):
	Entity(entityType, health, position, faction),
	hunger(hunger),
	strength(strength),
	defense(defense)
{ }
MobileEntity::MobileEntity(EntityType entityType, int health, int xPos, int yPos, Faction faction, int hunger, int strength, int defense):
	Entity(entityType, health, xPos, yPos, faction),
	hunger(hunger),
	strength(strength),
	defense(defense)
{ }

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
			position.move(PD_UP);
			break;

		case 1:
			position.move(PD_RIGHT);
			break;

		case 2:
			position.move(PD_DOWN);
			break;

		case 3:
			position.move(PD_LEFT);
			break;
	}
}
