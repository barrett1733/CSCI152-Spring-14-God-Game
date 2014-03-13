
#ifndef SDL_MANAGER_H_
#define SDL_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include <vector>

#include <iostream>
//#include <unistd.h>

#include "sdl-widget.h"
#include "sdl-button.h"
#include "sdl-slider.h"
#include "sdl-text-display.h"
#include "sdl-event-subscriber.h"

const int FRAME_RATE = 30;
const unsigned int TICK_INTERVAL = 1000/FRAME_RATE;

enum {
	WL_BACKGROUND,
	WL_NON_INTERACTIVE,
	WL_INTERACTIVE,

	WL_COUNT
};

class SdlManager
{
	SDL_Window * window;
	SDL_Renderer * renderer;
	TTF_Font * font;

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
	void addWidget(WidgetReference widget, int widgetLayer)
	{
		widgetList[widgetLayer].push_back(widget);
		widgetCount[widgetLayer] = widgetList[widgetLayer].size();
	}
	void addWidget(WidgetReference widget)
	{
		return addWidget(widget, WL_INTERACTIVE);
	}
	void renderWidget(SdlWidget * widget);

	// Button functions
	ButtonReference createButton(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, const char * label, int xPos, int yPos, int width, int height);
	ButtonReference createButton(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, const char * label, int xPos, int yPos);
	void destroyButton(ButtonReference&);

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