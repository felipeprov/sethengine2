#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "window.h"

#include <SDL.h>
#undef main
struct window_module module1 = {
	.name = "Window Module1"
};

struct window_module module2 = {
	.name = "Window Module2"
};

int main(int argc, char* argv[])
{
	lua_State *L = luaL_newstate();
	luaopen_base(L);
	luaopen_table(L);
	luaopen_string(L);
	luaopen_math(L);


	window_register(&module1);
	window_register(&module2);

	window_print_available();

	lua_close(L);

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		//std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL){
		//std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL){
		SDL_DestroyWindow(win);
		//std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	SDL_Delay(1000);
	
	return 0;
}

