#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H

#include "Equippable.h"
#include "Position.h"

class Equippable;
class Character;
class PlayableCharacter;

class Weapon : public Equippable {
    protected:
        int calculateDamage(int strength);
    public:
        Weapon(std::string name, int minDamage,int maxDamage, int goldCost);
        void equipTo(PlayableCharacter *character, int i) override;
        virtual int attack(Character *enemy,int strength,int level,int &mana,Position &holderPos) = 0;
        void unequipFrom(PlayableCharacter *character) override ;
        virtual ~Weapon() = default;
};


#endif //ARGENTUM_WEAPON_H
