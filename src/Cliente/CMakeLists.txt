project(argentum)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -pthread")

# Find the QtWidgets library
find_package(Qt5Widgets)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

# Agrego ej3/include a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/include)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
        ui/client_qt_characterlogin.ui
        ui/client_qt_serverlogin.ui
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

# Permite llamar al "automoc", que es una herramienta que toma archivos.h con
# metadatos de Qt y expande sus macros
set(CMAKE_AUTOMOC ON)

add_executable(qt_argentum
  src/client_qt_characterlogin.cpp
  src/client_qt_loginmediator.cpp
  src/client_qt_serverlogin.cpp
  src/main.cpp
  ${UIS_HEADERS}
        )

# Use the Widgets module from Qt 5.
target_link_libraries(qt_argentum Qt5::Widgets)
