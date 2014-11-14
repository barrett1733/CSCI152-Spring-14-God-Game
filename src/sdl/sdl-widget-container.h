//
//  File: sdl-widget-container.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Widget Container Defintion
// Implements the Config class to load a specified set of widget definitions from file.
// Stores a collection of widgets to be shown and hidden together.
//

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
	Color buttonColor;
	int buttonId;
	SDL_Rect rect;
	int buttonConfig;
	FontSize fontSize;

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
