
#ifndef SDL_MAP_VIEW_H_
#define SDL_MAP_VIEW_H_

#include "sdl-widget.h"

class SdlMapView : public SdlWidget
{
	ImageReference createBackground(SDL_Rect & rect);

public:
	SdlMapView(int xPos, int yPos, int width, int height);
	~SdlMapView();
};

typedef SdlMapView * MapViewReference;

#endif
