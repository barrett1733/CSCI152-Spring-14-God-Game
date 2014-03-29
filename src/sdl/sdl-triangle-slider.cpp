
#include <iostream>

#include "sdl-triangle-slider.h"

SdlTriangleSlider::SdlTriangleSlider(SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget()
{
	callback = callback_arg;

	int width  = rect.w;
	int height = rect.h;

	clipping.w = width;
	clipping.h = height;
	boundingBox.x = rect.x;
	boundingBox.y = rect.y;
	boundingBox.w = width;
	boundingBox.h = height;

	surface = sdlUtility.createSurface(width, height);
	background = createTriangleSliderBackground();
	handle = createTriangleSliderHandle();

	valueA = valueB = valueC = 1/3.0;
	renderTriangleSliderSurface();

	state = WS_OFF;
	liveCallback = callback;
}

SdlTriangleSlider::SdlTriangleSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(surface_arg, rect, callback_arg)
{
	liveCallback = callback;
}

SdlTriangleSlider::SdlTriangleSlider(SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference), void (*liveCallback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget()
{
	callback = callback_arg;

	int width  = rect.w;
	int height = rect.h;

	clipping.w = width;
	clipping.h = height;
	boundingBox.x = rect.x;
	boundingBox.y = rect.y;
	boundingBox.w = width;
	boundingBox.h = height;

	surface = sdlUtility.createSurface(width, height);
	background = createTriangleSliderBackground();
	handle = createTriangleSliderHandle();

	valueA = valueB = valueC = 1/3.0;
	renderTriangleSliderSurface();

	state = WS_OFF;

	liveCallback = liveCallback_arg;
}

SdlTriangleSlider::SdlTriangleSlider(SDL_Surface * surface_arg, SDL_Rect & rect, void (*callback_arg)(SDL_Event&, WidgetReference), void (*liveCallback_arg)(SDL_Event&, WidgetReference)) :
	SdlWidget(surface_arg, rect, callback_arg)
{
	liveCallback = liveCallback_arg;
}

SdlTriangleSlider::~SdlTriangleSlider()
{}

void SdlTriangleSlider::handleEvent(SDL_Event & event)
{
	updateState(event);

	if(state == WS_ACTIVE)
	{
		int width = boundingBox.w;
		int height = boundingBox.h;

		double mSlope = 2.0 * height / width;
		int mid = width / 2;

		int xA = width/2;
		int yA = 0;
		int xB = width;
		int yB = height;
		int xC = 0;
		int yC = height;

		double dx = width * 3.0 / 4.0;
		double dy = height / 2.0;
		double norm = sqrt(dx * dx + dy * dy);

		int xMouse, yMouse;
		SDL_GetMouseState( &xMouse, &yMouse );

		xMouse -= boundingBox.x;
		yMouse -= boundingBox.y;

		xMouse *= 1 + ((float)padding / boundingBox.w);
		yMouse *= 1 + (2.0 * padding / boundingBox.h);

		//  CALCULATE A
		valueA = 1 - (double)yMouse/height;
		if(valueA > 1) valueA = 1;
		if(valueA < 0) valueA = 0;

		//  CALCULATE B
		dx = xA - xC;
		dy = yA - yC;
		valueB = abs(dx*(yA-yMouse) - (xA-xMouse)*dy) / sqrt(dx*dx + dy*dy) / norm;
		if(xMouse < mid - yMouse / mSlope)
			valueB = 0;
		if(valueB > 1)
			valueB = 1;

		//  CALCULATE C
		dx = xA - xB;
		dy = yA - yB;
		valueC = abs(dx*(yA-yMouse) - (xA-xMouse)*dy) / sqrt(dx*dx + dy*dy) / norm;
		if(xMouse > mid + yMouse / mSlope)
			valueC = 0;
		if(valueC > 1)
			valueC = 1;

		double sum = valueA + valueB + valueC;
		valueA /= sum;
		valueB /= sum;
		valueC /= sum;

		renderTriangleSliderSurface();

		if(liveCallback)
			liveCallback(event, this);
	}

	if(state == WS_ON)
	{
		state = WS_OFF;
		if(callback)
			callback(event, this);
	}
}

/////

bool SdlTriangleSlider::isInside(int xMouse, int yMouse)
{
	bool inside = SdlWidget::isInside(xMouse, yMouse);
	if(inside)
	{
		int width = boundingBox.w;
		int height = boundingBox.h;
		double mSlope = 2.0 * height / width;
		int mid = width / 2;

		xMouse -= boundingBox.x;
		yMouse -= boundingBox.y;

		if(xMouse < mid - yMouse / mSlope)
			inside = false;

		if(xMouse > mid + yMouse / mSlope)
			inside = false;
	}

	return inside;
}

//////

ImageReference SdlTriangleSlider::createTriangleSliderBackground()
{
	int width = boundingBox.w - 2 * padding;
	int height = boundingBox.h - 2 * padding;

	ImageReference image = sdlUtility.createTriangle(C_GRAY, width, height);

	return image;
}

ImageReference SdlTriangleSlider::createTriangleSliderHandle()
{
	int size = padding * 2;
	ImageReference image = sdlUtility.createCircle(C_BLUE, size);

	return image;
}

void SdlTriangleSlider::renderTriangleSliderSurface()
{
	int width = boundingBox.w;
	int height = boundingBox.h;
	SDL_Rect clip;

	//surface = sdlUtility.createSurface(width, height);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));


	clip = sdlUtility.createRect(2,2,width-4,height-4);
	SDL_BlitSurface(background, NULL, surface, &clip);

	int xPos = (width - padding * 3)*(0.5 + valueB/2.0 - valueC/2.0);
	int yPos = (height - padding * 3) * (1 - valueA);

	clip = sdlUtility.createRect(xPos,yPos,16,16);
	SDL_BlitSurface(handle, NULL, surface, &clip);

}
