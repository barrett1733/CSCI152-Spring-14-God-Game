
#ifndef SDL_WIDGET_H_
#define SDL_WIDGET_H_

#include <SDL2/SDL.h>

#include <iostream>

class SdlWidgetBase
{
protected:
	SDL_Surface * surface;
	SDL_Rect clipping;
	SDL_Rect boundingBox;

public:
	SdlWidgetBase(SDL_Surface * surface_arg, SDL_Rect & rect) :
		surface(surface_arg)
	{
		clipping = {0,0,0,0};
		boundingBox = {rect.x, rect.y, rect.w, rect.h};
	}

	virtual ~SdlWidgetBase() {

		if(surface) SDL_FreeSurface(surface);
		clipping = boundingBox = {0, 0, 0, 0};
	}

	SDL_Surface * getSurface() {return surface; }
	const SDL_Rect * getClipping() { return & clipping; }
	const SDL_Rect * getBoundingBox() { return & boundingBox; }

	virtual void handleEvent(SDL_Event&) = 0;
};

typedef SdlWidgetBase * WidgetBaseReference;

class SdlWidget : public SdlWidgetBase
{
public:
	SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect) :
		SdlWidgetBase(surface_arg, rect)
	{}
	void handleEvent(SDL_Event&) {}
};

typedef SdlWidget * WidgetReference;

#endif
