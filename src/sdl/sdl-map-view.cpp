
#include "sdl-map-view.h"

ImageReference SdlMapView::clearSurface = sdlUtility.createSurface(2, 2, C_BEIGE);

SdlMapView::SdlMapView() :
	SdlWidget(WL_BACKGROUND)
{
	clipping = sdlUtility.createRect(0, 0, 600, 600);
	boundingBox = sdlUtility.createRect(200, 0, 600, 600);
	surface = createBackground(clipping);
}

SdlMapView::SdlMapView(int xPos, int yPos, int width, int height) :
	SdlWidget(WL_BACKGROUND)
{
	clipping = sdlUtility.createRect(xPos, yPos, width, height);
	boundingBox = sdlUtility.createRect(xPos, yPos, width, height);
	surface = createBackground(clipping);
}

SdlMapView::~SdlMapView()
{}

ImageReference SdlMapView::createBackground(SDL_Rect & rect)
{

	ImageReference image = sdlUtility.createSurface(rect.w, rect.h, C_BEIGE);

	return image;
}


void SdlMapView::clear(SDL_Rect & rect)
{
	SDL_Rect clip = sdlUtility.createRect(0, 0, rect.w - 1, rect.h - 1);
	SDL_BlitSurface(clearSurface, &clip, surface, &rect);

	if(texture) SDL_DestroyTexture(texture);
	texture = 0;
}

void SdlMapView::draw(ImageReference entitySurface, SDL_Rect & rect)
{
	SDL_BlitSurface(entitySurface, NULL, surface, &rect);

	if(texture) SDL_DestroyTexture(texture);
	texture = 0;
}
