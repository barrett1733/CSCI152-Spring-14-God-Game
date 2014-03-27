
#include "entity-manager.h"
#include "sdl/sdl-manager.h"
#include <iostream>

void EntityManager::createEntity(Entity* entityIn)
{
	std::cout << "EntityManager::createEntity() called" << std::endl;
	EM_Record *rec=new EM_Record(entityIn,0,0);

	entityList.push_back(rec);
	sdl.addWidget(rec->widget);
	widgetList.push_back(rec->widget);
}

void EntityManager::deleteEntity(){}

void EntityManager::getEntityType(){}

void EntityManager::update()
{
}

void EntityManager::show()
{
	int count = widgetList.size();
	for(int index = 0; index < count; index ++)
		widgetList[index]->show();
}

void EntityManager::hide()
{
	int count = widgetList.size();
	for(int index = 0; index < count; index ++)
		widgetList[index]->hide();

}

// from config.
bool EntityManager::setProperty(std::string property, std::string value){return true;}
bool EntityManager::setProperty(std::string property, int value){return true;}
bool EntityManager::setProperty(std::string property, int value1, int value2){return true;}

