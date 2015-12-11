
#include <stdint.h>
#include <stdio.h>
#include "window.h"
#include "system.h"

/***************** Prototypes ********************/
#ifdef CONFIG_SDL_PORT
void sdl_init(void);
#endif

void lua_init(void);

struct platform_init {
	const char* name;
	void (*function)(void);
};

void entity_init(void);
void core_components_init(void);
int core_systems_init(void);
/*
 * platform_init  - entry point for all engine
 */
void platform_init(void)
{
	struct platform_init m_platform[] =
	{

///////// Core Modules /////////////////////////////
#ifdef CONFIG_SDL_PORT
		{.name = "SDL WINDOW", .function = sdl_init},
#endif
		{.name = "System", .function = system_init},
		{.name = "Core Components", .function = core_components_init},
		{.name = "Core Systems", .function = core_systems_init},
///////// Secondary   //////////////////////////////
		{.name = "Lua Module", .function = lua_init},
		{.name = "Entity", .function = entity_init},
		{0, 0}
	};

	struct platform_init *plat = m_platform;
	while(plat->name != 0)
	{
		printf("Starting the module %s \n", plat->name);
		plat->function();
		plat++;
	}

	system_init();
}

/*
 * platform_loop - after evertything is initiated, lets work
 */
void platform_loop(void)
{
	int rc;
	do
	{
		system_update(100);
		window_render();
		rc = window_update(100);
	}while(rc == 0);
}
