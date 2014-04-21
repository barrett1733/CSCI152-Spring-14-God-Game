
#ifndef SDL_MAP_VIEW_H_
#define SDL_MAP_VIEW_H_

#include "sdl-widget.h"

class SdlMapView : public SdlWidget
{
	static ImageReference clearSurface;
	ImageReference createBackground(SDL_Rect & rect);

public:
	SdlMapView();
	SdlMapView(int xPos, int yPos, int width, int height);
	~SdlMapView();

	void clear(SDL_Rect&);
	void draw(ImageReference, SDL_Rect&);
};

typedef SdlMapView * MapViewReference;

#endif
