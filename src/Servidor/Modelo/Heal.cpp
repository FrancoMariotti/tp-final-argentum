#include "Heal.h"

int Heal::useOn(Character *target, int strength, int level, MagicalWeapon *weapon) {
    return weapon->use(this,target,strength,level);
}
