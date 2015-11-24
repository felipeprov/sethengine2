#include <stdint.h>
#include "core_components.h"

void core_components_init(void)
{
	component_register("Transform", sizeof(struct transform_component));
	component_register("Image", sizeof(struct resource_component));
	component_register("Audio", sizeof(struct resource_component));
}
