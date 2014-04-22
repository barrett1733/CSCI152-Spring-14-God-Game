
#include <iostream>

#include "village-manager.h"

VillageManager * VillageManager::self = 0;
std::map<std::string, void (*)(SDL_Event&, WidgetReference)> VillageManager::callbackMap;
bool VillageManager::callbackMapInitialized = false;

VillageManager::VillageManager()
{
	if(self)
	{
		std::cerr << "\033[31m VillagerManager already exists!\033[m" << std::endl;
		return;
	}
	self = this;

	initializeCallbackMap();

	buttonContainer = new SdlWidgetContainer(callbackMap, "res/sidebar.cfg");
	hide();
}

long VillageManager::addVillage(Faction faction)
{
	villageList.push_back(new Village(faction));
	return villageList.size();
}

void VillageManager::importEntity(EntityReference entity)
{
	long villageCount = villageList.size();
	for(long villageIndex = 0; villageIndex < villageCount; villageIndex ++)
		villageList[villageIndex]->importEntity(entity);

	if(entity->getGroup() == EG_RESOURCE || entity->getFaction() == F_STATIC)
		resourceList.push_back(entity);
}

void VillageManager::show()
{
	if(visible) return;
	visible = true;
	buttonContainer->show();
}

void VillageManager::hide()
{
	if(!visible) return;
	visible = false;
	buttonContainer->hide();
}

void VillageManager::update()
{
	show();
	// TODO: Clean out dead entities from resource list.

	long villageCount = villageList.size();
	for(long villageIndex = 0; villageIndex < villageCount; villageIndex ++)
	{
		VillageReference village = villageList[villageIndex];

		if( village->hasGodLogic() )
			village->runGodLogic();

		village->update();
	}
}

//

void VillageManager::initializeCallbackMap()
{
	if(callbackMapInitialized) return;
	callbackMapInitialized = true;

	callbackMap["buildHouse()"] = buildHouse;

	callbackMap["triangleSliderCallback()"] = triangleSliderCallback;
	callbackMap["sliderCallback()"] = sliderCallback;
}

//

void VillageManager::buildHouse(SDL_Event & event, WidgetReference widget)
{
	if(self)
		self->villageList[0]->buildHouse();
	else
		std::cerr << "VillagerManager not initialized." << std::endl;
}


void VillageManager::sliderCallback(SDL_Event & event, WidgetReference widget)
{

}
void VillageManager::triangleSliderCallback(SDL_Event & event, WidgetReference widget)
{

}

