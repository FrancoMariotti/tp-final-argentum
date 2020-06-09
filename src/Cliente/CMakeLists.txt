cmake_minimum_required(VERSION 3.15)
project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sdlsrc
        sdl/src/sdl_exception.cpp
        sdl/src/sdl_texture.cpp sdl/src/sdl_texture.h sdl/src/dot.cpp sdl/src/dot.h sdl/src/sdl_window.cpp sdl/src/sdl_window.h sdl/src/sdl_npc.cpp sdl/src/sdl_npc.h)

add_executable(SDLTest sdl/src/main_motion.cpp)

target_link_libraries(SDLTest sdlsrc SDL2 SDL2_image SDL2_ttf)


#add_executable(Cliente main.cpp)
