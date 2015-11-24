//Controls entity related data

#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "entity.h"

#define MAX_ATTR_LOADER	32

struct component_template {
	uint32_t size;
	struct list_head list;
	uint32_t type;
	char name[32];
} ;

static LIST_HEAD(component_head);
static LIST_HEAD(att_loader_head);


static int component_new(void)
{
	static uint32_t componentype = 1;

	return componentype++;
}

int component_register(const char* type, uint32_t size)
{
	struct component_template* att = (struct component_template*)malloc(sizeof(struct component_template));

	strncpy(att->name, type, sizeof(att->name));
	att->size = size;
	att->type = component_new();
	list_add_tail(&att->list, &att_loader_head);

	return att->type;
}

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
			struct component*at = (struct component*)malloc(att->size);
			list_add_tail(&at->list, &component_head);
			at->parent_id = entity;
			return 0;
		}
	}

	//Attribute Not found
	return -1;
}
