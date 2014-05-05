
#ifndef SDL_WIDGET_CONTAINER_H_
#define SDL_WIDGET_CONTAINER_H_

#include <vector>
#include <map>

#include "sdl-widget.h"
#include "../config.h"

class SdlWidgetContainer : public SdlWidget, public Config
{
	std::vector<WidgetReference> widgetList;
	std::map<std::string, void (*)(SDL_Event&, WidgetReference)> callbackMap;

	bool visible;

	std::string callbackName;
	std::string buttonLabel;
	int buttonId;
	SDL_Rect rect;
	int buttonConfig;

public:
	SdlWidgetContainer(std::map<std::string, void (*)(SDL_Event&, WidgetReference)> callbackMap, const char * loadFileName);

	void show();
	void hide();

	// From Config
	bool setProperty(std::string property, std::string value);
	bool setProperty(std::string property, int value);
	bool setProperty(std::string property, int value1, int value2);
};

#endif

typedef SdlWidgetContainer * WidgetContainerReference;
