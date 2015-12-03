#ifndef __SYSTEM_H
#define __SYSTEM_H 

#include <stdint.h>
#include "list.h"

struct system;

typedef int (*system_update)(struct system* system, float dt, struct system* arg);
typedef int (*system_init)(struct system* system);
typedef void* (*system_alloc)(struct system* system, int size);

struct system {
	uint32_t id;
	system_update update;
	system_init init;	
	system_alloc alloc;
	struct list_head list;
	const char* name;
};


int system_register(const char* name, struct system* sys);
int system_init(void);
void* system_alloc_component(int id, int size);
int system_update(float dt);
#endif /* ifndef __SYSTEM_H */
