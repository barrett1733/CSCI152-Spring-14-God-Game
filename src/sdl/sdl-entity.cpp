
#include <iostream>

#include "sdl-entity.h"

SdlEntity::SdlEntity(COLOR color, int width, int height) : SdlWidget()
{
	surface = sdlUtility.createCircle(color, width);

	clipping.w = width;
	clipping.h = height;
	boundingBox.w = width;
	boundingBox.h = height;

	std::cout << "SDL Entity created." << std::endl;
}
