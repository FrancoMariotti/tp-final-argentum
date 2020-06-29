#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H

#include "Character.h"
#include "Equippable.h"

class Equippable;
class Character;

class Weapon : public Equippable {
    protected:
        //int minDamage;
        //int maxDamage;
        int calculateDamage(int strength);
    public:
        Weapon(std::string name, int minDamage,int maxDamage);
        void equipTo(PlayableCharacter *character, int i) override;
        virtual int attack(Character *enemy,int strength,int level,int &mana,Position &holderPos) = 0;
        virtual ~Weapon() = default;

    void unequipFrom(PlayableCharacter *character);
};


#endif //ARGENTUM_WEAPON_H
