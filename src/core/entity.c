//Controls entity related data

#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "entity.h"
#include "component.h"
#include "system.h"


void entity_init(void)
{
}

int entity_new(void)
{
	static int entity_count = 0;
	return entity_count++;
}

int entity_add_component(int entity, const char* name)
{
	struct component*at = component_new(name);
	if(at)
	{
		at->parent_id = entity;
		return at->uid;
	}
   
	//Component Not found
	return -1;
}

int entity_search_component(int entity, const char* name)
{
	struct list_head *pos;
    int comp_type = component_get_type(name);

	list_for_each(pos, &component_head)
	{
		struct component *comp = container_of(pos, struct component, list);
		if(entity == comp->parent_id &&
				comp->type)
			return comp->uid;

	}

	return -1;
}
