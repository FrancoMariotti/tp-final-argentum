project(argentum)

FILE(GLOB SRCS "*.cpp")

add_library(servidorModeloLib
        ${SRCS}
        )