
#include "village-manager.h"

std::map<std::string, void (*)(SDL_Event&, WidgetReference)> VillageManager::callbackMap;
bool VillageManager::callbackMapInitialized = false;

VillageManager::VillageManager()
{
	initializeCallbackMap(); // Must be called first.

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

	callbackMap["triangleSliderCallback()"] = triangleSliderCallback;
	callbackMap["sliderCallback()"] = sliderCallback;
}

void VillageManager::sliderCallback(SDL_Event & event, WidgetReference widget)
{

}
void VillageManager::triangleSliderCallback(SDL_Event & event, WidgetReference widget)
{

}

