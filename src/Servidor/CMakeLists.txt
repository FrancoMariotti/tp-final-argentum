project(argentum)
include_directories(..)
include_directories(msgpack-c/include)
# Flags de compilacion
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -pedantic -Wall -Werror -g -pthread")
file(COPY config DESTINATION ./)
file(COPY config DESTINATION ./../Proxy)
add_executable(Servidor main.cpp)
add_library(proxysources
        ./../Proxy/src/common_socket.h
        ./../Proxy/src/common_socket.cpp
        ./../Proxy/src/common_proxy_socket.h
        ./../Proxy/src/common_proxy_socket.cpp
        ./../Proxy/src/common_message_structs.h
        ./../Proxy/src/common_message.h
        ./../Proxy/src/common_message.cpp
        ./../Proxy/src/common_osexception.h
        ./../Proxy/src/common_osexception.cpp
        ./../Proxy/src/common_blocking_queue.h
        ./../Proxy/src/common_thread.h
        ./../Proxy/src/common_thread.cpp
        ./../Proxy/src/client_protected_list.h
        ./../Proxy/src/common_closedqueue_exception.h
        ./../Proxy/src/common_closedqueue_exception.cpp)
add_subdirectory(Common)
add_subdirectory(Conexion)
add_subdirectory(Modelo)
target_link_libraries(Servidor servidorModeloLib servidorConexionLib proxysources commonLib jsoncpp)