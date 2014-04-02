
#ifndef SDL_ENTITY_H_
#define SDL_ENTITY_H_

#include <iostream>

#include "sdl-widget.h"
#include "../entity.h"
#include "sdl-map-view.h"

class SdlEntity : public SdlWidget
{
	static SdlMapView * mapView;

	int size;
	const Entity * entity;

public:
	SdlEntity(const Entity&);

	void update();
	void updatePosition();

	const static SDL_Rect * mapRect;
	static int worldSize;
};

typedef SdlEntity * SdlEntityReference;

#endif
