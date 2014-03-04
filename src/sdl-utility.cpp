
#include <iostream>

#include "sdl-utility.h"

SdlUtility sdlUtility;

////////

SdlUtility::SdlUtility()
{
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
}

SdlUtility::~SdlUtility()
{
	if(font)
		TTF_CloseFont(font);
	TTF_Quit();
}

////////

SDL_Rect SdlUtility::makeRect(int x, int y, int w, int h)
{
	SDL_Rect rect = {x, y, w, h};
	return rect;
}

SDL_Surface * SdlUtility::createSurface(int width, int height)
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

SDL_Surface * SdlUtility::createTextSurface(const char * text)
{
	SDL_Color textColor = {0,0,0};
	if(!font) std::cerr << "No font!" << std::endl;
	SDL_Surface * surface = TTF_RenderText_Solid( font, text, textColor);
	return surface;
}
