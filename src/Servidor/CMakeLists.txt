project(argentum)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(Modelo)
target_link_libraries(${PROJECT_NAME} myclasses)
#target_link_libraries(${PROJECT_NAME} cppunit)