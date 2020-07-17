cmake_minimum_required(VERSION 2.8)
project(argentum)
include_directories(..)

find_package(Qt5Widgets)

#find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt5 COMPONENTS Core REQUIRED)
message("[INFO] La raiz Proxy es ${PROJECT_SOURCE_DIR}")

# Agrego ProxyQt/include a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/Qt/include)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -pthread")
file(COPY config DESTINATION ./)
file(COPY config DESTINATION ./../Servidor)

add_executable(SDLTest src/client_main.cpp)
FILE(GLOB sdlSRCS src/*.cpp src/*.h)
add_library(clienteSRCS ${sdlSRCS})

target_link_libraries(SDLTest clienteSRCS commonLib qtLib SDL2 SDL2_image SDL2_ttf SDL2_mixer Qt5::Widgets)
add_subdirectory(Qt)


#add_executable(Cliente main.cpp)
