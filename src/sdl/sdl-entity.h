//
//  File: sdl-entity.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Entity Widget Definition
// Extends the generic Widget Class.
// Provides the on-screen representation of a game entity.
// Requires a world size to be provided before instantiation.
// Requires a SdlMapView to be provided before instantiation.
// Rather than render to the renderer, this class blits onto the map.
//

#ifndef SDL_ENTITY_H_
#define SDL_ENTITY_H_

#include <iostream>

#include "sdl-widget.h"
#include "../entity.h"
#include "sdl-map-view.h"

class SdlEntity : public SdlWidget
{

	float size;
	float scale;
	const Entity * entity;

public:
	SdlEntity(const Entity&);

	void erase();
	void update();

	static int worldSize;
	static SdlMapView * mapView;
};

typedef SdlEntity * SdlEntityReference;

#endif
