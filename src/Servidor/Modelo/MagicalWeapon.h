#ifndef ARGENTUM_MAGICALWEAPON_H
#define ARGENTUM_MAGICALWEAPON_H

#include "Character.h"
#include "Weapon.h"

class SpellType;
class Heal;
class Damage;

class MagicalWeapon: public Weapon {
    int cost;
    SpellType *spellType;
    public:
        MagicalWeapon(std::string name,SpellType *spellType,
                int minDamage,int maxDamage,int cost, int goldCost);
        int attack(Character* owner,Character *enemy,int strength,int level,float &mana,Position &holderPos) override;
        ~MagicalWeapon() override;

};


#endif //ARGENTUM_MAGICALWEAPON_H
