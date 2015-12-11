//Controls entity related data

#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "entity.h"
#include "component.h"
#include "system.h"

static LIST_HEAD(component_head);

void entity_init(void)
{
}

uint32_t entity_new(void)
{
	static uint32_t entity_count = 0;
	return entity_count++;
}

int entity_add_component(uint32_t entity, const char* name)
{
	struct component_template* att = component_get_template(name);

	if(att)
	{
		struct component*at = (struct component*)system_alloc_component(att->alloc_id, att->size);
		list_add_tail(&at->list, &component_head);
		at->parent_id = entity;
		return 0;
	}

	//Component Not found
	return -1;
}

struct component* entity_search_component(uint32_t entity, const char* name)
{
	struct list_head *pos;
	int comp_type = component_get_type(name);

	list_for_each(pos, &component_head)
	{
		struct component *comp = container_of(pos, struct component, list);
		if(entity == comp->parent_id &&
				comp->type)
			return comp;

	}

	return 0;
}
