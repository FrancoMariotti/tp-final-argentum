project(argentum)

FILE(GLOB SRCS *.cpp *.h)

add_library(servidorConexionLib ${SRCS} MessageSerializer.cpp MessageSerializer.h Serializer.h MovementMessageSerializer.cpp MovementMessageSerializer.h)