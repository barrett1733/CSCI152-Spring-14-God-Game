
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

const int FRAME_RATE = 30;
const unsigned int TICK_INTERVAL = 1000/FRAME_RATE;

class SdlManager
{
	SDL_Window * window;
	SDL_Renderer * renderer;

	TextDisplayReference fpsCounter;
	int timer;
	int frameCount;

	std::vector<SdlEventSubscriber*> subscriberList;
	std::vector<SdlWidget*> widgetList[WL_COUNT];
	int widgetCount[WL_COUNT];

	unsigned long next_time;

	void wait();

	static void testCallback(SDL_Event & event, WidgetReference widget)
	{
		std::cout << "Callback!" << std::endl;
	}

public:

	SdlManager();
	~SdlManager();

	void launchWindow(const char * title, int width, int height);
	void update();

	// Event functions
	SubscriptionReference subscribeToEvent(void (*callback)(SDL_Event&), int type);
	SubscriptionReference subscribeToEvent(void (*callback)(SDL_Event&), int type, int sym);

	// Text functions
	WidgetReference createTextWidget(const char * text, int xPos, int yPos);
	TextDisplayReference createTextDisplay(std::string text, int xPos, int yPos);

	// Image functions
	SDL_Texture * loadImage( const char * file);
	void renderImage(SDL_Texture * image, int xPos, int yPos, int width, int height);
	void renderImage(SDL_Texture * image, int xPos, int yPos);

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

	// Button functions
	ButtonReference createButton(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, const char * label, int xPos, int yPos, int width, int height);
	ButtonReference createButton(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, const char * label, int xPos, int yPos);

	// Slider functions
	SliderReference createSlider(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, int xPos, int yPos, int width, int height);
	SliderReference createSlider(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, int xPos, int yPos);

	// Test function.
	void test_setUp()
	{
		std::cout << "Running test set-up." << std::endl;
		launchWindow("Window Title!", 800, 600);

		std::cout << "Test Set-up: Creating button..." << std::endl;
		createButton(testCallback, 0, "Buttan!", 100, 100, 128, 32);

		std::cout << "Test Set-up: Creating text widget..." << std::endl;
		createTextWidget("my text", 16, 8);

		std::cout << "Test set-up done." << std::endl;

	} // end test()
};

#endif

extern SdlManager sdl;
