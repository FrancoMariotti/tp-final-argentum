project(argentum)

FILE(GLOB SRCS *.cpp *.h)

add_library(servidorModeloLib ${SRCS} Event.h EventMove.cpp EventMove.h)