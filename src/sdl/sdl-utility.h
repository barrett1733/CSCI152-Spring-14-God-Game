//
//  File: sdl-utility.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Utility Definition
// Provides a host of utility function:
// : createRect() returns an SDL_Rect of the specified dimentions.
// : createSurface() returns a rectangle of the specified size and optional color filled.
// : createTextSurface() returns a surface initialized with text characteristics.
// : createCircle() returns a circular surface of the specified size with specified color filled.
// : createTriangle() returns a triangular (isoceles, pointing up) surface.
//

#ifndef SDL_UTILITY_H_
#define SDL_UTILITY_H_

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <map>
#include <vector>

typedef SDL_Surface * ImageReference;
typedef int FontSize;

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

enum SdlSurfaceType
{
	ST_DEFAULT,
	ST_TEXT,
	ST_CIRCLE,
	ST_SQUARE,
	ST_TRIANGLE
};

class SdlUtility
{
	struct SurfaceData
	{
		int width = 0, height = 0;
		SdlSurfaceType type = ST_DEFAULT;
		Color color = C_WHITE;
		ImageReference surface = NULL;
		SurfaceData(int w, int h, Color c, SdlSurfaceType t, ImageReference s) :
			width(w),
			height(h),
			color(c),
			type(t),
			surface(s)
		{ }
		bool const operator==(const SurfaceData& sd) const
		{
			if (sd.width == width &&
				sd.height == height &&
				sd.color == color &&
				sd.type == type)
				return true;
			return false;
		}
	};
	TTF_Font * font;

	std::map<int, TTF_Font*> fontList;
	std::vector<SurfaceData> surfaces;
	ImageReference checkExistingSurfaces(int w, int h, Color c, SdlSurfaceType t);

	void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
	void loadFont(std::string fontName, FontSize fontSize);


public:
	SdlUtility();
	~SdlUtility();

	SDL_Rect createRect(int x, int y, int w, int h);

	Uint32 getColor(ImageReference image, Color color);

	ImageReference createSurface(int width, int height);
	ImageReference createSurface(int width, int height, Color);
	ImageReference createTextSurface(const char * text, FontSize fontSize);
	ImageReference createTextSurface(const char * text);
	ImageReference createCircle(Color, int size);
	ImageReference createSquare(Color, int size);
	ImageReference createTriangle(Color, int size);
	ImageReference createTriangle(Color, int width, int height);
};

#endif

extern SdlUtility sdlUtility;
