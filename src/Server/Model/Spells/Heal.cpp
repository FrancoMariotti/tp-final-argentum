#include "Heal.h"
#include "Server/Model/Character/PlayableCharacter.h"

int Heal::use(Character *owner,Character *target, int strength, int level,int damage) {
    owner->restoreLife();
    return 0;
}
