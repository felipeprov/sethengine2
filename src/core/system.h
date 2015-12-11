#ifndef __SYSTEM_H
#define __SYSTEM_H 

#include <stdint.h>
#include "list.h"

struct system;

typedef int (*system_update_cb)(struct system* system, float dt, struct system* arg);
typedef int (*system_init_cb)(struct system* system);
typedef void* (*system_alloc_cb)(struct system* system, int size);

struct system {
	uint32_t id;
	void* arg;
	system_update_cb update;
	system_init_cb init;	
	system_alloc_cb alloc;
	struct list_head next;
	struct list_head components;
	const char* name;
};


int system_register(struct system* sys);
int system_init(void);
void* system_alloc_component(int id, int size);
int system_update(float dt);
int system_get_id(const char* name);
#endif /* ifndef __SYSTEM_H */
