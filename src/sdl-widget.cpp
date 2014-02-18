
#include "sdl-widget.h"

SdlWidgetBase::SdlWidgetBase(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event)) :
	callback(callback_arg),
	surface(surface_arg),
	state(WIDGET_OFF)
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

SdlWidgetBase::~SdlWidgetBase() {

	if(surface) SDL_FreeSurface(surface);
	clipping.x = 0;
	clipping.y = 0;
	clipping.w = 0;
	clipping.h = 0;
	boundingBox.x = 0;
	boundingBox.y = 0;
	boundingBox.w = 0;
	boundingBox.h = 0;
	state = WIDGET_OFF;
	callback = 0;
}

SDL_Surface * SdlWidgetBase::getSurface()
{
	return surface;
}

const SDL_Rect * SdlWidgetBase::getClipping()
{
	return & clipping;
}

const SDL_Rect * SdlWidgetBase::getBoundingBox()
{
	return & boundingBox;
}

void SdlWidgetBase::updateState(SDL_Event & event)
{
	if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int xMouse, yMouse;
		SDL_GetMouseState( &xMouse, &yMouse );

		//Check if mouse is in boundary
		bool inside = isInside(xMouse, yMouse);

		//Set mouse over sprite
		switch( event.type )
		{
		case SDL_MOUSEMOTION:
			if(inside && state == WIDGET_OFF)
				state = WIDGET_HOVER;
			else if(!inside && state != WIDGET_ACTIVE)
				state = WIDGET_OFF;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(inside)
				state = WIDGET_ACTIVE;
			break;

		case SDL_MOUSEBUTTONUP:
			if(inside && state == WIDGET_ACTIVE)
				state = WIDGET_ON;
			else if(!inside)
				state = WIDGET_OFF;
			break;
		}
	}
}

bool SdlWidgetBase::isInside(int xMouse, int yMouse)
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
