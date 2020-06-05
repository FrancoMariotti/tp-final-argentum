cmake_minimum_required(VERSION 2.8)

project(argentum)

# specify the c++ standard
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
# Flags de compilacion
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic-errors -pedantic -Wall -Werror -g")

add_executable(${PROJECT_NAME} main.cpp)
