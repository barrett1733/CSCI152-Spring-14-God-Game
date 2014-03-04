
#ifndef SDL_UTILITY_H_
#define SDL_UTILITY_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

typedef SDL_Surface * ImageReference;

enum COLOR {
	C_WHITE,
	C_GRAY,
	C_BLACK,
	C_RED,
	C_GREEN,
	C_BLUE,
	C_CYAN,
	C_MAGENTA,
	C_YELLOW,
};

class SdlUtility
{
	TTF_Font * font;
public:
	SdlUtility();
	~SdlUtility();

	SDL_Rect makeRect(int x, int y, int w, int h);

	SDL_Surface * createSurface(int width, int height);
	SDL_Surface * createTextSurface(const char * text);
	Uint32 getColor(ImageReference image, COLOR color);
};

#endif

extern SdlUtility sdlUtility;
