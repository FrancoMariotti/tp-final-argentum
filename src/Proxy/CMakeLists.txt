cmake_minimum_required(VERSION 3.15)
project(argentum)
include_directories(..)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -pthread")
file(COPY config DESTINATION ./)
file(COPY config DESTINATION ./../Servidor)

add_executable(SDLTest src/client_main.cpp)
FILE(GLOB sdlSRCS src/*.cpp src/*.h)
add_library(clienteSRCS ${sdlSRCS})

add_library(clienteConnection
                ./../Servidor/Conexion/Serializer.h
                ./../Servidor/Conexion/MessageSerializer.h
                ./../Servidor/Conexion/MessageSerializer.cpp
                ./../Servidor/Conexion/MessageSerializer.h
                ./../Servidor/Conexion/MovementMessageSerializer.h
                ./../Servidor/Conexion/MovementMessageSerializer.cpp
                ./../Servidor/Conexion/DrawMessageSerializer.h
                ./../Servidor/Conexion/DrawMessageSerializer.cpp
        ./../Servidor/Conexion/ConnectMessageSerializer.h
                ./../Servidor/Conexion/ConnectMessageSerializer.cpp
                ./../Servidor/Conexion/Protocol.h
                ./../Servidor/Conexion/Protocol.cpp)


target_link_libraries(SDLTest clienteSRCS clienteConnection commonLib SDL2 SDL2_image SDL2_ttf SDL2_mixer)



#add_executable(Cliente main.cpp)
