//
//  File: sdl-manager.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Manager Class Definition
// This is a singleton class.
// It provides a global static instance called 'sdl'.
// It is reponsible for rendering all the on-screen assets.
// It handles user-driven events.
//

#ifndef SDL_MANAGER_H_
#define SDL_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include <vector>

#include <iostream>

#include "sdl-widget.h"
#include "sdl-button.h"
#include "sdl-slider.h"
#include "sdl-text-display.h"
#include "sdl-event-subscriber.h"
#include "../config.h"

class SdlManager : public Config
{
	static int FRAME_RATE;
	static unsigned int frameDuration;

	SDL_Window * window;
	SDL_Renderer * renderer;

	TextDisplayReference fpsCounter;
	long timer;
	int frameCount;

	std::vector<SdlEventSubscriber*> subscriberList;
	std::vector<SdlWidget*> widgetList[WL_COUNT];
	unsigned long widgetCount[WL_COUNT];

	unsigned int next_time;

	void wait();

	//  From Config
	bool setProperty(std::string property, int value);

public:

	SdlManager();
	~SdlManager();

	void launchWindow(const char * title, int width, int height);
	void update();
	unsigned int getRemainingFrameTime();

	// Event functions
	SubscriptionReference subscribeToEvent(void (*callback)(SDL_Event&), int type);
	SubscriptionReference subscribeToEvent(void (*callback)(SDL_Event&), int type, int sym);

	// Widget functions
	bool addWidget(WidgetReference widget, int widgetLayer)
	{
		widgetList[widgetLayer].push_back(widget);
		widgetCount[widgetLayer] = widgetList[widgetLayer].size();
		return true;
	}
	bool addWidget(WidgetReference widget)
	{
		return addWidget(widget, WL_INTERACTIVE);
	}
	void renderWidget(SdlWidget * widget);
	bool removeWidget(WidgetReference widget, int layer);
	bool removeWidget(WidgetReference widget);
};

#endif

extern SdlManager sdl;
