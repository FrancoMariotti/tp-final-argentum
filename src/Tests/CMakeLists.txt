project(argentum)

include_directories(..)

file(GLOB modeloTestsSrcs Modelo/*/*.cpp)

add_executable(tests
        TestMain.cpp
        ${modeloTestsSrcs})

target_link_libraries(tests cppunit servidorModeloLib)