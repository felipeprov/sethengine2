add_library(core window.c lua_module.c platform.c resources.c)
target_link_libraries(core lual)

if(CONFIG_SDL_PORT)

add_library(sdlport sdport.c)
target_link_libraries(core ${SDL2_LIBRARY} sdlport)

endif()