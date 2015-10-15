
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "window.h"


struct lua_info{
	lua_State *L;
};

void lua_init(void)
{
	lua_State *L = luaL_newstate();
	luaopen_base(L);
	luaopen_table(L);
	luaopen_string(L);
	luaopen_math(L);

	lua_close(L);
}