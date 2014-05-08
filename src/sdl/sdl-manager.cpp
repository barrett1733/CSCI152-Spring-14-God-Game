//
//  File: sdl-manager.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Manager Implementation
//

#include <ctime>
#include "sdl-manager.h"
#include <iostream>
#include <sstream>

int SdlManager::FRAME_RATE = 30;
unsigned int SdlManager::frameDuration = 1000/SdlManager::FRAME_RATE;

SdlManager sdl;

SdlManager::SdlManager() :
	window(0),
	renderer(0),
	texture(0),
	next_time(0)
{
	std::cout << "SdlManager::SdlManager() - SDL_Init()" << std::endl;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		throw "SDL_Init()";
	}

	//SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1");
	SDL_SetHint( SDL_HINT_RENDER_DRIVER, "opengl");
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1");

	// Initialize PNG loading
	std::cout << "SdlManager::SdlManager() - IMG_Init()" << std::endl;
	int imgFlags = IMG_INIT_PNG;
	if( ! ( IMG_Init( imgFlags ) & imgFlags ) )
	{
		std::cerr << SDL_GetError() << std::endl;
		throw "IMG_Init()";
	}

	std::cout << "SdlManager::SdlManager() - Initializing Frame Counter" << std::endl;
	timer = time(0);
	frameCount = 0;

	std::cout << "SdlManager::SdlManager() - Loading config" << std::endl;
	load("res/sdl.cfg");

	std::cout << "Ready." << std::endl;
}

SdlManager::~SdlManager()
{
	std::cout << "SdlManager::~SdlManager()" << std::endl;

	if(renderer) SDL_DestroyRenderer(renderer);
	if(window)   SDL_DestroyWindow(window);
	if(texture)  SDL_DestroyTexture(texture);

	IMG_Quit();
	SDL_Quit();
}

////////
//  CONFIG
////////

bool SdlManager::setProperty(std::string property, int value)
{
	if(property == "frame_rate")
	{
		FRAME_RATE = value;
		frameDuration = 1000/FRAME_RATE;
		return true;
	}
	return false;
}

////////

void SdlManager::update()
{
	SDL_Event event;

	unsigned long subscriberCount = subscriberList.size();

	//Handle events on queue
	while(SDL_PollEvent(&event) != 0)
	{
		for(unsigned long subscriberIndex = 0; subscriberIndex < subscriberCount; subscriberIndex++)
			subscriberList[subscriberIndex]->handleEvent(event);

		for(unsigned long widgetIndex = 0; widgetIndex < widgetCount[WL_INTERACTIVE]; ++widgetIndex)
			widgetList[WL_INTERACTIVE][widgetIndex]->handleEvent(event);
	} // end event handler loop

	// Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );

	// Render everything to renderTexture
	for(int layerIndex = 0; layerIndex < WL_COUNT; layerIndex ++)
		for(int widgetIndex = 0; widgetIndex < widgetCount[layerIndex]; ++widgetIndex)
			renderWidget(widgetList[layerIndex][widgetIndex]);

	// Copy render texture and update screen
	SDL_RenderPresent( renderer );

	// Update frame rate display
	frameCount ++;
	if(timer != time(0))
	{
		timer = time(0);

		std::stringstream ss;
		ss << (frameCount) << " fps";
		fpsCounter->setText(ss.str());

		frameCount = 0;
	}

	// Waste time until the next frame starts
	wait();
}

void SdlManager::renderWidget(SdlWidget * widget)
{
	return widget->render(renderer);
}

unsigned int SdlManager::getRemainingFrameTime()
{
	unsigned int now = SDL_GetTicks();
	unsigned int time_left = 0;
	if(next_time > now)
		time_left = next_time - now;
	return time_left;
}

void SdlManager::wait()
{
	unsigned int time_left = getRemainingFrameTime();
	next_time = SDL_GetTicks() + frameDuration;
	SDL_Delay(time_left);
}

////////

void SdlManager::launchWindow(const char * title, int width, int height)
{
	if(window) throw "Window exists.";

	std::cout << "SdlManager::launchWindow() - starting" << std::endl;

	next_time = 0;

	// Create window
	std::cout << "SDL_CreateWindow()" << std::endl;
	if ( ! ( window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN) ) )
		throw "SDL_CreateWindow";

	// Create renderer for window
	std::cout << "SDL_CreateRenderer()" << std::endl;
	if ( ! ( renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE ) ) )
		throw "SDL_CreateRenderer";

	// Create texture for renderer
	std::cout << "SDL_CreateTexture()" << std::endl;
	if (!(texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height)))
		throw "SDL_CreateTexture";

	// Initialize renderer color
	std::cout << "SDL_SetRenderDrawColor()" << std::endl;
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	fpsCounter = new SdlTextDisplay(2, 2, 60, 20);
	fpsCounter->setText("00 FPS");
	addWidget(fpsCounter, WL_NON_INTERACTIVE);

	std::cout << "SdlManager::launchWindow() - Finished" << std::endl;
}

