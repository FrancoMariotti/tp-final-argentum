project(argentum)
include_directories(..)

# Flags de compilacion
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -pedantic -Wall -Werror -g")
file(COPY config DESTINATION ./)
add_executable(Servidor main.cpp)
add_library(proxysources
        ./../Proxy/src/common_proxy_socket.h
        ./../Proxy/src/common_proxy_socket.cpp
        ./../Proxy/src/common_message_structs.h
        ./../Proxy/src/common_message.h
        ./../Proxy/src/common_message.cpp
        ./../Proxy/src/common_osexception.h
        ./../Proxy/src/common_osexception.cpp
        ./../Proxy/src/common_closedqueue_exception.h
        ./../Proxy/src/common_closedqueue_exception.cpp)
add_subdirectory(Common)
add_subdirectory(Conexion)
add_subdirectory(Modelo)
target_link_libraries(Servidor servidorModeloLib proxysources commonLib jsoncpp)