#ifndef __CORE_COMPONENT_H
#define __CORE_COMPONENT_H 

#include <stdint.h>
#include "entity.h"
#include "resources.h"
#include "component.h"

struct transform_component{
	struct component comp;
	float x;
	float y;
	float w;
	float l;
	float sx;
	float sy;
	float rot;
};

struct resource_component{
	struct component comp;
	struct resource res;
};

void core_components_init(void);

#endif /* ifndef __CORE_COMPONENT_H */
