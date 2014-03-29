
#include <iostream>

#include "sdl-utility.h"

SdlUtility sdlUtility;

////////

SdlUtility::SdlUtility()
{
	// Initialize Fonts
	std::cerr << "SdlUtility::SdlUtility() - TTF_Init()" << std::endl;
	if( TTF_Init() == -1 )
	{
		std::cerr << TTF_GetError() << std::endl;
		throw "TTF_Init()";
	}

	std::cerr << "SdlUtility::SdlUtility() - TTF_OpenFont()" << std::endl;
	font = TTF_OpenFont( "res/arial.ttf", 16 );
	if(!font)
		std::cerr << TTF_GetError() << std::endl;
	std::cerr << "SdlUtility::SdlUtility() finished." << std::endl;
}

SdlUtility::~SdlUtility()
{
	if(font)
		TTF_CloseFont(font);
	TTF_Quit();
}

////////

SDL_Rect SdlUtility::createRect(int x, int y, int w, int h)
{
	SDL_Rect rect = {x, y, w, h};
	return rect;
}

ImageReference SdlUtility::createSurface(int width, int height)
{
	SDL_Surface * result;
	unsigned int rmask, gmask, bmask, amask;

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

ImageReference SdlUtility::createTextSurface(const char * text)
{
	SDL_Color textColor = {0,0,0};
	if(!font) std::cerr << "No font!" << std::endl;
	SDL_Surface * surface = TTF_RenderText_Solid( font, text, textColor);
	return surface;
}

Uint32 SdlUtility::getColor(ImageReference image, Color color)
{
	switch(color)
	{
	case C_WHITE:   return SDL_MapRGBA(image->format, 255, 255, 255, 255); break;
	case C_GRAY:    return SDL_MapRGBA(image->format, 127, 127, 127, 255); break;
	case C_BLACK:   return SDL_MapRGBA(image->format,   0,   0,   0, 255); break;
	case C_RED:     return SDL_MapRGBA(image->format, 255,  31,  31, 255); break;
	case C_GREEN:   return SDL_MapRGBA(image->format,  31, 255,  31, 255); break;
	case C_BLUE:    return SDL_MapRGBA(image->format,  31,  31, 255, 255); break;
	case C_CYAN:    return SDL_MapRGBA(image->format,   0, 255, 255, 255); break;
	case C_MAGENTA: return SDL_MapRGBA(image->format, 255,   0, 255, 255); break;
	case C_YELLOW:  return SDL_MapRGBA(image->format, 255, 255,   0, 255); break;

	case C_BEIGE:   return SDL_MapRGBA(image->format, 255, 255, 191, 255); break;
	}
}

void SdlUtility::set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}

ImageReference SdlUtility::createCircle(Color color, int size)
{
	ImageReference image = createSurface(size+1,size+1);

	double cx = size / 2;
	double cy = size / 2;
	double radius = cx;
	Uint32 pixel = getColor(image, color);

	//  From:
	// http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles

	static const int BPP = 4;

	double r = (double)radius - 0.5;

	for (double dy = 1; dy <= r; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
		int x = cx - dx;

		Uint8 *target_pixel_a = (Uint8 *)image->pixels + ((int)(cy + r - dy)) * image->pitch + x * BPP;
		Uint8 *target_pixel_b = (Uint8 *)image->pixels + ((int)(cy - r + dy)) * image->pitch + x * BPP;

		for (; x <= cx + dx; x++)
		{
			*(Uint32 *)target_pixel_a = pixel;
			*(Uint32 *)target_pixel_b = pixel;
			target_pixel_a += BPP;
			target_pixel_b += BPP;
		}
	}

	pixel = getColor(image, C_BLACK);
	double error = (double)-radius;
	double x = (double)radius -0.5;
	double y = (double)0.5;
	cx -= 0.5;
	cy -= 0.5;

	while (x >= y)
	{
		set_pixel(image, (int)(cx + x), (int)(cy + y), pixel);
		set_pixel(image, (int)(cx + y), (int)(cy + x), pixel);

		if (x != 0)
		{
			set_pixel(image, (int)(cx - x), (int)(cy + y), pixel);
			set_pixel(image, (int)(cx + y), (int)(cy - x), pixel);
		}

		if (y != 0)
		{
			set_pixel(image, (int)(cx + x), (int)(cy - y), pixel);
			set_pixel(image, (int)(cx - y), (int)(cy + x), pixel);
		}

		if (x != 0 && y != 0)
		{
			set_pixel(image, (int)(cx - x), (int)(cy - y), pixel);
			set_pixel(image, (int)(cx - y), (int)(cy - x), pixel);
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}
	}

	return image;
}

ImageReference SdlUtility::createTriangle(Color color, int width, int height)
{
	ImageReference image = createSurface(width, height);;

	Uint32 inner = getColor(image, color);
	Uint32 outer = getColor(image, C_BLACK);

	double m = 2.0 * height / width;
	int mid = width/2;

	int y,x;

	for(y = 0; y < height; y++)
	{
		for(x = mid - y / m; x <= mid; x ++)
		{
			set_pixel(image, x, y, inner);
			set_pixel(image, width - x, y, inner);
		}


		set_pixel(image, mid - y / m, y, outer);
		set_pixel(image, width - mid + y / m + 1, y, outer);
	}
	for(x = 0; x <= mid; x ++)
	{
		set_pixel(image, x, height-1, outer);
		set_pixel(image, width - x, height-1, outer);
	}

	return image;
}
