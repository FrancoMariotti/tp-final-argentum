cmake_minimum_required(VERSION 3.15)
project(argentum)
include_directories(..)

find_package(Qt5Widgets)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -pthread")
file(COPY config DESTINATION ./)
file(COPY config DESTINATION ./../Servidor)

add_executable(SDLTest src/client_main.cpp)
FILE(GLOB sdlSRCS src/*.cpp src/*.h)
add_library(clienteSRCS ${sdlSRCS})

target_link_libraries(SDLTest clienteSRCS commonLib qtLib SDL2 SDL2_image SDL2_ttf SDL2_mixer)
add_subdirectory(Qt)


#add_executable(Cliente main.cpp)
