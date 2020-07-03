project(argentum)

FILE(GLOB SRCS *.cpp *.h)

add_library(servidorModeloLib ${SRCS} CommandExecutor.cpp CommandExecutor.h)