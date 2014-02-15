
#ifndef SDL_WIDGET_H_
#define SDL_WIDGET_H_

#include <SDL2/SDL.h>

#include <iostream>

class SdlWidget
{
protected:
	SDL_Surface * surface;
	SDL_Rect clipping;
	SDL_Rect boundingBox;

public:
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect) :
		surface(surface_arg)
	{
		clipping = {0,0,0,0};
		boundingBox = {rect.x, rect.y, rect.w, rect.h};
	}

	virtual ~SdlWidget() {

		if(surface) SDL_FreeSurface(surface);
		clipping = boundingBox = {0, 0, 0, 0};
	}

	SDL_Surface * getSurface() {return surface; }
	const SDL_Rect * getClipping() { return & clipping; }
	const SDL_Rect * getBoundingBox() { return & boundingBox; }

	virtual void handleEvent(SDL_Event&) = 0;
};

#endif
