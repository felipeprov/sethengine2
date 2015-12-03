#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "component.h"
#include "entity.h"

static LIST_HEAD(component_head);
static LIST_HEAD(att_loader_head);

static int component_new(void)
{
	static uint32_t componentype = 1;

	return componentype++;
}

int component_register(const char* type, uint32_t size, int alloc_id)
{
	struct component_template* att = (struct component_template*)malloc(sizeof(struct component_template));

	strncpy(att->name, type, sizeof(att->name));
	att->size = size;
	att->type = component_new();
	att->alloc_id = alloc_id;
	list_add_tail(&att->list, &att_loader_head);

	return att->type;
}

int component_get(const char* type)
{
	struct list_head *pos;
	list_for_each(pos, &att_loader_head)
	{
		struct component_template* comp = list_entry(pos, struct component_template, list);

		if(strncmp(type, comp->name, 32) == 0)
		{
			return comp->type;
		}
	}

	return -1;
}
