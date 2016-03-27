#include <stdint.h>
#include "system.h"
#include "component.h"
#include <string.h>
#include <stdlib.h>
#include "entity.h"
#include "core_components.h"

static int render_sys_update(struct system* system, float dt, struct system* arg)
{
	struct list_head *pos;
	int type = component_get_type("Image"); 
	struct list_head *renders = component_get_list(type);

	list_for_each(pos, renders)
	{
		struct image_component* img = (struct image_component*)comp;
		resource_process(img->img);
	}

	return 0;
}

static int render_sys_init(struct system* system)
{
	return 0;
}

static struct system render=
{
	.name = "Render",
	.update = render_sys_update,
	.init = render_sys_init,
};

int core_systems_init(void)
{
	system_register(&render);
	return 0;
}

