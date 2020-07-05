//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_DROPPABLE_H
#define ARGENTUM_DROPPABLE_H

class PlayableCharacter;

class Droppable {
public:
    virtual void takenBy(PlayableCharacter* player) = 0;
    virtual ~Droppable() = default;
};


#endif //ARGENTUM_DROPPABLE_H
