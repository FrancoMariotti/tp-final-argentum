project(argentum)

FILE(GLOB SRCS *.cpp *.h)

add_library(servidorModeloLib ${SRCS} SpellType.h Heal.cpp Heal.h Damage.cpp Damage.h LifeState.h Ghost.cpp Ghost.h Alive.cpp Alive.h)