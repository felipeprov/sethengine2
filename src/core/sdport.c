
#include "list.h"
#include "window.h"
#include <stdio.h>

#include <SDL.h>

struct sdl_vars{
	SDL_Window* win;
	SDL_Renderer* ren;
};

static int sdl_window_init(struct window_module* module)
{
	struct sdl_vars* vars = (struct sdl_vars*)malloc(sizeof(struct sdl_vars));
	struct window_properties prop = module->properties;

	(module->data) = vars;

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("SDL init error %d \n", SDL_GetError());
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow(prop.name, prop.x, prop.y, prop.width, prop.length, SDL_WINDOW_SHOWN);
	if (win == NULL){
		printf("SDL_CreateWindow error %d \n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL){
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	vars->win = win;
	vars->ren = ren;

	return 0;
}

static int sdl_window_update(struct window_module* module, float dt)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		if(e.type == SDL_QUIT)
			return -1;
	}

	return 0;
}

static int sdl_window_render(struct window_module* module)
{
	struct sdl_vars* vars = (struct sdl_vars*)module->data;
	SDL_RenderClear(vars->ren);
	SDL_RenderPresent(vars->ren);

	return  0;
}

struct window_module sdport={
	.name = "SDL",
	.init = sdl_window_init,
	.update = sdl_window_update,
	.render = sdl_window_render
};

void sdl_init(void)
{
	window_register(&sdport);
}
	