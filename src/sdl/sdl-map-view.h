//
//  File: sdl-map-view.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Map View Widget Definition
// Extends the generic Widget Class.
// Provides the on-screen representation of the game world.
// SDL Entity Widgets are blitted onto this.
//

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
