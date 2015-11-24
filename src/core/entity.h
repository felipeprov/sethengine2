#ifndef __ENTITY_H
#define __ENTITY_H

#include <stdio.h>
#include "list.h"

struct component {
	struct list_head list;
	uint32_t type;
	uint32_t parent_id;
};

struct entity_t {
	uint32_t id;
};

#define component_register_type(name, attr) attribute_register(name, sizeof(attr)); 

int component_register(const char* type, uint32_t size);

void entity_init(void);
uint32_t entity_new(void);
int entity_add_component(uint32_t entity, const char* name);

#endif /* end of include guard: __ENTITY_H */
