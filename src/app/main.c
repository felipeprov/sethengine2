#include <stdio.h>
#include <stdlib.h>
#include "window.h"


void platform_init();

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
	window_start(prop);

	for(int i = 0; i< 10; i++)
		window_update(100);

	return 0;
}

