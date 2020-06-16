#ifndef ARGENTUM_EVENT_H
#define ARGENTUM_EVENT_H

#include "Game.h"

class Event {
public:
    virtual void execute(Game& game,std::string player) = 0;
    virtual ~Event() = default;
};

#endif //ARGENTUM_EVENT_H
