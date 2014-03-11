
#include "sdl-manager.h"
#include <iostream>

SdlManager sdl;

SdlManager::SdlManager() :
	window(0),
	renderer(0),
	font(0)
{

	std::cerr << "SDL_Init()" << std::endl;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		throw "SDL_Init()";
	}

	SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1");
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1");

	// Initialize PNG loading
	std::cerr << "IMG_Init()" << std::endl;
	int imgFlags = IMG_INIT_PNG;
	if( ! ( IMG_Init( imgFlags ) & imgFlags ) )
	{
		std::cerr << SDL_GetError() << std::endl;
		throw "IMG_Init()";
	}

	// Initialize Fonts
	std::cerr << "TTF_Init()" << std::endl;
	if( TTF_Init() == -1 )
	{
		std::cerr << TTF_GetError() << std::endl;
		throw "TTF_Init()";
	}

	font = TTF_OpenFont( "res/arial.ttf", 16 );
	if(!font)
		std::cerr << TTF_GetError() << std::endl;

	std::cerr << "Ready." << std::endl;
}

SdlManager::~SdlManager()
{
	std::cerr << "sdl.destructor()" << std::endl;

	if(renderer) SDL_DestroyRenderer(renderer);
	if(window)   SDL_DestroyWindow(window);
	if(font)     TTF_CloseFont(font);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

////////

void SdlManager::update()
{
	SDL_Event event;

	int subscriberCount = subscriberList.size();

	//Handle events on queue
	while(SDL_PollEvent(&event) != 0)
	{
		for(int subscriberIndex = 0; subscriberIndex < subscriberCount; subscriberIndex++)
			subscriberList[subscriberIndex]->handleEvent(event);

		for(int widgetIndex = 0; widgetIndex < widgetCount[WL_INTERACTIVE]; ++widgetIndex)
			widgetList[WL_INTERACTIVE][widgetIndex]->handleEvent(event);
	} // end event handler loop

	// Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );

	// Render everything
	for(int layerIndex = 0; layerIndex < WL_COUNT; layerIndex ++)
		for(int widgetIndex = 0; widgetIndex < widgetCount[layerIndex]; ++widgetIndex)
			renderWidget(widgetList[layerIndex][widgetIndex]);

	// Update screen
	SDL_RenderPresent( renderer );

	wait();
}

void SdlManager::renderWidget(SdlWidget * widget)
{
	SDL_Surface * surface = widget->getSurface();
	if(!surface) return;
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	const SDL_Rect * rect = widget->getBoundingBox();
	if(rect->w == 0 || rect->h == 0) return;
	SDL_RenderCopy(renderer, texture, widget->getClipping(), rect);
	SDL_DestroyTexture(texture);
}

void SdlManager::wait()
{
	unsigned long now = SDL_GetTicks();
	unsigned long time_left = 0;
	if(next_time > now)
		time_left = next_time - now;
	else
		next_time = now;
	if(time_left > TICK_INTERVAL) time_left = TICK_INTERVAL;
	SDL_Delay(time_left);
	next_time += TICK_INTERVAL;
}

////////

void SdlManager::launchWindow(const char * title, int width, int height)
{
	if(window) throw "Window exists.";

	std::cerr << "sdl.launchWindow() starting" << std::endl;

	next_time = 0;

	// Create window
	std::cerr << "SDL_CreateWindow()" << std::endl;
	if ( ! ( window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN) ) )
		throw "SDL_CreateWindow";

	// Create renderer for window
	std::cerr << "SDL_CreateRenderer()" << std::endl;
	if ( ! ( renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ) ) )
		throw "SDL_CreateRenderer";

	// Initialize renderer color
	std::cerr << "SDL_SetRenderDrawColor()" << std::endl;
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	std::cerr << "sdl.launchWindow() finished" << std::endl;
}

////////

SubscriptionReference SdlManager::subscribeToEvent(void (*callback)(SDL_Event & event), int type)
{
	return subscribeToEvent(callback, type, SDLK_UNKNOWN);
}

SubscriptionReference SdlManager::subscribeToEvent(void (*callback)(SDL_Event & event), int type, int sym)
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

ButtonReference SdlManager::createButton(void (*callback)(SDL_Event & event), SDL_Surface * background, const char * labelText, int xPos, int yPos)
{
	return createButton(callback, background, labelText, xPos, yPos, 128, 32);
}
ButtonReference SdlManager::createButton(void (*callback)(SDL_Event & event), SDL_Surface * background, const char * text, int xPos, int yPos, int width, int height)
{
	SDL_Rect rect = sdlUtility.createRect(xPos, yPos, width, height);
	SdlButton * button = new SdlButton(text, rect, callback);
	addWidget(button, WL_INTERACTIVE);
	return button;
}

void SdlManager::destroyButton(ButtonReference & buttonRef)
{
	int widgetCount = widgetList[WL_INTERACTIVE].size();
	for(int widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
		if(widgetList[WL_INTERACTIVE][widgetIndex] == buttonRef)
			widgetList[WL_INTERACTIVE].erase(widgetList[WL_INTERACTIVE].begin()+widgetIndex);
	delete buttonRef;
}

////////

SliderReference SdlManager::createSlider(void (*callback)(SDL_Event & event), SDL_Surface * background, int xPos, int yPos)
{
	return createSlider(callback, background, xPos, yPos, 256, 32);
}
SliderReference SdlManager::createSlider(void (*callback)(SDL_Event & event), SDL_Surface * background, int xPos, int yPos, int width, int height)
{
	std::cout << "SdlManager::createSlider()" << std::endl;

	int handleWidth = height/2;

	if(!background)
	{
		background = sdlUtility.createSurface(width*2 - handleWidth*2, height);
		SDL_FillRect(background, NULL, SDL_MapRGBA(background->format, 127, 127, 127, 255));

		SDL_Surface * handle = sdlUtility.createSurface(handleWidth, height);
		SDL_FillRect(handle, NULL, SDL_MapRGBA(handle->format, 64, 64, 64, 255));

		SDL_Rect clip = sdlUtility.createRect(width - handleWidth, 0, handleWidth, height);
		SDL_BlitSurface(handle, NULL, background, &clip);
		SDL_FreeSurface(handle);
	}

	SDL_Rect rect = sdlUtility.createRect(xPos, yPos, width, height);
	SdlSlider * slider = new SdlSlider(background, rect, callback);
	addWidget(slider, WL_INTERACTIVE);

	std::cout << "createSlider() finished" << std::endl;
	return slider;
}

////////
