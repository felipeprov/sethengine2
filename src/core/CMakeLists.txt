add_library(core window.c lua_module.c platform.c sdport.c)
target_link_libraries(core lual ${SDL2_LIBRARY})