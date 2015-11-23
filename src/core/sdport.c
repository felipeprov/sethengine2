
#include <stdio.h>
#include "list.h"
#include "window.h"
#include "resources.h"

#include <SDL.h>

struct sdl_vars{
	SDL_Window* win;
	SDL_Renderer* ren;
};

struct sdl_img{
	struct resource res;
	SDL_Texture *tex;
	struct sdl_vars* vars;
};


static int sdl_window_init(struct window_module* module);
static int sdl_window_update(struct window_module* module, float dt);
static int sdl_window_render(struct window_module* module);
static struct resource* sdl_load_bmp(struct resource_loader* load, const char* path);
static int sdl_bmp_process(struct resource* res);

static struct window_module sdport={
	.name = "SDL",
	.init = sdl_window_init,
	.update = sdl_window_update,
	.render = sdl_window_render,
};

static struct resource_loader sdl_bmp_loader=
{
	.name = "BMP Loader",
	.ext = "bmp",
	.load = sdl_load_bmp,
	.process = sdl_bmp_process
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
	sdl_bmp_loader.data = vars;

	resource_loader_register(&sdl_bmp_loader);
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

/** BMP Loader **/
static struct resource* sdl_load_bmp(struct resource_loader* load, const char* path)
{
	struct sdl_vars* vars = (struct sdl_vars*)(load->data);
	SDL_Surface *bmp = SDL_LoadBMP(path);
	if (bmp == NULL){
		return 0;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(vars->ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == NULL){
		return 0;
	}

	struct sdl_img* img = (struct sdl_img*)malloc(sizeof(struct sdl_img));
	img->tex = tex;
	img->vars = vars;

	return &img->res;
}

static int sdl_bmp_process(struct resource* res)
{
	struct sdl_img* img = container_of(res, struct sdl_img, res);
	SDL_RenderCopy(img->vars->ren, img->tex, NULL, NULL);

	return 0;
}


void sdl_init(void)
{
	window_register(&sdport);
}
	
