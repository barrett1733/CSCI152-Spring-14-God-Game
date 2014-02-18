
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

	bool isInside(int xMouse, int yMouse)
	{
		bool inside = true;

		//Mouse is left of the button
		if( xMouse < boundingBox.x )
			inside = false;

		//Mouse is right of the button
		else if( xMouse > boundingBox.x + boundingBox.w )
			inside = false;

		//Mouse above the button
		else if( yMouse < boundingBox.y )
			inside = false;

		//Mouse below the button
		else if( yMouse > boundingBox.y + boundingBox.h )
			inside = false;

		return inside;
	}
public:
	SdlWidgetBase(SDL_Surface * surface_arg, SDL_Rect & rect) :
		surface(surface_arg)
	{
		clipping.x = 0;
		clipping.y = 0;
		clipping.w = rect.w;
		clipping.h = rect.h;
		boundingBox.x = rect.x;
		boundingBox.y = rect.y;
		boundingBox.w = rect.w;
		boundingBox.h = rect.h;
	}

	virtual ~SdlWidgetBase() {

		if(surface) SDL_FreeSurface(surface);
		clipping.x = 0;
		clipping.y = 0;
		clipping.w = 0;
		clipping.h = 0;
		boundingBox.x = 0;
		boundingBox.y = 0;
		boundingBox.w = 0;
		boundingBox.h = 0;
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
