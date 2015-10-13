
add_executable (sethengine main.c)
target_link_libraries(sethengine lual core ${SDL2_LIBRARY})
