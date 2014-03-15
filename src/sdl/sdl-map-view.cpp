
#include "sdl-map-view.h"

SdlMapView::SdlMapView(int xPos, int yPos, int width, int height) :
	SdlWidget()
{
	clipping = sdlUtility.createRect(xPos, yPos, width, height);
	boundingBox = sdlUtility.createRect(xPos, yPos, width, height);
	surface = createBackground(clipping);
}

SdlMapView::~SdlMapView()
{}

ImageReference SdlMapView::createBackground(SDL_Rect & rect)
{
	int width = rect.w;
	int height = rect.h;

	ImageReference image = sdlUtility.createSurface(width, height);
	SDL_FillRect(image, NULL, sdlUtility.getColor(image,C_BEIGE));

	return image;
}

