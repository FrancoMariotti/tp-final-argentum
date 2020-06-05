project(argentum)

include_directories(${SERVER_SOURCE_DIR}/Modelo)

add_executable(tests
        TestMain.cpp
        Mapa/MapaTest.cpp)

target_link_libraries(tests cppunit modelo)