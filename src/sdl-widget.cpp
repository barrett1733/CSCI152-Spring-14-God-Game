
#include "sdl-widget.h"

SdlWidget::SdlWidget() :
	callback(0),
	surface(0),
	state(WIDGET_DISABLED)
{
	clipping.x = 0;
	clipping.y = 0;
	clipping.w = 0;
	clipping.h = 0;
	boundingBox.x = 0;
	boundingBox.y = 0;
	boundingBox.w = 0;
	boundingBox.h = 0;
}

SdlWidget::SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect) :
	callback(0),
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

SdlWidget::SdlWidget(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, SdlWidget*)) :
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

SdlWidget::~SdlWidget() {

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

bool SdlWidget::isInside(int xMouse, int yMouse)
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

SDL_Surface * SdlWidget::getSurface()
{
	if(state == WIDGET_HIDDEN)
		return 0;
	return surface;
}

const SDL_Rect * SdlWidget::getClipping()
{
	return & clipping;
}

const SDL_Rect * SdlWidget::getBoundingBox()
{
	return & boundingBox;
}

void SdlWidget::updateState(SDL_Event & event)
{
	if(state == WIDGET_DISABLED || state == WIDGET_HIDDEN)
		return;

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

void SdlWidget::handleEvent(SDL_Event & event)
{
	updateState(event);
}

WidgetState SdlWidget::getState()
{
	return state;
}

void SdlWidget::enable()
{
	state = WIDGET_OFF;
}

void SdlWidget::disable()
{
	state = WIDGET_DISABLED;
}

void SdlWidget::show()
{
	state = WIDGET_OFF;
}

void SdlWidget::hide()
{
	state = WIDGET_HIDDEN;
}
