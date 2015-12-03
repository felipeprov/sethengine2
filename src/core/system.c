#include "system.h"
#include <stdint.h>

static LIST_HEAD(system_root);

static void* default_alloc(struct system* sys, int size)
{
	return malloc(size);
}

static struct system default_system= 
{
	.alloc = default_alloc,
};

static int new_system_id(void)
{
	static int system_id = 0;

	return system_id++;
}

int system_register(const char* name, struct system* sys)
{
	list_add_tail(&system->list, &system_root);
	system->id = new_system_id();

	return system->id;
}


int system_update(float dt)
{
	struct list_head *pos;
	list_for_each(pos, &system_root)
	{
		if(pos->update)
		{
			pos->update(pos, dt);
		}
	}
}

int system_init(void)
{
	struct list_head *pos;
	
	system_register("Default System", &default_system); 

	list_for_each(pos, &system_root)
	{
		if(pos->init)
		{
			pos->init(pos);
		}
	}

}

void* system_alloc_component(int id, int size)
{
	struct list_head *pos;
	list_for_each(pos, &system_root)
	{
		if(id == pos->id)
		{
			if(pos->alloc)
			{
				return pos->alloc(pos,size);
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
		if( strcmp(name, pos->name) == 0 )
		{
			return pos->id;
		}
	}

}
