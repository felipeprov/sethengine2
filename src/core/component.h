#ifndef __COMPONENT_H
#define __COMPONENT_H 

#include <stdint.h>
#include <list.h>

#define component_register_type(name, attr) attribute_register(name, sizeof(attr)); 
struct component {
	struct list_head list;
	struct list_head next;
	uint32_t type;
	uint32_t parent_id;
	uint32_t uid;
};

typedef int (*component_setter)(struct component* comp, int filed_id, void* value);

struct component_template {
	uint32_t size;
	struct list_head list;
	uint32_t type;
	int alloc_id;
	char name[32];
	component_setter setter;
};

struct component* component_new(void);
int component_type_new(void);
int component_template_register(const char* type, uint32_t size, int alloc_id, component_setter setter);
int component_get_type(const char* type);
struct component_template* component_get_template(const char* name);
void* component_get_by_uid(int uid);
int component_set_property(int uid, int field_id, void* value)
struct list_head* component_get_list(int type);

#endif /* ifndef __COMPONENT_H */
