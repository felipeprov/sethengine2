#ifndef __ENTITY_H
#define __ENTITY_H

#include <stdio.h>
#include "list.h"

struct entity_t {
	uint32_t id;
};

void entity_init(void);
uint32_t entity_new(void);
int entity_add_component(uint32_t entity, const char* name);

#endif /* end of include guard: __ENTITY_H */
