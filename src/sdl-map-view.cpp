
#include "sdl-map-view.h"

// SdlMapView::SdlMapView(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event)) :
// 	SdlWidget(surface_arg, rect, callback_arg)
// {}

// SdlMapView::SdlMapView(const char * text, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event)) :
// 	SdlWidget(0, rect, callback_arg)
// {
// 	surface = createBackground(rect);
// }

SdlMapView::SdlMapView(int xPos, int yPos, int width, int height) :
	SdlWidget()
{
	clipping = sdlUtility.createRect(xPos, yPos, width, height);
	boundingBox = sdlUtility.createRect(xPos, yPos, width, height);
	surface = createBackground(clipping);
}

SdlMapView::~SdlMapView()
{}

void SdlMapView::handleEvent(SDL_Event & event)
{
	updateState(event);

	if(state == WIDGET_ON)
	{
		if(callback)
			callback(event);
		state = WIDGET_OFF;
	}

	// Update button appearance for button state
	clipping.y = boundingBox.h * state;
}

ImageReference SdlMapView::createBackground(SDL_Rect & rect)
{
	int width = rect.w;
	int height = rect.h;

	ImageReference image = sdlUtility.createSurface(width, 5 * height);
	SDL_FillRect(image, NULL, sdlUtility.getColor(image,C_BEIGE));


	return image;
}

