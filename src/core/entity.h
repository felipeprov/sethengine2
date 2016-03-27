#ifndef __ENTITY_H
#define __ENTITY_H

#include <stdio.h>
#include "list.h"

struct entity_t {
	int id;
};

void entity_init(void);
int entity_new(void);
int entity_add_component(int entity, const char* name);
int entity_search_component(int entity, const char* name);

#endif /* end of include guard: __ENTITY_H */
