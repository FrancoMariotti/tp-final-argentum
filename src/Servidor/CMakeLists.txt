project(argentum)

add_executable(Servidor main.cpp)
add_subdirectory(Modelo)
target_link_libraries(Servidor myclasses)
#target_link_libraries(${PROJECT_NAME} cppunit)