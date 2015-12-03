//Controls entity related data

#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "entity.h"
#include "component.h"

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
	struct list_head* pos;
	list_for_each(pos, &att_loader_head)
	{
		struct component_template* att = list_entry(pos, struct component_template, list);

		if(strncmp(name, att->name, 32) == 0)
		{
			struct component*at = (struct component*)system_alloc_component(att->alloc_id, att->size);
			list_add_tail(&at->list, &component_head);
			at->parent_id = entity;
			return 0;
		}
	}

	//Component Not found
	return -1;
}

