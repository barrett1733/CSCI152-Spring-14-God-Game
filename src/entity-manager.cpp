
#include "entity-manager.h"
#include "sdl/sdl-manager.h"
#include <iostream>

void EntityManager::createEntity(Entity* entityIn)
{
	std::cout << "EntityManager::createEntity() called" << std::endl;
	EM_Record *rec=new EM_Record(entityIn,C_Blue);
	
	entityList->push_back(rec->entity);
	sdl.addWidget(rec->widget);
	widgetList.push_back(rec->widget);
}

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
