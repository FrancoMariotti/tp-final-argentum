#include "StrategyMoveNPC.h"
#include "Offset.h"
#include "Character.h"

#define MAX_RANGE 4

void StrategyMoveNPC::move(Position currPos,Map& map) {
    Offset offset(0,0);

    Character* enemy = map.findClosestCharacter(currPos, MAX_RANGE);
    if (!enemy) {
        offset.randomDir();
    } else {
        offset = enemy->getOffset(currPos);
        offset.approach();
    }

    Position siguiente(currPos);
    siguiente.apply(offset);
    map.move(currPos,siguiente);
}