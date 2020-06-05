cmake_minimum_required(VERSION 2.8)
project(argentum)

# Flags de compilacion
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -pedantic -Wall -Werror -g")

add_subdirectory(Servidor)
add_subdirectory(Tests)
#cuando agreguen cosas descomentar
#add_subdirectory(Cliente)
