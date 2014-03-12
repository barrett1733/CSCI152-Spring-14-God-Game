
#ifndef SDL_MAP_VIEW_H_
#define SDL_MAP_VIEW_H_

#include "sdl-widget.h"

class SdlMapView : public SdlWidget
{
	ImageReference createBackground(SDL_Rect & rect);

public:
	// SdlMapView(SDL_Surface * surface, SDL_Rect & rect, void (*callback_arg)(SDL_Event & event));
	// SdlMapView(const char * text, SDL_Rect & rect, void (*)(SDL_Event&));
	SdlMapView(int xPos, int yPos, int width, int height);
	~SdlMapView();

	void handleEvent(SDL_Event & event);
};

typedef SdlMapView * MapViewReference;

#endif
