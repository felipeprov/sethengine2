#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(int argc, char* argv[])
{
	lua_State *L = luaL_newstate();
	luaopen_base(L);
	luaopen_table(L);
	luaopen_string(L);
	luaopen_math(L);


	lua_close(L);
	return 0;
}

