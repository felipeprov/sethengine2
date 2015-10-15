
#include <stdint.h>
#include <stdio.h>

#define CONFIG_SDL_PORT
/***************** Prototypes ********************/
#ifdef CONFIG_SDL_PORT
void sdl_init();
#endif

void lua_init(void);

struct platform_init {
	const char* name;
	void (*function)(void);
};

void platform_init()
{
	struct platform_init m_platform[] =
	{

///////// Core Modules /////////////////////////////
#ifdef CONFIG_SDL_PORT
		{.name = "SDL WINDOW", .function = sdl_init},
#endif

///////// Secondary   //////////////////////////////
		{.name = "Lua Module", .function = lua_init},
		{0, 0}
	};

	struct platform_init *plat = m_platform;
	while(plat->name != 0)
	{
		printf("Starting the module %s \n", plat->name);
		plat->function();
		plat++;
	}
}