
#ifndef SDL_MANAGER_H_
#define SDL_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include <vector>

#include <iostream>
#include <unistd.h>

#include "sdl-widget.h"
#include "sdl-button.h"

const int FRAME_RATE = 30;
const int TICK_INTERVAL = 1000/FRAME_RATE;

void testCallback();

class SdlManager
{
	SDL_Window * window;
	SDL_Renderer * renderer;
	TTF_Font * font;

	std::vector<SdlWidget*> widgetList;
	int widgetCount;
	int widgetIndex;

	unsigned long next_time;

	void wait();

public:

	SdlManager();
	~SdlManager();

	void launchWindow(const char * title, int width, int height);
	bool update();

	SDL_Surface * createSurface(int width, int height);

	// Text functions
	SDL_Surface * createTextSurface(const char * text);
	TextWidgetReference createTextWidget(const char * text, int xPos, int yPos);

	// Image functions
	SDL_Texture * loadImage( const char * file);
	void renderImage(SDL_Texture * image, int xPos, int yPos, int width, int height);
	void renderImage(SDL_Texture * image, int xPos, int yPos);

	// Widget functions
	void renderWidget(SdlWidget * widget);

	// Button functions
	ButtonReference createButton(void (*callback)(), SDL_Surface * background, const char * label, int xPos, int yPos, int width, int height);
	void destroyButton(ButtonReference&);

	// Test function.
	void test()
	{
		launchWindow("Window Title!", 1024, 768);

		ButtonReference buttonRef = createButton(testCallback, 0, "Buttan!", 100, 100, 128, 32);
		TextWidgetReference textWidgetRef = createTextWidget("my text", 16, 8);

		// Main loop flag
		bool running = true;

		//While application is running
		while( running )
		{
			running = update();
		} // end while(!quit)

		destroyButton(buttonRef);
	} // end test()
};

#endif

extern SdlManager sdl;
