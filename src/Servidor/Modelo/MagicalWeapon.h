#ifndef ARGENTUM_MAGICALWEAPON_H
#define ARGENTUM_MAGICALWEAPON_H

#include "Weapon.h"

class SpellType;
class Heal;
class Damage;

class MagicalWeapon: public Weapon {
    int cost;
    SpellType *spellType;
    public:
        MagicalWeapon(std::string name,SpellType *spellType, int minDamage,int maxDamage,int cost);
        int attack(Character *enemy,int strength,int level,int &mana,Position &holderPos) override;
        int use(Heal *spell, Character *target, int strength, int level);
        int use(Damage *spell, Character *target, int strength, int level);
        ~MagicalWeapon() override;

};


#endif //ARGENTUM_MAGICALWEAPON_H
