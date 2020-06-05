project(argentum)

file(GLOB mapaSrcsLib ./Servidor/*/*.cpp)

add_executable(tests
        TestMain.cpp
        ${mapaSrcsLib}
        )

#add_subdirectory(Servidor)
#add_subdirectory(cliente)

target_link_libraries(tests cppunit servidorModeloLib)
#testServidorLib