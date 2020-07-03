#include "Heal.h"
#include "PlayableCharacter.h"

int Heal::use(Character *owner,Character *target, int strength, int level,int damage) {
    owner->restoreLife();
    return 0;
}
