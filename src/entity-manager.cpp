
#include "entity-manager.h"
#include "sdl/sdl-manager.h"
#include <iostream>

void EntityManager::createEntity()
{
	std::cout << "EntityManager::createEntity()" << std::endl;
	WidgetReference testWidget = new SdlEntity(C_BLUE, 16);
	testWidget->enable();
	sdl.addWidget(testWidget);

	widgetList.push_back(testWidget);
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
