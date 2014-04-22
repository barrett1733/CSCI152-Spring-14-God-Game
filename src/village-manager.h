
#ifndef VILLAGE_MANAGER_H_
#define VILLAGE_MANAGER_H_

#include <vector>
#include <map>

#include "village.h"
#include "entity-manager.h"
#include "sdl/sdl-widget-container.h"

class VillageManager
{
	WidgetContainerReference buttonContainer;

	std::vector<VillageReference> villageList;
	std::vector<EntityReference> resourceList;

	bool visible;

	static std::map<std::string, void (*)(SDL_Event&, WidgetReference)> callbackMap;
	static bool callbackMapInitialized;

public:
	VillageManager();

	long addVillage(Faction);

	void importEntity(EntityReference);

	void show();
	void hide();
	void update();


	static void initializeCallbackMap();
	static void sliderCallback(SDL_Event&, WidgetReference);
	static void triangleSliderCallback(SDL_Event&, WidgetReference);
};

#endif
