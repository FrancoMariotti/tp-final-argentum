#ifndef ARGENTUM_EVENTMOVE_H
#define ARGENTUM_EVENTMOVE_H

#include "string"
#include "Event.h"
#include "Offset.h"

class EventMove: public Event {
    Offset offset;
    public:
        explicit EventMove(Offset offset);
        void execute(Game& game,std::string player) override;
        ~EventMove();
};


#endif //ARGENTUM_EVENTMOVE_H
