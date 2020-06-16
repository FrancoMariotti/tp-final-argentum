#include "EventMove.h"

EventMove::EventMove(Offset offset):offset(offset) {}

void EventMove::execute(Game& game,std::string player) {
    game.movePlayer(player,offset);
}

EventMove::~EventMove() = default;