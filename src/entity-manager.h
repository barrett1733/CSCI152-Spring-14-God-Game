
#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <vector>

#include "sdl/sdl-entity.h"
#include "entity.h"

struct EM_Record
{
	Entity * entity;
	WidgetReference widget;
};

class EntityManager
{
	std::vector<WidgetReference> widgetList;

public:
	void createEntity();

	void update();
	void show();
	void hide();
};

#endif
