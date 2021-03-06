//
//  File: sdl-slider.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Slider Widget Implementation
//

#include "sdl-slider.h"

SdlSlider::SdlSlider(SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(0, rect, callback_arg),
	percent(0)
{
	liveCallback = callback;
	clipping.x = clipping.w - clipping.h / 2;
	surface = createSliderBackground();
}

SdlSlider::SdlSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(surface_arg, rect, callback_arg),
	percent(0)
{
	liveCallback = callback;
	clipping.x = clipping.w - clipping.h / 2;
}

SdlSlider::SdlSlider(SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference), void (*liveCallback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(0, rect, callback_arg),
	percent(0)
{
	liveCallback = liveCallback_arg;
	clipping.x = clipping.w - clipping.h / 2;
	surface = createSliderBackground();
}

SdlSlider::SdlSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference), void (*liveCallback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(surface_arg, rect, callback_arg),
	percent(0)
{
	liveCallback = liveCallback_arg;
	clipping.x = clipping.w - clipping.h / 2;
}

SdlSlider::~SdlSlider()
{
	percent = 0;
}

void SdlSlider::handleEvent(SDL_Event & event)
{
	updateState(event);

	if(state == WS_ACTIVE)
	{
		int xMouse, yMouse;
		SDL_GetMouseState( &xMouse, &yMouse );

		double previous = percent;
		int handleWidth = clipping.h / 2;

		percent = (xMouse - boundingBox.x)/(float)boundingBox.w;
		if(percent < 0) percent = 0;
		if(percent > 1) percent = 1;

		clipping.x = (clipping.w - handleWidth) * (1-percent);

		if(percent != previous && liveCallback)
			liveCallback(event, this);
	}

	if(state == WS_ON)
	{
		state = WS_OFF;
		if(callback)
			callback(event, this);
	}
}

/////

ImageReference SdlSlider::createSliderBackground()
{
	int width = boundingBox.w;
	int height = boundingBox.h;

	int handleWidth = height/2;

	ImageReference background = sdlUtility.createSurface(width*2 - handleWidth*2, height);
	SDL_FillRect(background, NULL, SDL_MapRGBA(background->format, 127, 127, 127, 255));

	SDL_Surface * handle = sdlUtility.createSurface(handleWidth, height);
	SDL_FillRect(handle, NULL, SDL_MapRGBA(handle->format, 64, 64, 64, 255));

	SDL_Rect rect = sdlUtility.createRect(width - handleWidth, 0, handleWidth, height);
	SDL_BlitSurface(handle, NULL, background, &rect);
	SDL_FreeSurface(handle);

	return background;
}
