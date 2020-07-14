project(argentum)
include_directories(..)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors -pthread")

# Find the QtWidgets library
find_package(Qt5Widgets)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

# Agrego Cliente/include a la lista de directorios de includes
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

#Esta libreria quiero agregar
add_library(qtProxysources
        ./../Proxy/src/common_proxy_socket.h
        ./../Proxy/src/common_proxy_socket.cpp
        ./../Proxy/src/common_message_structs.h
        ./../Proxy/src/common_message.h
        ./../Proxy/src/common_message.cpp
        ./../Proxy/src/common_osexception.h
        ./../Proxy/src/common_osexception.cpp
        ./../Proxy/src/common_blocking_queue.h
        ./../Proxy/src/common_thread.h
        ./../Proxy/src/common_thread.cpp
        ./../Proxy/src/client_protected_list.h
        ./../Proxy/src/common_closedqueue_exception.h
        ./../Proxy/src/common_closedqueue_exception.cpp)
# Use the Widgets module from Qt 5.
target_link_libraries(qt_argentum proxysources Qt5::Widgets)
