#ifndef ARGENTUM_DAMAGE_H
#define ARGENTUM_DAMAGE_H

#include "SpellType.h"

class Damage: public SpellType {
public:
    Damage();
    int useOn(Character *target,int strength,int level,MagicalWeapon *weapon) override;
    ~Damage();
};


#endif //ARGENTUM_DAMAGE_H
