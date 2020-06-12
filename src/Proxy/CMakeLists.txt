cmake_minimum_required(VERSION 3.15)
project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sdlsrc
        src/sdl_exception.cpp
        src/sdl_texture.cpp src/sdl_texture.h src/dot.cpp src/dot.h src/sdl_window.cpp src/sdl_window.h src/sdl_npc.cpp src/sdl_npc.h)

add_executable(SDLTest src/main_motion.cpp)

target_link_libraries(SDLTest sdlsrc SDL2 SDL2_image SDL2_ttf)



#add_executable(Cliente main.cpp)
