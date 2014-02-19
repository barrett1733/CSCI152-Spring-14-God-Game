
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
		throw SDL_GetError(); //std::cerr << "Init failed." << std::endl;

	SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1");
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1");

	// Initialize PNG loading
	std::cerr << "IMG_Init()" << std::endl;
	int imgFlags = IMG_INIT_PNG;
	if( ! ( IMG_Init( imgFlags ) & imgFlags ) )
		throw "IMG_Init";

	// Initialize Fonts
	std::cerr << "TTF_Init()" << std::endl;
	if( TTF_Init() == -1 )
		throw TTF_GetError();

	font = TTF_OpenFont( "res/arial.ttf", 16 );

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

	//Handle events on queue
	while(SDL_PollEvent(&event) != 0)
	{
		int subscriberCount = subscriberList.size();
		for(int subscriberIndex = 0; subscriberIndex < subscriberCount; subscriberIndex++)
			subscriberList[subscriberIndex]->handleEvent(event);

		for(widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
			widgetList[widgetIndex]->handleEvent(event);
	} // end event handler loop

	// Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );

	// Render everything
	for(widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
		renderWidget(widgetList[widgetIndex]);

	// Update screen
	SDL_RenderPresent( renderer );

	wait();
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

SDL_Surface * SdlManager::createSurface(int width, int height)
{
	SDL_Surface * result;
	unsigned long rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	result = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
	return result;
}

////////
//  TEXT WIDGET METHODS
////////

SDL_Surface * SdlManager::createTextSurface(const char * text)
{
	std::cout << "SdlManager::createTextSurface() starting" << std::endl;
	SDL_Color textColor = {0,0,0};
	std::cout << "SdlManager::createTextSurface() half way" << std::endl;
	if(!font) std::cout << "No font!" << std::endl;
	if(!text) std::cout << "No text!" << std::endl;
	if(!textColor) std::cout << "No color!" << std::endl;
	SDL_Surface * surface = TTF_RenderText_Solid( font, text, textColor);
	std::cout << "SdlManager::createTextSurface() finished" << std::endl;
	return surface;
}

WidgetReference SdlManager::createTextWidget(const char * text, int xPos, int yPos)
{
	SDL_Surface * surface = createTextSurface(text);
	SDL_Rect rect = {xPos, yPos, surface->w, surface->h};

	SdlWidget * widget = new SdlWidget(surface, rect);
	widgetList.push_back(widget);
	widgetCount = widgetList.size();
	return widget;
}

TextDisplayReference SdlManager::createTextDisplay(std::string text, int xPos, int yPos)
{
	std::cout << "SdlManager::createTextDisplay()" << std::endl;

	int width = 256;
	int height = 32;


	SDL_Surface * surface = createSurface(width, 4*height);

	SDL_Rect rect = makeRect(xPos, yPos, width, height);
	SdlTextDisplay * textDisplay = new SdlTextDisplay(surface, rect, text);
	widgetList.push_back(textDisplay);
	widgetCount = widgetList.size();

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
//  BASE WIDGET METHODS
////////

void SdlManager::renderWidget(SdlWidgetBase * widget)
{
	SDL_Surface * surface = widget->getSurface();
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, widget->getClipping(), widget->getBoundingBox());
	SDL_DestroyTexture(texture);
}

////////
//  BUTTON WIDGET METHODS
////////

ButtonReference SdlManager::createButton(void (*callback)(SDL_Event & event), SDL_Surface * background, const char * labelText, int xPos, int yPos)
{
	return createButton(callback, background, labelText, xPos, yPos, 128, 32);
}
ButtonReference SdlManager::createButton(void (*callback)(SDL_Event & event), SDL_Surface * background, const char * labelText, int xPos, int yPos, int width, int height)
{
	std::cout << "SdlManager::createButton() starting" << std::endl;

	SDL_Rect rect = {xPos, yPos, width, height};
	SDL_Rect clip;

	if(!background)
	{
		std::cout << "CreateButton(): Generating button images... ";
		background = createSurface(width, 4*height);
		SDL_FillRect(background, NULL, SDL_MapRGBA(background->format, 0, 0, 0, 255));

		SDL_Surface * buttonFill = createSurface(width, height);
		SDL_PixelFormat * pixelFormat = buttonFill->format;

		std::cout << "0/4";
		for(int i = 0; i < 4; i++)
		{
			int tone = 32 * (6-i);
			SDL_FillRect(buttonFill, NULL, SDL_MapRGBA(pixelFormat, tone, tone, tone, 255));
			rect = makeRect(1, 1,            width-2, height-2);
			clip = makeRect(1, 1 + i*height, width-2, height-2);
			SDL_BlitSurface(buttonFill, &rect, background, &clip);
			std::cout << "\b\b\b" << (i+1) << "/4";
		}
		SDL_FreeSurface(buttonFill);

		std::cout << " done." << std::endl;
	}

	SDL_Surface * textSurface = createTextSurface(labelText);

	int yPosText = (height - textSurface->h)/2;
	int xPosText = (width - textSurface->w)/2;
	if(xPosText < 8) xPosText = 8;

	std::cout << "CreateButton(): Writing text to button images... ";
	std::cout << "0/4";
	for(int i = 0; i < 4; i++)
	{
		rect = makeRect(xPosText, yPosText, width, height);
		clip = makeRect(xPosText, yPosText + i*height, width, height );
		SDL_BlitSurface(textSurface, NULL, background, &clip);
		std::cout << "\b\b\b" << (i+1) << "/4";
	}
	SDL_FreeSurface(textSurface);
	std::cout << " done." << std::endl;

	std::cout << "CreateButton(): Creating the button." << std::endl;
	rect = makeRect(xPos, yPos, width, height);
	SdlButton * button = new SdlButton(background, rect, callback);
	widgetList.push_back(button);
	widgetCount = widgetList.size();

	std::cout << "SdlManager::createButton() finished" << std::endl;
	return button;
}

void SdlManager::destroyButton(ButtonReference & buttonRef)
{
	for(widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
		if(widgetList[widgetIndex] == buttonRef)
			widgetList.erase(widgetList.begin()+widgetIndex);
	delete buttonRef;
	widgetCount = widgetList.size();
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
		background = createSurface(width*2 - handleWidth*2, height);
		SDL_FillRect(background, NULL, SDL_MapRGBA(background->format, 127, 127, 127, 255));

		SDL_Surface * handle = createSurface(handleWidth, height);
		SDL_FillRect(handle, NULL, SDL_MapRGBA(handle->format, 64, 64, 64, 255));

		SDL_Rect clip = makeRect(width - handleWidth, 0, handleWidth, height);
		SDL_BlitSurface(handle, NULL, background, &clip);
		SDL_FreeSurface(handle);
	}

	SDL_Rect rect = makeRect(xPos, yPos, width, height);
	SdlSlider * slider = new SdlSlider(background, rect, callback);
	widgetList.push_back(slider);
	widgetCount = widgetList.size();

	std::cout << "createSlider() finished" << std::endl;
	return slider;
}

////////
