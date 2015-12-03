#include <stdint.h>
#include "core_components.h"
#include "system.h"
#include "component.h"

void core_components_init(void)
{
	int id;
	component_register("Transform", sizeof(struct transform_component), 0);
	id = system_get_id("Render System");
	component_register("Image", sizeof(struct resource_component), id);

	id = system_get_id("Audio System");
	component_register("Audio", sizeof(struct resource_component), id);
}
