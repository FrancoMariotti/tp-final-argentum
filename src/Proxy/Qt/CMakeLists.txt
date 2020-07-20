project(argentum)
include_directories(..)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -pthread")

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

# Agrego ProxyQt/include a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/include)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
        ui/client_qt_characterlogin.ui
        ui/client_qt_charactercreation.ui
        ui/client_qt_serverlogin.ui
        ui/mainwindow.ui
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

# Permite llamar al "automoc", que es una herramienta que toma archivos.h con
# metadatos de Qt y expande sus macros
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(qt_argentum_v2
        src/client_qt_characterlogin.cpp
        src/client_qt_loginmediator.cpp
        src/client_qt_serverlogin.cpp
        src/client_qt_charactercreation.cpp
        src/mainwindow.cpp
        src/main.cpp
        ${UIS_HEADERS}
        ../assets/resources.qrc)

#add_executable(qtServer src/server_main.cpp src/QtServer.cpp src/QtServer.h)

add_library(qtLib
        src/client_qt_characterlogin.cpp
        src/client_qt_loginmediator.cpp
        src/client_qt_serverlogin.cpp
        src/client_qt_charactercreation.cpp
        src/mainwindow.cpp
        src/main.cpp
        ${UIS_HEADERS}
        )

# Use the Widgets module from Qt 5.
target_link_libraries(qt_argentum_v2 clienteSRCS commonLib SDL2 SDL2_image SDL2_ttf SDL2_mixer Qt5::Widgets)
#target_link_libraries(qtServer commonLib)
