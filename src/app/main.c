#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "resources.h"

void platform_init(void);
void platform_loop(void);

struct window_properties prop = {
	"SethEngine",
	640,
	480,
	100,
	100,
};

int main(int argc, char* argv[])
{
	platform_init();

	printf("Window startup\n");
	window_start(prop);

	resource_print();

	uint32_t ent1 = entity_new();
	int transf = entity_add_component(ent1, "Transform");
	int img = entity_add_component(ent1, "Image");
    
 	componet_set_property(transf, SET_X, (void*) 0);	
 	componet_set_property(transf, SET_Y, (void*) 50);	
 	componet_set_property(transf, SET_H, (void*) 64);	
 	componet_set_property(transf, SET_W, (void*) 64);	
 	componet_set_property(transf, SET_SX, (void*) 1.0f);	
 	componet_set_property(transf, SET_SY, (void*) 1.0f);	
 	componet_set_property(transf, SET_ROT, (void*) 0);	

 	componet_set_property(img, SET_RES, (void*) 0);	
 	componet_set_property(img, SET_TRANS, (void*)transf);	

	printf("Starting Loop\n");
	platform_loop();

	return 0;
}

