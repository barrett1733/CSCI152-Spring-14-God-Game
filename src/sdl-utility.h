
#ifndef SDL_UTILITY_H_
#define SDL_UTILITY_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

typedef SDL_Surface * ImageReference;

class SdlUtility
{
	TTF_Font * font;
public:
	SdlUtility();
	~SdlUtility();

	SDL_Rect makeRect(int x, int y, int w, int h);

	SDL_Surface * createSurface(int width, int height);
	SDL_Surface * createTextSurface(const char * text);
};

#endif

extern SdlUtility sdlUtility;
