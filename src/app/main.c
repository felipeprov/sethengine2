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
	printf("Starting Loop\n");
	platform_loop();

	return 0;
}

