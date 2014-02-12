
#include "sdl-manager.h"
#include <iostream>

SdlManager sdl;

SdlManager::SdlManager() :
	window(nullptr),
	renderer(nullptr)
{
	std::cerr << "SDL_Init()" << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw SDL_GetError(); //std::cerr << "Init failed." << std::endl;

	std::cerr << "Ready." << std::endl;
}

SdlManager::~SdlManager()
{
	std::cerr << "sdl.destructor()" << std::endl;

	if(renderer) SDL_DestroyRenderer(renderer);
	if(window)   SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();
}

void SdlManager::launchWindow(const char * title, int width, int height)
{
	std::cerr << "sdl.launchWindow() starting" << std::endl;

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

	// Initialize PNG loading
	std::cerr << "IMG_Init()" << std::endl;
	int imgFlags = IMG_INIT_PNG;
	if( ! ( IMG_Init( imgFlags ) & imgFlags ) )
		throw "IMG_Init";

	std::cerr << "sdl.launchWindow() finished" << std::endl;
}

SDL_Texture * SdlManager::loadTexture(const char * file)
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

void SdlManager::renderTexture(SDL_Texture *texture, int x, int y)
{
	std::cerr << "sdl.renderTexture() starting." << std::endl;
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	//Query the texture to get its width and height to use
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_RenderPresent(renderer);

	std::cerr << "sdl.renderTexture() finished." << std::endl;
}
