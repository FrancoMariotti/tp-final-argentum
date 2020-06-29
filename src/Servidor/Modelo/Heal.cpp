#include "Heal.h"

int Heal::giveAbilityTo(MagicalWeapon *weapon, Character *target, int strength, int level) {
    return weapon->use(this,target,strength,level);
}
