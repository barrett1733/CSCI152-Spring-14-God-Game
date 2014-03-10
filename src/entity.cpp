
#include "entity.h"

//Entity * EntityList[MAX_ENTITY_COUNT];

Entity::Entity(EntityType entityType, int health, Position position):type(entityType),currentHealth(health),maxHealth(health),position(position)
{ }

EntityType Entity::getEntityType() {
	return this->type;
}
std::string Entity::getName() {
	return this->name;
}
int Entity::getMaxHealth() {
	return this->maxHealth;
}
int Entity::getCurrentHealth() {
	return this->currentHealth;
}
Position Entity::getPosition() {
	return this->position;
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