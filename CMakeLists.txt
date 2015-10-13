cmake_minimum_required(VERSION 3.2)

project(SethEngine2)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SethEngine2_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

link_directories("lib/SDL2-2.0.3/lib/x64")


add_subdirectory(src)

