#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "component.h"
#include "entity.h"

#define	MAX_COMPONENTS_TYPES 512

static LIST_HEAD(att_loader_head);
static LIST_HEAD(component_head);

static struct list_head comp_by_type[MAX_COMPONENTS_TYPES];


int component_init(void)
{
	for(int i= 0; i < MAX_COMPONENTS_TYPES; i++)
	{
		LIST_HEAD_INIT(comp_by_type[i]);
	}
}

int component_type_new(void)
{
	static uint32_t componentype = 1;

	return componentype++;
}

struct component* component_new(const char* name)
{
	static uint32_t componentype = 1;
	struct component_template *template = component_get_template(name);
	if(template)
	{
		int size = template->size;
		struct component* comp = malloc(size);
		comp->type = template->type;

		list_add(&comp->list, &component);
		list_add(&comp->next, &comp_by_type[comp->type]);
		comp->uid = componentype++;
		return comp;
	}
	return 0;
}

int component_template_register(const char* type, uint32_t size, int alloc_id, component_setter setter)
{
	struct component_template* att = (struct component_template*)malloc(sizeof(struct component_template));

	strncpy(att->name, type, sizeof(att->name));
	att->size = size;
	att->type = component_type_new();
	att->alloc_id = alloc_id;
	att->setter = setter;
	list_add_tail(&att->list, &att_loader_head);

	return att->type;
}

int component_get_type(const char* type)
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

struct component_template* component_get_template(const char* name)
{
	struct list_head* pos;
	list_for_each(pos, &att_loader_head)
	{
		struct component_template* att = list_entry(pos, struct component_template, list);

		if(strncmp(name, att->name, 32) == 0)
		{
			return att;
		}
	}
	return 0;
}

int component_set_property(int uid, int field_id, void* value)
{
	struct list_head* pos;
	struct component* found_comp = 0;
	list_for_each(pos, &component_head)
	{
		struct component* comp = list_entry(pos, struct component, list);

		if(comp->uid == uid)
		{
			found_comp = comp;
			break;
		}
	}

	if(!found_comp)
		goto erro_exit

	list_for_each(pos, &att_loader_head)
	{
		struct component_template* att = list_entry(pos, struct component_template, list);
		
		if(att->type == found_comp->type)
		{
			return att->setter(found_comp, field_id, value);
		}
	}

error_exit:
	return -1;
}


void* component_get_by_uid(int uid)
{
	struct list_head* pos;
	list_for_each(pos, &component_head)
	{
		struct component* comp = list_entry(pos, struct component, list);

		if(comp->uid == uid)
		{
			return comp;
		}
	}

	return 0;
}

struct list_head* component_get_list(int type)
{
	if(type < 0)
		return &component_head;
	else
		return &comp_by_type[type];
}
