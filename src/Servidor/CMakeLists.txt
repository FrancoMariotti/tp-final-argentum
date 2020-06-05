project(argentum)

add_executable(Servidor main.cpp)
add_subdirectory(Modelo)
target_link_libraries(Servidor modelo)