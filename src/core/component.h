#ifndef __COMPONENT_H
#define __COMPONENT_H 

#include <stdint.h>
#include <list.h>

#define component_register_type(name, attr) attribute_register(name, sizeof(attr)); 
struct component {
	struct list_head list;
	uint32_t type;
	uint32_t parent_id;
};

struct component_template {
	uint32_t size;
	struct list_head list;
	uint32_t type;
	int alloc_id;
	char name[32];
};

int component_register(const char* type, uint32_t size, int alloc_id);
int component_get_type(const char* type);
struct component_template* component_get_template(const char* name);

#endif /* ifndef __COMPONENT_H */
