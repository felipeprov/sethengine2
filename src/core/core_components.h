#ifndef __CORE_COMPONENT_H
#define __CORE_COMPONENT_H 

#include <stdint.h>
#include "entity.h"
#include "resources.h"
#include "component.h"

enum{
	SET_X = 0,
	SET_Y,
	SET_W,
	SET_H,
	SET_SX,
	SET_SY,
	SET_ROT
	SET_RES,
	SET_TRANS,
};

struct transform_component{
	struct component comp;
	float x;
	float y;
	float w;
	float h;
	float sx;
	float sy;
	float rot;
};

struct image_component{
	struct component comp;
	struct resource* img;
	struct transform_component* trans;
}

struct audio_component{
	struct component comp;
	struct resource* audio;
};

void core_components_init(void);

#endif /* ifndef __CORE_COMPONENT_H */
