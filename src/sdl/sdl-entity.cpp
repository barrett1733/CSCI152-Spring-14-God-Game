//
//  File: sdl-entity.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  SDL Entity Widget Implementation
//

#include <iostream>

#include "sdl-entity.h"

SdlMapView * SdlEntity::mapView = 0;
int SdlEntity::worldSize = 0;

SdlEntity::SdlEntity(const Entity & entity) :
	SdlWidget(WL_NON_INTERACTIVE),
	entity(&entity)
{
	size = mapView->getBoundingBox()->w / float(worldSize);
	scale = 1.0;

	Color color;
	switch(entity.getFaction())
	{
		case F_RESOURCE:
			switch(entity.getType())
			{
			case ET_TREE:
				color = C_GREEN;
				break;
			case ET_STONE:
				color = C_GRAY;
				break;
			case ET_IRON:
				color = C_BLACK;
				break;

			default:
				color = C_GRAY;
				break;
			}
			break;

		case F_ANIMAL_DOMESTIC:
			color = C_CYAN;
			break;

		case F_ANIMAL_PASSIVE:
			color = C_YELLOW;
			break;

		case F_ANIMAL_HOSTILE:
			color = C_MAGENTA;
			break;

		case F_PLAYER_1:
			color = C_BLUE;
			break;

		case F_PLAYER_2:
			color = C_RED;
			break;

		default:
			color = C_BLACK;
			break;
	}

	switch(entity.getGroup())
	{
		case EG_RESOURCE:
			surface = sdlUtility.createTriangle(color, size * scale);
			break;

		case EG_BUILDING:
			surface = sdlUtility.createSquare(color, size * scale);
			break;

		case EG_MIRACLE:
			color = C_RED;
			scale = 2.0;
			surface = sdlUtility.createCircle(color, size * scale);
			break;

		default:
			surface = sdlUtility.createCircle(color, size * scale);
			break;
	}


	clipping.x = 0;
	clipping.y = 0;
	clipping.w = size * scale;
	clipping.h = size * scale;
	boundingBox.w = size * scale;
	boundingBox.h = size * scale;

	erase();

	state = WS_HIDDEN;
}

void SdlEntity::erase()
{
	mapView->clear(boundingBox);
	boundingBox.x = (entity->getPosition().getX() - (scale - 1)/2) * size;
	boundingBox.y = (entity->getPosition().getY() - (scale - 1)/2) * size;
}


void SdlEntity::update()
{
	mapView->draw(surface, boundingBox);
}
