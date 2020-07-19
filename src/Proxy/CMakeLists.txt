cmake_minimum_required(VERSION 2.8)
project(argentum)
include_directories(..)

file(COPY assets DESTINATION ./)
file(COPY audio DESTINATION ./)
file(COPY interfaces DESTINATION ./)
file(COPY items DESTINATION ./)

find_package(Qt5Widgets)

#find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt5 COMPONENTS Core REQUIRED)
message("[INFO] La raiz Proxy es ${PROJECT_SOURCE_DIR}")

# Agrego ProxyQt/include a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/Qt/include)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -pthread")

add_executable(SDLTest src/client_main.cpp)
FILE(GLOB sdlSRCS src/*.cpp src/*.h)
add_library(clienteSRCS ${sdlSRCS})
add_subdirectory(Qt)

target_link_libraries(SDLTest clienteSRCS commonLib qtLib SDL2 SDL2_image SDL2_ttf SDL2_mixer Qt5::Widgets)


#add_executable(Cliente main.cpp)
