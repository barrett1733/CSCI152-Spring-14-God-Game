
#ifndef SDL_UTILITY_H_
#define SDL_UTILITY_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <map>

typedef SDL_Surface * ImageReference;

enum Color {
	C_WHITE,
	C_GRAY,
	C_BLACK,
	C_RED,
	C_GREEN,
	C_BLUE,
	C_CYAN,
	C_MAGENTA,
	C_YELLOW,

	C_BEIGE,
};

class SdlUtility
{
	TTF_Font * font;

	std::map<int, TTF_Font*> fontList;

	void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
	void loadFont(std::string fontName, int size);

public:
	SdlUtility();
	~SdlUtility();

	SDL_Rect createRect(int x, int y, int w, int h);

	Uint32 getColor(ImageReference image, Color color);

	ImageReference createSurface(int width, int height);
	ImageReference createSurface(int width, int height, Color);
	ImageReference createTextSurface(const char * text, int fontSize);
	ImageReference createTextSurface(const char * text);
	ImageReference createCircle(Color, int size);
	ImageReference createTriangle(Color, int width, int height);
};

#endif

extern SdlUtility sdlUtility;
