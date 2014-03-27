
#include <iostream>

#include "sdl-entity.h"

SdlEntity::SdlEntity()
{
	std::cout << "SdlEntity::SdlEntity()" << std::endl;
	int size = 16;
	Color color = C_RED;

	surface = sdlUtility.createCircle(color, size);

	clipping.w = size;
	clipping.h = size;
	boundingBox.w = size;
	boundingBox.h = size;
}

SdlEntity::SdlEntity(const Entity & entity)
{
	std::cout << "SdlEntity::SdlEntity(const Entity&)" << std::endl;
	int size = 16;
	Color color = C_MAGENTA;

	surface = sdlUtility.createCircle(color, size);

	clipping.w = size;
	clipping.h = size;
	boundingBox.w = size;
	boundingBox.h = size;
}

SdlEntity::SdlEntity(Color color, int size) :
	SdlWidget(WL_NON_INTERACTIVE)
{
	surface = sdlUtility.createCircle(color, size);

	clipping.w = size;
	clipping.h = size;
	boundingBox.w = size;
	boundingBox.h = size;

	std::cout << "SDL Entity created." << std::endl;
}
