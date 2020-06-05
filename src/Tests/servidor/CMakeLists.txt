add_executable(run_tests run_tests.cpp)

add_subdirectory(MapaTests)

target_link_libraries(run_tests myclasses mapa-test cppunit)