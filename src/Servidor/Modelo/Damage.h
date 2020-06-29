#ifndef ARGENTUM_DAMAGE_H
#define ARGENTUM_DAMAGE_H

#include "SpellType.h"

class Damage: public SpellType {
public:
    Damage();
    int giveAbilityTo(MagicalWeapon *weapon,Character *target,int strength,int level);
    ~Damage();
};


#endif //ARGENTUM_DAMAGE_H
