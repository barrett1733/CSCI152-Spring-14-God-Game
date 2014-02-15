
#include "sdl-manager.h"
#include <iostream>

SdlManager sdl;

SdlManager::SdlManager() :
	window(nullptr),
	renderer(nullptr),
	font(nullptr)
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

bool SdlManager::update()
{
	bool running = true;
	SDL_Event event;

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
					// case SDLK_UP: yVel -= velocityIncrement; break;
					// case SDLK_DOWN: yVel += velocityIncrement; break;
					// case SDLK_LEFT: xVel -= velocityIncrement; break;
					// case SDLK_RIGHT: xVel += velocityIncrement; break;
					case '\e' : running = false;; break;

					default: std::cout << event.key.keysym.sym << std::endl; break;
				}
				break;

			case SDL_QUIT:
				running = false;
				break;
		}
	} // end event handler loop

	// Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );

	// Render everything
	for(widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
		renderWidget(widgetList[widgetIndex]);//widgetList[widgetIndex]->render(renderer);

	// Update screen
	SDL_RenderPresent( renderer );

	wait();
	return running;
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

////////

SDL_Surface * SdlManager::createTextSurface(const char * text)
{
	SDL_Color textColor = {0,0,0};
	SDL_Surface * surface = TTF_RenderText_Solid( font, text, textColor);
	return surface;
}

WidgetReference SdlManager::createTextWidget(const char * text, int xPos, int yPos)
{
	SDL_Surface * surface = createTextSurface(text);
	SDL_Rect rect = {xPos, yPos, surface->w, surface->h};

	SdlWidget * widget = new SdlWidget(surface, rect);
	widgetList.push_back(widget);
	return widget;
}

////////

SDL_Texture * SdlManager::loadImage(const char * file)
{
	SDL_Texture * texture = nullptr;

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

void SdlManager::renderWidget(SdlWidgetBase * widget)
{
	SDL_Surface * surface = widget->getSurface();
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, widget->getBoundingBox());
	SDL_DestroyTexture(texture);
}

////////

ButtonReference SdlManager::createButton(void (*callback)(), SDL_Surface * background, const char * labelText, int xPos, int yPos, int width, int height)
{
	SDL_Rect rect = {xPos, yPos, width, height};

	if(!background)
	{
		background = createSurface(width, height);
		SDL_FillRect(background, NULL, 0xFF000000);

		SDL_Surface * buttonFill = createSurface(width, height);
		SDL_FillRect(buttonFill, NULL, SDL_MapRGBA(buttonFill->format, 127, 127, 127, 255));
		rect = {1,1,width-2, height-2};
		SDL_BlitSurface(buttonFill, &rect, background, &rect);
		SDL_FreeSurface(buttonFill);
	}

	SDL_Surface * textSurface = createTextSurface(labelText);

	rect = {(width - textSurface->w)/2, (height - textSurface->h)/2, width, height };
	if(rect.x < 8) rect.x = 8;

	SDL_BlitSurface(textSurface, NULL, background, &rect);
	SDL_FreeSurface(textSurface);

	rect = {xPos, yPos, width, height};
	SdlButton * button = new SdlButton(background, rect, callback);
	widgetList.push_back(button);

	std::cout << "createButton() finished" << std::endl;
	return button;
}

void SdlManager::destroyButton(ButtonReference & buttonRef)
{
	for(widgetIndex = 0; widgetIndex < widgetCount; ++widgetIndex)
		if(widgetList[widgetIndex] == buttonRef)
			widgetList.erase(widgetList.begin()+widgetIndex);
	delete buttonRef;
}

////////

void testCallback()
{
	std::cout << "Callback!" << std::endl;
}
