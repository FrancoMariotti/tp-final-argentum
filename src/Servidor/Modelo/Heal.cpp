#include "Heal.h"
#include "PlayableCharacter.h"

int Heal::use(Character *owner,Character *target, int strength, int level,int damage) {
    if(owner == target) {
        owner->restoreLife();
    }
    return 0;
}
