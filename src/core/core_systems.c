#include <stdint.h>
#include "system.h"
#include "component.h"
#include <string.h>
#include <stdlib.h>

struct render_sys_entry
{
	struct list_head next;
	struct transform_component* trans;
	struct resource_component* image;	
	int flags;
	struct component component;
	uint8_t data[];
};

static LIST_HEAD(render_entries);

static int render_sys_update(struct system* system, float dt, struct system* arg)
{
	struct list_head pos;

	list_for_each(pos, &render_entries)
	{
		struct render_sys_entry *entry = container_of(pos, struct render_sys_entry, next);

		if(!entry->flags)
		{
			int ent = entry->component.parent_id;
			entry->trans = entity_search_component(ent, "Transform");	
			entry->image = entity_search_component(ent, "Image");	
			entry->flags = 1;
		}
	}

	return 0;
}

static int render_sys_init(struct system* system)
{
	return 0;
}

static void* render_sys_alloc(struct system* system, int size)
{
	size = sizeof(struct render_sys_entry) + size;
	struct render_sys_entry *entry = (struct render_sys_entry*)malloc(size);
	memset(entry, 0, size);

	return entry;
}


static struct system render=
{
	.name = "Render",
	.update = render_sys_update,
	.init = render_sys_init,
	.alloc = render_sys_alloc
};

int core_systems_init(void)
{
	system_register(&render);
	return 0;
}

