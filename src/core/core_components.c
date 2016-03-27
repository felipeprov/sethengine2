#include <stdint.h>
#include "core_components.h"
#include "system.h"
#include "component.h"
#include "resources.h"

static int transform_setter(struct component* comp, int field_id, void* value)
{
	struct transform_component* me = (struct transform_component*)comp;

	switch (field_id) {
		case SET_X:
			me->x = (float)value;	
			break;
		case SET_Y:
			me->y = (float)value;	
			break;
		case SET_W:
			me->w = (float)value;	
			break;
		case SET_H:
			me->h = (float)value;	
			break;		
		case SET_SX:
			me->sx = (float)value;	
			break;
		case SET_SY:	
			me->sy = (float)value;	
			break;
		case SET_ROT:
			me->rot = (float)value;	
			break;		
	}

	return 0;
}

static int image_setter(struct component* comp, int field_id, void* value)
{
	struct image_component* me = (struct image_component*)comp;

	switch (field_id) {
		case SET_RES:
			me->res = resource_get_by_uid((int)value);	
			break;
		case SET_TRANS:
			me->trans = component_get_by_ui((int)value);	
			break;
	}

	return 0;
}

void core_components_init(void)
{
	int id;
	component_register("Transform", sizeof(struct transform_component), 0, transform_setter);
	id = system_get_id("Render System");
	component_register("Image", sizeof(struct image_component), id, image_setter);

	id = system_get_id("Audio System");
	component_register("Audio", sizeof(struct resource_component), id);
}
