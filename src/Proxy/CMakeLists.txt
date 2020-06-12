cmake_minimum_required(VERSION 3.15)
project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(sdlsrc
        src/client_sdl_exception.cpp
        src/client_sdl_texture.cpp src/client_sdl_texture.h src/dot.cpp src/dot.h src/client_sdl_window.cpp src/client_sdl_window.h src/client_sdl_player.cpp src/client_sdl_player.h
        src/common_blocking_queue.h src/client_sdl_button.cpp src/client_sdl_button.h)

add_executable(SDLTest src/client_main.cpp)

target_link_libraries(SDLTest sdlsrc SDL2 SDL2_image SDL2_ttf)



#add_executable(Cliente main.cpp)