////////

bool SdlManager::removeWidget(WidgetReference widget, int layer)
{
	unsigned long widgetCount = widgetList[layer].size();
	for(unsigned long widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
		if(widgetList[layer][widgetIndex] == widget)
		{
			widgetList[layer].erase(widgetList[layer].begin()+widgetIndex);
			return true;
		}
	return false;
}

bool SdlManager::removeWidget(WidgetReference widget)
{
	for(int layer = 0; layer < WL_COUNT; layer++)
		if(removeWidget(widget, layer))
			return true;
	return false;
}

////////

SubscriptionReference SdlManager::subscribeToEvent(void (*callback)(SDL_Event&), int type)
{
	return subscribeToEvent(callback, type, SDLK_UNKNOWN);
}

SubscriptionReference SdlManager::subscribeToEvent(void (*callback)(SDL_Event&), int type, int sym)
{
	SdlEventSubscriber * subscriber = new SdlEventSubscriber( callback, type, sym );
	subscriberList.push_back(subscriber);

	std::cout << "SdlManager::subscribeToEvent()" << std::endl;

	return subscriber;
}

////////
//  TEXT WIDGET METHODS
////////

WidgetReference SdlManager::createTextWidget(const char * text, int xPos, int yPos)
{
	SDL_Surface * surface = sdlUtility.createTextSurface(text);
	SDL_Rect rect = {xPos, yPos, surface->w, surface->h};

	SdlWidget * widget = new SdlWidget(surface, rect);
	addWidget(widget, WL_NON_INTERACTIVE);
	return widget;
}

TextDisplayReference SdlManager::createTextDisplay(std::string text, int xPos, int yPos)
{
	std::cout << "SdlManager::createTextDisplay()" << std::endl;

	int width = 256;
	int height = 32;

	SDL_Surface * surface = sdlUtility.createSurface(width, 4*height);

	SDL_Rect rect = sdlUtility.createRect(xPos, yPos, width, height);
	SdlTextDisplay * textDisplay = new SdlTextDisplay(surface, rect, text);
	addWidget(textDisplay, WL_NON_INTERACTIVE);

	std::cout << "SdlManager::createTextDisplay() finished" << std::endl;
	return textDisplay;
}

////////
//  IMAGE METHODS
////////

SDL_Texture * SdlManager::loadImage(const char * file)
{
	SDL_Texture * texture = 0;

	SDL_Surface * surface = IMG_Load(file);
	if( ! surface)
		throw "IMG_Load";

	texture = SDL_CreateTextureFromSurface( renderer, surface );

	if( ! texture)
		throw "SDL_CreateTextureFromSurface";

	SDL_FreeSurface(surface);

	return texture;
}

void SdlManager::renderImage(SDL_Texture *image, int xPos, int yPos, int width, int height)
{
	SDL_Rect boundingBox = {xPos, yPos, width, height};

	SDL_RenderCopy(renderer, image, NULL, &boundingBox);
}

void SdlManager::renderImage(SDL_Texture *image, int xPos, int yPos)
{
	int width, height;

	//Query the image to get its width and height to use
	SDL_QueryTexture(image, NULL, NULL, &width, &height);

	return renderImage(image, xPos, yPos, width, height);
}

////////
//  BUTTON WIDGET METHODS
////////

ButtonReference SdlManager::createButton(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, const char * labelText, int xPos, int yPos)
{
	return createButton(callback, background, labelText, xPos, yPos, 128, 32);
}
ButtonReference SdlManager::createButton(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, const char * text, int xPos, int yPos, int width, int height)
{
	SDL_Rect rect = sdlUtility.createRect(xPos, yPos, width, height);
	SdlButton * button = new SdlButton(text, rect, callback);
	addWidget(button, WL_INTERACTIVE);
	return button;
}

////////

SliderReference SdlManager::createSlider(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, int xPos, int yPos)
{
	return createSlider(callback, background, xPos, yPos, 256, 32);
}
SliderReference SdlManager::createSlider(void (*callback)(SDL_Event&, WidgetReference), SDL_Surface * background, int xPos, int yPos, int width, int height)
{
	std::cout << "SdlManager::createSlider()" << std::endl;


	SDL_Rect rect = sdlUtility.createRect(xPos, yPos, width, height);
	SdlSlider * slider = new SdlSlider(rect, callback);
	addWidget(slider, WL_INTERACTIVE);

	std::cout << "createSlider() finished" << std::endl;
	return slider;
}

////////
