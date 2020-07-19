#ifndef ARGENTUM_DAMAGE_H
#define ARGENTUM_DAMAGE_H

#include "SpellType.h"

class Damage: public SpellType {
public:
    Damage();
    int use(Character* owner,Character *target,int strength,int level,int damage) override;
    ~Damage();
};


#endif //ARGENTUM_DAMAGE_H
