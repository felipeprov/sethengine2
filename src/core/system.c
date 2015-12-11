#include "system.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static LIST_HEAD(system_root);
static LIST_HEAD(components_root);

static void* default_alloc(struct system* sys, int size)
{
	return malloc(size);
}

static struct system default_system= 
{
	.name = "Default",
	.alloc = default_alloc,
};

static int new_system_id(void)
{
	static int system_id = 0;

	return system_id++;
}

int system_register(struct system* sys)
{
	list_add_tail(&sys->next, &system_root);
	sys->id = new_system_id();

	return sys->id;
}


int system_update(float dt)
{
	struct list_head *pos;
	list_for_each(pos, &system_root)
	{
		struct system * sys = container_of(pos, struct system, next);
		if(sys->update)
		{
			sys->update(sys, dt, sys->arg);
		}
	}
	return 0;
}

int system_init(void)
{
	struct list_head *pos;
	
	system_register(&default_system); 

	list_for_each(pos, &system_root)
	{
		struct system * sys = container_of(pos, struct system, next);
		if(sys->init)
		{
			sys->init(sys);
		}
	}

	return 0;
}

void* system_alloc_component(int id, int size)
{
	struct list_head *pos;
	list_for_each(pos, &system_root)
	{
		struct system * sys = container_of(pos, struct system, next);
		if(id == sys->id)
		{
			if(sys->alloc)
			{
				return sys->alloc(sys, size);
			}
		}
	}

	return 0;

}

int system_get_id(const char* name)
{
	struct list_head *pos;
	list_for_each(pos, &system_root)
	{
		struct system * sys = container_of(pos, struct system, next);
		if( strcmp(name, sys->name) == 0 )
		{
			return sys->id;
		}
	}

	return 0;
}
