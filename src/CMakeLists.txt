include_directories(core app base)

option(CONFIG_SDL_PORT "SDL" ON)

if(CONFIG_SDL_PORT)
	add_definitions(-DCONFIG_SDL_PORT)
endif()

add_subdirectory(lua)
add_subdirectory(app)
add_subdirectory(core)

