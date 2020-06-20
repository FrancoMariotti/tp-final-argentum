cmake_minimum_required(VERSION 3.15)
project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -pthread")

add_library(sdlsrc
        src/client_sdl_exception.cpp
        src/client_sdl_texture.cpp
        src/client_sdl_texture.h
        src/dot.cpp src/dot.h
        src/client_sdl_window.cpp
        src/client_sdl_window.h
        src/client_sdl_player.cpp
        src/client_sdl_player.h
        src/common_blocking_queue.h
        src/client_sdl_button.cpp
        src/client_sdl_button.h
        src/client_command.cpp
        src/client_command.h
        src/common_osexception.cpp
        src/common_osexception.h
        src/common_proxy_socket.cpp
        src/common_proxy_socket.h
        src/common_protocol.cpp
        src/common_protocol.h
        src/common_socket.cpp
        src/common_socket.h
        src/common_thread.cpp
        src/common_thread.h
        src/client_client.cpp
        src/client_client.h
        src/client_sdl_inventory.cpp
        src/client_sdl_inventory.h
        src/client_iobserver.h
        src/client_sdl_console.cpp
        src/client_sdl_console.h
        src/client_th_send.cpp
        src/client_th_send.h src/common_message.cpp src/common_message.h src/client_protected_list.h src/client_th_recv.cpp src/client_th_recv.h src/common_closedqueue_exception.cpp src/common_closedqueue_exception.h)


add_executable(SDLTest src/client_main.cpp)

target_link_libraries(SDLTest sdlsrc SDL2 SDL2_image SDL2_ttf)



#add_executable(Cliente main.cpp)
