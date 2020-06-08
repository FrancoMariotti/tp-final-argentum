project(argentum)

# Flags de compilacion
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -pedantic -Wall -Werror -g")

add_executable(Servidor main.cpp)
add_subdirectory(Modelo)
target_link_libraries(Servidor servidorModeloLib)