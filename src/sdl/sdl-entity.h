
#ifndef SDL_ENTITY_H_
#define SDL_ENTITY_H_

#include <iostream>

#include "sdl-widget.h"
#include "../entity.h"
#include "sdl-map-view.h"

class SdlEntity : public SdlWidget
{

	int size;
	const Entity * entity;

public:
	SdlEntity(const Entity&);

	void update();
	void updatePosition();

	static int worldSize;
	static SdlMapView * mapView;
};

typedef SdlEntity * SdlEntityReference;

#endif
