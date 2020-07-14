project(argentum)
include_directories(..)
find_package(msgpack REQUIRED)
# Flags de compilacion
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -pedantic -Wall -Werror -g -pthread")
file(COPY config DESTINATION ./)
add_executable(Servidor main.cpp)

add_subdirectory(Conexion)
add_subdirectory(Modelo)
target_link_libraries(Servidor servidorConexionLib servidorModeloLib commonLib jsoncpp)