
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

		ButtonReference buttonRef = createButton(testCallback, 0, "Buttaaaaaaaaaaaaaaaaaaaaaaaan!", 100, 100, 128, 32);

		SDL_Texture * my_dot  = loadImage("res/dot.bmp");
		TextWidgetReference textWidgetRef = createTextWidget("my text", 16, 8);

		// dot position and size
		float xPos, yPos;
		xPos = 400;
		yPos = 300;

		// dot velocity
		float velocityIncrement = 0.5;
		float xVel, yVel;
		xVel = 0;
		yVel = 0;

		// Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event event;

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while(SDL_PollEvent(&event) != 0)
			{
				//User requests quit
				switch(event.type)
				{
					case SDL_MOUSEMOTION:
					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
						widgetCount = widgetList.size();
						for(widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
							widgetList[widgetIndex]->handleEvent(event);
						break;

					case SDL_KEYDOWN:
						switch(event.key.keysym.sym)
						{
							case SDLK_UP: yVel -= velocityIncrement; break;
							case SDLK_DOWN: yVel += velocityIncrement; break;
							case SDLK_LEFT: xVel -= velocityIncrement; break;
							case SDLK_RIGHT: xVel += velocityIncrement; break;
							case '\e' : quit = true; break;
							default : std::cout << event.key.keysym.sym << std::endl; break;
						}
						break;

					case SDL_QUIT:
						quit = true;
						break;

				}

			}

			xPos += xVel;
			yPos += yVel;

			if(xPos < 0)    xPos = 1023;
			if(xPos > 1023) xPos = 0;
			if(yPos < 0)    yPos = 767;
			if(yPos > 767)  yPos = 0;

			// Clear screen
			SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( renderer );
			SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );

			// Render everything
			for(widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
				renderWidget(widgetList[widgetIndex]);//widgetList[widgetIndex]->render(renderer);
			renderImage(my_dot, xPos, yPos, 8, 8);

			// Update screen
			SDL_RenderPresent( renderer );

			wait();
		} // end while(!quit)

		destroyButton(buttonRef);
	} // end test()
};

#endif

extern SdlManager sdl;
