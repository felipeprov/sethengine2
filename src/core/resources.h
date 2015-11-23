#ifndef __RESOURCES_H
#define __RESOURCES_H 

#include <stdint.h>
#include "list.h"

enum{
	RESOURCE_GRAPHICAL = 0,
	RESOURCE_AUDIO,
	RESOURCE_LUA_SCRIPT
};

struct resource_loader;

struct resource{
	struct list_head list;
	uint32_t type;
	struct resource_loader* loader;
};

struct resource_loader
{
	struct list_head list;
	const char* name;
	const char* ext;
	struct resource* (*load)(struct resource_loader* load, const char* path);
	int (*process)(struct resource* res);
	void* data;
};


void resource_loader_register(struct resource_loader* loader);
void resource_process(struct resource* res);
struct resource* resource_load(const char* filename);
void resource_print(void);

#endif
