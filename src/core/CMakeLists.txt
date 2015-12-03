add_library(core window.c lua_module.c platform.c resources.c entity.c core_components.c system.c component.c)
target_link_libraries(core lual)

if(CONFIG_SDL_PORT)

target_link_libraries(core ${SDL2_LIBRARY} sdlport)

endif()
