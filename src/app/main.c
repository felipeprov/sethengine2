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
	window_loop();

	return 0;
}

