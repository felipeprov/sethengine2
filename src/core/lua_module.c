
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "window.h"
#include "resources.h"

struct lua_info{
	lua_State *L;
};

//@TODO Implement the mechanismo to load startup script and update scripts

static struct resource* lua_load_script(struct resource_loader* load, const char* path)
{
	lua_State *L = (lua_State*)load->data;

	return NULL;
}


static int lua_script_process(struct resource* res)
{
	return 0;
}

static struct resource_loader lua_script_loader=
{
	.name = "Lua Loader",
	.ext = "lua",
	.load = lua_load_script,
	.process = lua_script_process
};

void lua_init(void)
{
	lua_State *L = luaL_newstate();
	luaopen_base(L);
	luaopen_table(L);
	luaopen_string(L);
	luaopen_math(L);

	lua_close(L);
	lua_script_loader.data = L;	
	resource_loader_register(&lua_script_loader);
}
