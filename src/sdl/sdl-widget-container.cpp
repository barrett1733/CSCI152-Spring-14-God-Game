
#include <iostream>

#include "sdl-widget-container.h"
#include "sdl-text-display.h"
#include "sdl-button.h"
#include "sdl-slider.h"
#include "sdl-triangle-slider.h"

enum {
	BCFG_LABEL = 0x01,
	BCFG_CALLBACK = 0x02,

	BCFG_VALID = BCFG_LABEL | BCFG_CALLBACK,
};

void SdlWidgetContainer_doNothing(SDL_Event& event, WidgetReference widget)
{}

SdlWidgetContainer::SdlWidgetContainer(std::map<std::string, void (*)(SDL_Event&, WidgetReference)> callbackMap, const char * fileName) :
	callbackMap(callbackMap),
	visible(true),
	callbackName(""),
	buttonLabel(""),
	buttonId(0),
	buttonConfig(0)
{
	this->callbackMap["nothing"] = SdlWidgetContainer_doNothing;
	load(fileName);
	hide();
}

void SdlWidgetContainer::show()
{
	if(visible) return;
	visible = true;

	std::cout << "SdlWidgetContainer::show()" << std::endl;

	long widgetCount = widgetList.size();
	for(long widgetIndex = 0; widgetIndex < widgetCount; widgetIndex ++)
		widgetList[widgetIndex]->show();
}

void SdlWidgetContainer::hide()
{
	if(!visible) return;
	visible = false;

	std::cout << "SdlWidgetContainer::hide()" << std::endl;

	long widgetCount = widgetList.size();
	for(long widgetIndex = 0; widgetIndex < widgetCount; widgetIndex ++)
		widgetList[widgetIndex]->hide();
}


// From Config
bool SdlWidgetContainer::setProperty(std::string property, std::string value)
{
	if(property == "label")
	{
		buttonLabel = value;
		buttonConfig |= BCFG_LABEL;
	}

	else if(property == "callback")
	{
		callbackName = "nothing";
		if(!callbackMap[value])
			return false;
		callbackName = value;
		buttonConfig |= BCFG_CALLBACK;
	}

	else if(property == "create")
	{
		if( ! (buttonConfig & BCFG_VALID))
		{
			std::cerr << "\033[33m Invalid Button Configuration: " << buttonConfig << " != " << BCFG_VALID << "\033[m" << std::endl;
			if( ! (buttonConfig & BCFG_LABEL)) std::cerr << "Missing label." << std::endl;
			if( ! (buttonConfig & BCFG_CALLBACK)) std::cerr << "Missing callback." << std::endl;
			return false;
		}

		WidgetReference widget;

		if(value == "text")
			widget = new SdlTextDisplay(buttonLabel.c_str(), rect);

		else if(value == "button")
			widget = new SdlButton(buttonLabel.c_str(), rect, callbackMap[callbackName]);

		else if(value == "slider")
			widget = new SdlSlider(rect, callbackMap[callbackName]);

		else if(value == "triangle-slider")
			widget = new SdlTriangleSlider(rect, callbackMap[callbackName]);

		else return false;

		widget->id = buttonId;
		widgetList.push_back(widget);
		buttonConfig = 0;
		buttonId = 0;
	}

	else return false;

	return true;
}

bool SdlWidgetContainer::setProperty(std::string property, int value)
{
	if(property == "id")
	{
		buttonId = value;
		return true;
	}
	return false;
}

bool SdlWidgetContainer::setProperty(std::string property, int value1, int value2)
{
	if(property == "position")
	{
		rect.x = value1;
		rect.y = value2;
		return true;
	}
	else if(property == "size")
	{
		rect.w = value1;
		rect.h = value2;
		return true;
	}
	return false;
}
