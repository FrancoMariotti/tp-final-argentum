//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_DROPPABLE_H
#define ARGENTUM_DROPPABLE_H

#include <Server/Model/Map/Position.h>

class PlayableCharacter;

class Droppable {
public:
    virtual void takenBy(PlayableCharacter *player, Position& position) = 0;
    virtual ~Droppable() = default;
};


#endif //ARGENTUM_DROPPABLE_H
